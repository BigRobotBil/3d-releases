// Originally by FluffyQuack
// https://www.fluffyquack.com/tools/source/VCPS3buttons.rar
// Release Thread: https://steamcommunity.com/sharedfiles/filedetails/?id=342465902
// Changes made by Zeek to only target a specific texture
// Original release doesn't appear to have a license, but I use the "Free as in Free Beer" license for my terrible contribution

#include <stdio.h>
#include <tchar.h>

unsigned char initialSequence[16] = {0xFD, 0x03, 0xCF, 0x67, 0xE0, 0xBF, 0x49, 0xC7, 0x00, 0x00, 0x00, 0x00, 0x54, 0x01, 0x00, 0x00};

unsigned int Scan(unsigned char *data, unsigned int dataSize, unsigned char *entryArray, unsigned int entrySize)
{
	for(unsigned int i = 0; i < dataSize; i++)
		for(unsigned int j = 0; j < entrySize; j++)
		{
			if(data[i + j] != entryArray[j] || i + j >= dataSize)
				break;

			if(j == entrySize - 1)
				return i;
		}

	return 0;
}

void Process()
{
	//Open file
	FILE *file;
	fopen_s(&file, "Valkyria.exe", "rb");
	if(!file)
	{
		printf("Error: Could not open file ""Valkyria.exe"" for reading.\n");
		return;
	}

	//Get size of file
	fpos_t fpos;
	fseek(file, 0, SEEK_END);
	fgetpos(file, &fpos);
	fseek(file, 0, SEEK_SET);
	unsigned int dataSize = (unsigned int) fpos;

	//Create buffer for new file
	unsigned char *data = new unsigned char[dataSize];

	//Read in file
	fread(data, 1, dataSize, file);
	fclose(file);

	//Scan for texture sequence
	unsigned int seqPos = Scan(data, dataSize, initialSequence, 16);
	if(seqPos == 0)
	{
		printf("Failed to find texture sequence. Executable is already modified?\n");
		delete[]data;
		return;
	}

	//Back up executable
	fopen_s(&file, "Valkyria-backup.exe", "wb");
	if(!file)
	{
		printf("Error: Could not open file ""Valkyria-backup.exe"" for writing.\n");
		delete[]data;
		return;
	}
	fwrite(data, 1, dataSize, file);
	fclose(file);
	printf("Wrote backup of Valkyria.exe\n");

	//Replace texture IDs
	unsigned int pos = seqPos;
	int count = 0;
	while(1)
	{
		count++;
		if(( (unsigned long long &) data[pos] == 3358280212318419906))
		{
			for(int i = 0; i < 8; i++)
				data[pos + i] = 0;
		}
		pos += 48;
		if(count >= 146 || (unsigned int &) data[pos] == 257)
			break;
	}

	//Write new executable
	fopen_s(&file, "Valkyria.exe", "wb");
	if(!file)
	{
		printf("Error: Could not open file ""Valkyria.exe"" for writing.\n");
		delete[]data;
		return;
	}
	fwrite(data, 1, dataSize, file);
	fclose(file);
	delete[]data;
	printf("Successfully edited Valkyria.exe\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
	printf("Valkyria Chronicles Playstation button prompt tool v1.2\n\n");

	Process();
}

// The original if statement that would go on line 79, in the while loop:
// if(!( (unsigned long long &) data[pos] == 4121779029669587293 //These are textures for "exit game", should still be replaced
// 	|| (unsigned long long &) data[pos] == 7682352040093519435 
// 	|| (unsigned long long &) data[pos] == 15293619919312322294 //These are HQ backgrounds, should still be replaced
// 	|| (unsigned long long &) data[pos] == 14424422347982842161
// 	|| (unsigned long long &) data[pos] == 12812042920565827770
// 	|| (unsigned long long &) data[pos] == 6979617774316825669
// 	|| (unsigned long long &) data[pos] == 17234129099337211102
// 	|| (unsigned long long &) data[pos] == 1126660568197716564
// 	|| (unsigned long long &) data[pos] == 6329309893307687112
// 	|| (unsigned long long &) data[pos] == 15040148626767517281 //Dialogue portrait borders, also should be replaced
// 	))