This files were originally created when I was under the impression I'd have to manually disable the marker above NPCs/enemies. However, alternatively solutions were found. These should not be used, but they're here since I went through the stupid effort.

> [!WARNING]
> None of this is required to use the fix as detailed in the main [README](../README.md).

The below instructions would have accompanied the README when the fix was in this state. However, keep in mind if you decide to engage this method to disable the textures, you will also have to hunt down the texture that corresponds to the crosshair. I didn't think of that until _after_ I put all this together, originally.

Do as you wish.


### In Game UI Change

> [!NOTE]
> Normally during gameplay, there is a marker above an enemy or ally to denote that you are currently targetting them.  This UI element isn't very pleasing to look at, and can instead be disabled by replacing a specific file with one of the ones provided.  This UI element is part of a larger texture, and we must overwrite the entire texture to remove this UI element.


Included in the fix folder is the folder `vc_replacement_textures`, containing three different folders:

- `xbox`
- `pc`
- `ps3`

These correspond to the glyphs/icons that will be on screen.  There is a `DLC_0002_val_in_action.htx` in all three, and each one is unique to the type of glyph.

Included in the fix folder is the folder `VCGlyphOverwrite` with `VCGlyphOverwrite.exe` within it. This will be used to modify the game's executable to load the custom texture that has been selected from the three different folders mentioned previously.

> [!CAUTION]
> Once this file is replaced, key rebinding and the glyphs changing dynamically between Xbox and Keyboard & Mouse for the in-game UI will no longer work!  Key rebinding will _technically_ still work, but the UI will not show any differences!

_If you plan to use the Playstation glyphs, please skip to [Playstation Glyphs subsection](#playstation-glyphs)_

1. Navigate to `Valkyria Chronicles\DLC_0002`
2. Locate the file `DLC_0002_val_in_action.htx`
3. Copy this file as a backup either somewhere else or within this folder (`DLC_0002_val_in_action_original.htx`)
4. Copy the `DLC_0002_val_in_action.htx` from the specific set of glyphs you plan to use for your playthrough
    - This can be swapped any time the game is not running if you desire to change your control method
5. Place `VCGlyphOverwrite.exe` in the same directory as `Valkyria.exe`
6. Double-click `VCGlyphOverwrite.exe` to run it
    - There should now be a `Valkyria.exe` and a `Valkyria_Backup.exe` in the game's folder

The game is now setup to using the custom texture that no longer has the marker above enemies/allies when they are being targetted.

> [!WARNING]
> You must always run the game with the `Valkyria.exe` and not `Valkyria_Backup.exe` to remove the marker above the enemy/ally during combat

If there is something else with the UI that is distracting or you want to customize, please see [this section](../../../tutorials/valkyria-chronicles-1/figuringthingsout_textures.md) on how to create and modify your own textures to match what you want.

To revert this texture change, simply delete `Valkyria.exe` and rename `Valkyria_Backup.exe`.  `DLC_0002_val_in_action_original.htx` can be renamed back to its original file name overwrite the replacement, however the patch to reference this archive is no longer present so it doesn't ultimately matter.

### Playstation Glyphs

If you plan to play the game using Playstation glyphs, please instead download and install the [VCPS3buttons by FluffyQuack](https://steamcommunity.com/sharedfiles/filedetails/?id=342465902) mod.  After setting this up, instead of replacing the textures in the `DLC_0002` folder provided by FluffyQuack, use the one provided in the fix archive for `ps3` that has been provided.  The Playstation glyphs included here have the marker remove as well as the X/O button swap performed.