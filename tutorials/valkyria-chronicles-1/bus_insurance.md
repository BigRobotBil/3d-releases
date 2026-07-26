_In case I get hit by a bus_

# Adjust depth
If you want to change the core issue with this fix, the various UI depth problems, you can go to this shader:

`ShaderFixes\3077d8f92f235b5a-vs_replace.txt`

Within here is this section:

```hlsl
  if (forceOffDepthRespectGameplay.z != 1) {
    float gameplayActive = (texFilter.x == 0 || texFilter.x == 1) && gameplayFilter.x == 0;
    
    if (gameplayActive) {
      if (o0.y > -0.5 && o0.y < 0.63 && o0.x > -0.36 && o0.x < 0.35) {
        o0.x += adjust_from_depth_buffer(0, 0, 255);
      }
    }
  }
```

The important part is the last if statement listed:

```hlsl
if (o0.y > -0.5 && o0.y < 0.63 && o0.x > -0.36 && o0.x < 0.35)
```

This creates an invisible rectangle that all items within it will be pushed into the screen. The previous conditionals attempt to isolate _what_ can get pushed in, but there's more work that could be done to truly fix this. However, with it's current state, if you want to adjust the size of this rectangle, you can make it larger or smaller based on your preference.

`o0.y` controls the vertical, and `o0.x` controls the horizontal. For something like the tank crosshair, the horizontal can be increased like so:

```hlsl
if (o0.y > -0.5 && o0.y < 0.63 && o0.x > -0.4 && o0.x < 0.4)
```

However, some other aspects of the UI will be affected and distorted due to this. But, it's an option if you don't find it _that_ distracting.

# Unit Selection

The unit selection that appears during a mission is controlled via the texture located within:

`Valkyria Chronicles\DLC_0002\DLC_0002_val_in_cmd_chip`

(Only one texture dumps here with VCTool)

This can be confirmed by launching the game with TexMod:

https://gamebanana.com/tools/6973

> [!TIP]
> Ensure that, with every new scene, you adjust the filtering toggle to be only textures drawn on screen, otherwise the game will likely crash

> [!NOTE]
> I only had success launching this tool with the game on my older laptop, where the installed Nvidia driver was 425.31, running a 750M. It crashed on my main desktop (using the latest Nvidia drivers on a 2080 Ti), so YMMV

When the unit selection appears, iterate until it's highlighted.

It is 512 x 512. This appears to match with the following from a ShaderUsage dump:

```xml
<Register orig_hash=a43af1f4 type=Texture2D width=512 height=512 mips=1 array=1 format="BC3_TYPELESS" msaa=1 msaa_quality=0 usage="DEFAULT" bind_flags="shader_resource" cpu_access_flags=0 misc_flags=0 hash_contaminated=true>
```

Assigning it:

```ini
[TextureOverride_UnitSelection6]
Hash=a43af1f4
filter_index=20
```

And filtering in `3077d8f92f235b5a-vs_replace`:

```hlsl
  if (texFilter.x == 20) {
    return;
  }
```

The texture does not draw. I assume that means I've targetted the correct one. Applying the depth adjustment:

```hlsl
  if (texFilter.x == 20) {
    if (o0.y > -0.9 && o0.y < 0.9 && o0.x > -0.9 && o0.x < 0.9) {
      adjust_from_depth_buffer(0, 0, 255);
    }
  }
```

This appears to wipe out everything related to the texture on screen instead of pushing it in as I thought it would.