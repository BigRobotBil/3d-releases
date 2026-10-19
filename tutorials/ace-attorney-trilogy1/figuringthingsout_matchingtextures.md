# Matching Textures

In other fixes detailed here, I went and dumped textures to make glorified booleans. This allowed us to trigger different 3D effects based on the presence of them. Now, for a game that is _completely_ flat, we have to make the 3D ourselves. This could be viewed as an extension of leveraging the `adjust_from_depth_buffer`, but we can take a much simplier approach:

```hlsl
o0.x = stereo.x * <some number>
```

or

```hlsl
o0.x = stereo.x * stereo.y * <some number>
```

## Trials and Tribulations

To begin with, the first instinct is to dump textures, see what their hashes are, and see if we can push them into depth at all. My first attempt was with another VN, and I was able to achieve this with this simple setup:

```ini
;10 is backgrounds
[TextureOverride_RoofSunset]
Hash=0a351a6e
filter_index=10

;20 is characters/middle
[TextureOverride_SoneDefaultIdle]
Hash=0763b838
filter_index=20

[TextureOverride_AoiEnthralled1_NormalColor]
Hash=c188677c
filter_index=20

[ShaderOverride_Everything]
Hash=f7751cb99529458e
x10 = ps-t0
```

```hlsl
  float4 stereo = StereoParams.Load(0);
  float4 texFilter = IniParams.Load(int2(10,0));

  if (texFilter.x == 10) {
    // background
    o0.x += stereo.x * 0.8;
  }
  else if (texFilter.x == 20) {
    // character
    o0.x += stereo.x * 0.3;
  }
```

So _AA_ should be pretty similiar. As a nice bonus, _AA_ has a Gallery mode where you can pick any pose from a character, and put them against whatever backdrop in the game. To start off, they have Phoenix in his usual position:

- screenshot here of opening the gallery

If we do the normal thing covered in other tutorials in this Github:

```ini
; Enable dumping the ShaderUsage.txt. We'll need it later
dump_usage=1
; Dumping options. See the readme right about this line for other options
analyse_options = dump_tex mono dds
```

> [!WARNING]
> This is likely overkill, and will dump out _a lot_. Be wary when you're doing a much larger game. You may want to instead target a specific shader, or shaders, when doing a dump instead to isolate more. And yes, I copied and pasted this from my _Pac-Man CE2_ section, making this the ... third time?