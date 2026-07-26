# A Box

_It's recommended you view the failures of the [Texture Atlas](figuringthingsout_textureatlas.md) before viewing this to understand how we got here_

I've started working on this fix in Feburary of 2026. It started with fixing shadows, getting stuck on water, and the remaining bit (assuming nothing else terrible happens) is the HUD. After all the trouble I've had, being specifically stuck on this, I've admitted defeat on trying to make something elegant. I can see why eqzitara opted to just disable most of the UI instead of trying to fix it; there's so many overlapping pieces. I feel as though this wouldn't be _as_ terrible if I could reasonably dump the textures from the game to identify different parts. But, the game will crash with the various versions of geo-11 I've tried.

_c'est la vie_

What we're going to do instead now is make a big dumb box on the screen that should only affect what we care about. We did this in _[Studio System](./../studio-system/figuringthingsout_crosshair.md)_, albeit at a much smaller scale.

After some trial and error, this size will do the job:

```hlsl
if (o0.y > -0.5 && o0.y < 0.5 && o0.x > -0.35 && o0.x < 0.35) {
    o0.x += adjust_from_depth_buffer(0, 0, 255);
}
```

There are some caveats:
- If there is a UI element outside of this box, it will appear at screen depth
- If the UI element is at the threshold, it'll appear warped/distorted

In testing this, my focus wasn't really at the sides of the screen, so the first bullet isn't too concerning. The second bullet, however, is a bit jarring, but there's not much else we can do. If we expand the box, more objects we _don't_ want to be affected will get drawn in. It's a compromise


## Shader Filtering

We can try to make it less painfully a bit more by specifically only doing this behaviour if we're in gameplay. Other fixes generally determine this based on textures. For example, if the texture for the title screen is present, we wouldn't do anything we care about for depth adjustment that would be in game. However, we can only get so far with this since we'd have to blindly figure out the hashes for each texture we want to affect.

```ini
;If we're in gameplay or not. Default to not, for initial title screen(s)
x90=1

[PresetGameplay]
x90 = 0

[ShaderOverride_GameplayEnabled]
Hash=83e630450d0ca593
preset = Gameplay
```

_More testing needs to be done if this is a valid shader to care about_

> [!WARNING]
> In initial testing, the one shader I was using previously randomly appeared on subseqent relaunches of the game where it didn't before. If this is unreliable, it may be best to just remove it and rely on...

## Additional Toggle

Since _I_ am not going to take the time to determine a bunch of different textures, it's time to implement a general toggle:

```ini
[Constants]
;Depth during gameplay toggle. An "oh crap" button
z20=0

[KeyHUDDepthToggle]
Key = 2
Key = XB_BACK
back = shift 1
type = cycle
z20 = 0, 1
```

If a user presses `2` (or the `Back`/`Minus`/`Whatever They Call Select These Days` on the controller), we can toggle if our depth adjustment is on or off. During gameplay, especially at the beginning, there's a bunch of help/tutorial information that will fly over the screen. These will be distorted despite our best efforts above, so we can give the user the ability to quickly toggle the depth adjustment off. In an ideal world, we'd detect if certain textures are on screen and dynamically do it, but, whelp.