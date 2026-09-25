# More Stereo Targets

Some games do not initially render in stereo, or some objects that should render simply do not. I've mostly seen this occur with older games or games that need to be converted with dgvoodoo.

## TextureOverride

_Note: This was put together by masterotaku. I take no credit at all for it. Just documenting it here so it's apparent, and so I can easily copy and paste it from somewhere instead of opening one of my fixes_

Within `d3dx.ini`:

```ini
[TextureOverrideAllNonSquareRT]
match_type = Texture2D
match_bind_flags = +render_target
match_width = !height
StereoMode = 1

[TextureOverrideAllNonSquareDT]
match_type = Texture2D
match_bind_flags = +depth_stencil
match_width = !height
StereoMode = 1
```

This will look for `Texture2D` elements the don't have a uniform shape to them (hence `NonSquare`) within render targets and depth stencils (what these ultimately mean is more tailored to how DX11 does rendering and where those resources are within the rendering pipeline). By applying `StereoMode` with a value of `1`, the items will be picked up by geo-11 and stereoized.

## Existing Fixes

Fixes I have created that use this:
- [RefRain - prism memories -](../../../Fixes/geo-11/RefRain/README.md)
- [Valkryia Chronicles](../../../Fixes/geo-11/Valkyria-Chronicles/README.md)
  - Fix is a strong term for this one, and I have to re-evaluate if it was even needed here