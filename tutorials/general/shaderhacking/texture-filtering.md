# Texture Filtering

> [!TIP]
> A general overview on dumping textures with 3DMigoto (geo-11) is provided [here](https://leotorrez.github.io/modding/guides/textures-101)

By dumping a texture, we can create a glorified boolean with it to trigger different conditions. This can be applied for things like:
- Adjusting the depth/convergence
- Disabling a shader
- Triggering conditionals in shader overrides to perform other adjustments

To see this with more tangiable examples:

- [Pac-Man CE2 - Conditional Texture](../../pac-man-ce2/figuringthingsout_conditionaltexture.md)
- [Mirage Feathers - Conditional Texture](../../mirage-feathers/figuringthingsout_conditionaltexture.md)
- [Valyria Chronicles - Texture Atlas](../../valkyria-chronicles-1/figuringthingsout_textureatlas.md#filtering-for-the-right-texture)

## Setting Things Up

Within `d3dx.ini` find and make the following changes:

```
; Be sure this is uncommented. Change the hotkey if you want
analyse_frame = no_modifiers VK_F8
; Enable dumping the ShaderUsage.txt
dump_usage=1
; Dumping options. See the readme right about this line for other options
analyse_options = dump_tex mono jpg
```

> [!NOTE]
> You can dump dds format to get textures with proper transparency. However, be sure you have _plenty_ of hard drive space if you think you'll hit your dumping hotkey more than once

## Run the Game

- Start the game
- Get to a moment where a texture is loaded that you want to dump
- Press `F8` (unless you changed the hotkey)

Within the game's directory, there will be two new items:
- `ShaderUsage.txt`
  - This contains an XML dump of the game's current state in regards to:
    - Textures
    - Shaders
- FrameAnalysis-<Timestamp>
  - This will contain _all_ the textures that were active when the hotkey was pressed
  - This is the folder we want to start looking at
  - A folder, `deduped`, is also in here, and contains all of the textures but removes any duplicates

Personally, I would go through the `dedupe` folder, and find the texture I was trying to find. Then, after knowing its attributes, find it in the parent folder. The filename of the texture will contain the overall information about it that will be important to making an override. For example:

If we look in the parent folder of the deduped, we can find a file with this hash on the front:

`000049-ps-t0=75ad0735-vs=af8c3eb5b621448e-ps=5aa5a715c29b4a9c.dds`

- `ps-t0` - The register this texture is under
- `75ad0735` - The texture's hash
- `vs=af8c3eb5b621448e` - The vertex shader that reads in the texture
- `ps=5aa5a715c29b4a9c` - The pixel shader the reads in the texture

With this information, in `d3dx.ini`, we can make an override:

```ini
;Dialog box that's exclusive to cutscenes
[TextureOverride_DialogBox]
Hash=<hash from the filename>
filter_index=<arbitrary number of your choosing>
```

### ini Override

We can make a conditional within `d3dx.ini` like so:

```ini
[ShaderOverride_SomethingReallyCool]
Hash=<a shader hash that will target the texture>
if (ps-t0 == <the same arbitrary number>)
  ; don't actually do this to your eyes
  separation = 500
endif
```

Whenever the shader loads, it will be given various textures. When the one we specifically targetted loads, the `ps-10` will have a value of the `filter_index` that we gave it.

### Internal Shader Conditional

We can pass along the filter index to inside the shader we are manipulating, and trigger whatever logic with it.

Initial setup in the `d3dx.ini`:

```ini
[ShaderOverride_SomethingRadical]
Hash=<a shader hash that will target the texture>
x10 = ps-t0
```
- `x10` can be a different value. It doesn't matter as long as it fits in the confines of geo-11's params (x/y/z###)
- `x10` will have a value of the current index in `ps-t0`
  - In our case, we will be conditionally waiting for it to have the value of the `filter_index` set earlier, so it's important to have that value be something obvious and noted down

In the vertex shader:

```hlsl
// This will load all the "10" values, so we technically have y10 as well (but these will, of course, be undefined). Keeping consistent variables is important
float4 texFilter = IniParams.Load(int2(10,0));

...

if (texFilter.x == <filter_index value>) {
    // do something absolutely NUTS
}
```

An example of something to do here would be to call the `adjust_from_depth_buffer`, or stereoize certain items differently. As, a specific texture _may_ be a sign that something is close to the screen or far away, etc. It all really depends on the game and what you're trying to accomplish.