# Adjust From Depth Buffer Setup

_The one thing I know how to do_

This is meant to be a more general document on how to apply the `adjust_from_depth_buffer` method that can be used for push items at screen depth into the scene. This is meant to be brief and copy and pasteable. For details on how this actually works, please checkout the following:

[Auto-Crosshair](https://github.com/bo3b/3Dmigoto/wiki/Auto-Crosshair)
- If you don't actually click this and read it, you're only hurting yourself if you're trying to understand how to apply any of this

To see this with more tangiable examples:

- [Studio System - Crosshair](../../studio-system/figuringthingsout_crosshair.md)
- [Mirage Feathers - HUD](../../mirage-feathers/figuringthingsout_dynamicdepth.md)
- [Valkyria Chronicles - A Box](../../valkyria-chronicles-1/figuringthingsout_abox.md)

# Code

_Note: All code below is from the above Auto Crosshair link. I take no credit for any of this at all_

Find the following in a HLSL vertex shader (generally after all the register declarations):

```hlsl
// 3Dmigoto declarations
#define cmp -
Texture1D<float4> IniParams : register(t120);
Texture2D<float4> StereoParams : register(t125);
```

Paste the following right after:

```hlsl
Texture2D<float> DepthBuffer : register(t110);

static const float near = 0.1;
static const float far = 40000;

float world_z_from_depth_buffer(float x, float y)
{
	uint width, height;
	float z;

	DepthBuffer.GetDimensions(width, height);

	x = min(max((x / 2 + 0.5) * width, 0), width - 1);
	y = min(max((-y / 2 + 0.5) * height, 0), height - 1);
	z = DepthBuffer.Load(int3(x, y, 0));
	if (z == 1)
		return 0;

	// Derive world Z from depth buffer. This is a kluge since I don't know
	// the correct scaling, and the Z buffer seems to be (1 - what I expected).
	// Might be able to determine the correct way to scale it from other shaders.
	return far*near/(((1-z)*near) + (far*z));
}

float adjust_from_depth_buffer(float x, float y)
{
	float4 stereo = StereoParams.Load(0);
	float separation = stereo.x; float convergence = stereo.y;
	float old_offset, offset, w, sampled_w, distance;
	uint i;

	// Stereo cursor: To improve the accuracy of the stereo cursor, we
	// sample a number of points on the depth buffer, starting at the near
	// clipping plane and working towards original x + separation.
	//
	// You can think of this as a line in three dimensional space that
	// starts at each eye and stretches out towards infinity. We sample 255
	// points along this line (evenly spaced in the X axis) and compare
	// with the depth buffer to find where the line is first intersected.
	//
	// Note: The reason for sampling 255 points came from a restriction in
	// DX9/SM3 where loops had to run a constant number of iterations and
	// there was no way to set that number from within the shader itself.
	// I'm not sure if the same restriction applies in DX11 with SM4/5 - if
	// it doesn't, we could change this to check each pixel instead for
	// better accuracy.
	//
	// Based on DarkStarSword's stereo crosshair code originally developed
	// for Miasmata, adapted to Unity, then translated to HLSL.

	offset = (near - convergence) * separation;	// Z = X offset from center
	distance = separation - offset;			// Total distance to cover (separation - starting X offset)

	old_offset = offset;
	for (i = 0; i < 255; i++) {
		offset += distance / 255.0;

		// Calculate depth for this point on the line:
		w = (separation * convergence) / (separation - offset);

		sampled_w = world_z_from_depth_buffer(x + offset, y);
		if (sampled_w == 0)
			return 0;

		// If the sampled depth is closer than the calculated depth,
		// we have found something that intersects the line, so exit
		// the loop and return the last point that was not intersected:
		if (w > sampled_w)
			break;

		old_offset = offset;
	}

	return old_offset;
}
```

Somewhere in your shader:

```hlsl
o0.x += adjust_from_depth_buffer(0,0,255);
```

Within `d3dx.ini`:

```ini
[ResourceDepthBuffer]
max_copies_per_frame=1

[ShaderOverrideCrosshair]
Hash = <vertex shader hash>
ResourceDepthBuffer = oD unless_null
vs-t110 = ResourceDepthBuffer
```

## Setup For Toggle

I generally include a toggle for this, so a user may turn it on or off, as it may not be needed depending on their existing convergence preferences.

Within `d3dx.ini`:

```ini
[Constants]
; HUD toggle
z20=0
```

```ini
[KeyHUDDepthToggle]
Key = 3
Key = XB_RIGHT_THUMB
type = cycle
z20 = 0, 1
```

Somewhere within your shader:

```hlsl
float4 hudToggle = IniParams.Load(int2(20,0));
if (hudToggle.z == 1) {
    o0.x += adjust_from_depth_buffer(0,0);
}
```


## Existing Fixes

Fixes I have created that use this:
- [Devotion](../../../Fixes/geo-11/Devotion/README.md)
- [The Missing](../../../Fixes/geo-11/Missing-JJ/README.md)
- [Pac-Man Championship Edition 2](../../../Fixes/geo-11/Pac-Man-CE2/README.md)
- [RefRain - prism memories -](../../../Fixes/geo-11/RefRain/README.md)
- [Studio System: Guardian Angel](../../../Fixes/geo-11/StudioSystem-GuardianAngel/README.md)
- [Valkryia Chronicles](../../../Fixes/geo-11/Valkyria-Chronicles/README.md)
  - Fix is a strong term for this one