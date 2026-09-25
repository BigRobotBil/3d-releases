 # _AI: The Somnium Files_ - geo-11 Stereoscopic 3D Fix

- [Changelog](#changelog)
- [Existing Fix](#existing-fix)
- [General](#general)
- [Instructions](#instructions)
- [Fixed Items and Issues](#fixed-items-and-issues)
- [Credits](#credits)
- [Thanks](#thanks)
- [LICENSE](#license)


<p align="center">
    <a href="screenshots/screenshot1.png"><img src="screenshots/screenshot1.png" width="75%" height="75%"></a>
</p>
<p align="center">
    <a href="screenshots/screenshot2.png"><img src="screenshots/screenshot2.png" width="75%" height="75%"></a>
</p>
<p align="center">
    <a href="screenshots/screenshot3.png"><img src="screenshots/screenshot3.png" width="75%" height="75%"></a>
</p>

## Changelog

- 1.0
  - Initial release

## General

 [Store Link](https://store.steampowered.com/app/948740/AI_The_Somnium_Files/)

Fix was created for the following build number of the game's executable:

- `1.0.0.0`

Fix was tested with the following version(s) of geo-11:

- `v0.7.11`

If either of these items change due to updates, this fix may no longer work.  Any updates to this fix will be posted to [the repo](https://github.com/BigRobotBil/3d-releases/blob/main/Fixes/geo-11/AI-Somnium-Files/) it was downloaded from.

This fix was tested in the following environments and performed as expected in relation to the display type:

- Samsung Odyssey G9 G90XF
- LG 55UH8500
- Sony KDL-50W800C
- Hisense PX3-PRO
- New Nintendo 3DS

An Nvidia GPU was used to test/develop this fix.  Other brands are untested.

## Instructions

- geo-11 `v0.7.11` is included in this archive

Download the `7z` archive [included in this folder](./geo11_aisomniumfiles_1.0.7z).

Navigate to the game's executable `AI_TheSomniumFiles.exe`:

`<path to your install directory>\AI The Somnium Files\`

Place all files within this archive in the same directory.  Meaning in the same folder as the game's main executable, you should now have `d3dx.ini`, `nvapi64.dll`, `ShaderFixes\`, etc.

Adjust settings in-game or within the `d3dxdm.ini` to your liking, which includes the output method. By default, it is set to side-by-side output (`sbs`).

> [!NOTE]
> geo-11's `0.7.7` release (and up) includes native support for Simulated Reality monitors, like the Samsung Odyssey and Acer Spaital Labs. Use `simulated_reality` as the configuration option in the `d3dxdm.ini`. If this does not work, [3DGameBridge](https://github.com/JoeyAnthony/3DGameBridgeProjects) or [SRLoom](https://github.com/effcol/SR-Loom) can be used as alternatives for engaging the weave required for Simulated Reality monitors.

### Control Setup

The following key/controller bindings are active:
- Cycle through depth presets (`25`, `50`)
  - Header: `KeyDepthPresets`
  - `1` (in the number row)
  - `Left Stick Button`/`L3`
- Cycle through convergence presets (`0.5`, `1.0`, `1.5`)
  - Header: `KeyConvergencePresets`
  - `2`
  - `Back`
- Toggle HUD/All 2D Elements pushed in
  - Should only be used when playing at low convergence (`1` should be fine)
  - Header: `KeyHUDDepthToggle`
  - `3` (in number row)
  - `Right Stick Button`/`R3`

Key bindings can be adjusted by editing the relevant sections in the `d3dx.ini` file.

> [!NOTE]
> Please reference <a href="https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes">the list of Virtual Keycodes</a> for precise mapping

## Fixed Items and Issues

Fixes the following:
- Practically everything (Universal Fix)
  - Polishing it up _just a tad_
- HUD depth adjustment by Zeek

Remaining Issues:
- Typical visual novels do not include a "talking head" near the text, but this game duplicates the 3D model on the lower part of the screen. This introduces some slight perspective issues overall throughout the entire game
  - Given that I've seemingly done what I can to adjust the depth of the text in general, I'm not sure what else can be done
- Increasing the depth/convergence beyond the preset values will break the game's visuals pretty badly

## Credits

- Uses the 2019 Unity universal fix to fix common issues with the game (shadows, halos, etc). The bulk of the fix is in this regex
  - The original release post/thread can be found [here](https://helixmod.blogspot.com/2018/09/unity-universal-fix.html)
- Toggles for things by Zeek
- [`adjust_from_depth_buffer`](https://github.com/bo3b/3Dmigoto/wiki/Auto-Crosshair)

## Thanks
- This fix would not exist without the Universal Unity fix! Everything that is working is due to this. Specifically, this is using the 2019 version of the fix
  - DHR, 4everawake
- Members of the HelixMod community that have made fixes over the years that I could see how other fixes worked

## LICENSE

- For any fixes/patterns/whatever that I have created directly within this archive, do whatever you want.  Please reference the [Beerware license](https://fedoraproject.org/wiki/Licensing/Beerware) (but with me instead) for more information
    - If you learn something, that's all that matters.  If you want to give me credit for something, that's `pretty neat`
- For any fixes/patterns included from other individuals, please reference their release information for how they should be attributed and/or reused

----Zeek/BigRobotBil