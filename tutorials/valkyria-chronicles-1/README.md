# <p align="center"><i><b>Valkyria Chronicles</b></i>
</p>

<p align="center"><i>some dumb logo coming when i get around to it</i></p>
<p align="center"><i>this is still a work in progress</i></p>


_Valkyria Chronicles_ is a game that has a bunch of baggage to get going.  I have wanted to play this game for awhile, and never got around to it.  Someone gave me a PS3 copy probably over a decade ago at this point, but the DualShock is quite possibly my least favorte layout for a controller, so I didn't get too far (nothing can compare to [greatness](https://en.wikipedia.org/wiki/Wii_U_Pro_Controller)).  There was a fix created for the original DX9 version of HelixMod, but that doesn't work outside of 3D Vision (obviously, you can make it work, but it's not entirely straight forward).  By wrapping with dgvoodoo, however, we can get it to boot with geo-11.

_But_

It's all broken.  The existing fix can't really be used here, since how shaders generate are completely different from before.  So, whelp, it's time to suffer.

<details>
<summary>Getting 3D for this game with geo-11 v198</summary>

<a href="https://www.pcgamingwiki.com/wiki/Valkyria_Chronicles#API">The Steam release of Valkryia Chronicles is 32-bit only.  Somehow, the Windows Store version has a 64-bit executable</a>.  So, we have to be mindful of the version of geo-11 we apply.

We can follow <a href="https://old.reddit.com/r/Stereo3Dgaming/comments/1qgpqx6/valkyria_chronicles_d3d9_games_in_stereo_3d_on/">noraetic's excellent write up</a> to get it running, with wrapping the game's rendering with dgvoodoo.  There's a break down of all the required files and settings here.

One thing of note when <a href="https://old.reddit.com/r/Odyssey3D/comments/1q7yhcw/need_help_to_set_up_valkyria_chronicles_in_on/nyqk38v/">I was trying to get this to work</a> was that only a specific version of the DX11 wrapper would actually boot up on my end:

<p align="center">
    <a href="figuringscreens/dgvoodoosettings_1.png"><img src="figuringscreens/dgvoodoosettings_1.png" width="25%" height="25%"></a><a href="figuringscreens/dgvoodoosettings_2.png"><img src="figuringscreens/dgvoodoosettings_2.png" width="25%" height="25%"></a>
</p>

The other options for DX11 under `Output API` resulted in geo-11 throwing a bunch of errors on boot or outright crashing.  I specifically went with `Direct3D 11 (feature level 11.0)`, and things were fine then.  Maybe this is obvious to some, but I've only used dgvoodoo a handful of times.  Though, with that out of the way, we can update the version of geo-11 to be a much later build.

Originally, I was under the impression that the only release of the x86 geo-11 was located in the <a href="https://helixmod.blogspot.com/2022/06/announcing-new-geo-11-3d-driver.html">HelixMod release</a> post.  However, with using this very old version, I was running into issues that shaders wouldn't dump with HLSL (or, perhaps, this version is too old that a proper warning doesn't trigger).  Ever hopeful, I checked the <a href="https://helixmod.blogspot.com/search/label/geo-11">geo-11 tags</a> on HelixMod, and looked for releases that would _have_ to be 32-bit only.  ~~And, would you <a href="https://helixmod.blogspot.com/2023/10/silent-hill-2-directors-cut-dx11.html">look</a> at <a href="https://helixmod.blogspot.com/2023/10/silent-hill-3-dx11.html">that</a> (I have been meaning to replay the original _Silent Hill 2_, especially in 3D.  The remake with <a href="https://helixmod.blogspot.com/2024/11/silent-hill-2-dx11.html">masterotaku's fix</a> was incredible).~~  And <a href="https://helixmod.blogspot.com/2025/08/castlevania-lords-of-shadow-dx11.html">would you look at that</a> (thanks noraetic for pointing it out to me!).

_With the [geo11 v0.7.7 release](https://helixmod.blogspot.com/2022/06/announcing-new-geo-11-3d-driver.html), we get a copy of the x32 build right there_
</details>

---

> [!NOTE]
> All images in this readme (should) have been converted to be cross-eye friendly.  Though, viewing broken effects with yours eyes crossed may be another level of pain you're unaware of right now.  The original screenshots have matching filenames in `/orig` if you want to see how they looked before the eyes were swapped
>
> Conversions were done using [StereoPhoto Maker](https://stereo.jpn.org/eng/stphmkr/)

---

## Contents
- [Shadows](figuringthingsout_shadows.md)
  - Target various shadows by changing them to mono
- [Water](figuringthingsout_water.md)
  - Fix a reflection using a gut feeling
- [Toggles](figuringthingsout_toggles.md)
  - Learn how toggles work with geo-11
- [Texture Removal](figuringthingsout_textures.md)
  - Attempt to do direct file manipulation to fix our problems
- [Texture Atlas](figuringthingsout_textureatlas.md)
  - Learn how a texture atlas works, provided you can dump the texture to begin with
  - Watch the slowmotion trainwreck of learning that, despite that everything is setup _seemingly_ correct, it still doesn't work
- [A Box](figuringthingsout_abox.md)
  - Learn (again) how to use the `adjust_from_depth_buffer` function
---

While this fix is "done," it can still of course be improved. I hope someone maybe picks up what I've done here and continues, or at least thinks 'Hey, I can do better than this.' While the fix is one _glaring_ issue of the HUD problems, it was still a learning experience for me to see how various parts of a game work under the hood, and what can ultimatley be manipulated.

[Bus Insurance](./bus_insurance.md)

What to do next:
- [ ] See if a regex is possible for the ASM-only shaders, since they're _generally_ pretty similar
- [x] Reflections are broken if water is present
  - ~~There's also an issue that the left and right eye get different lighting within the water~~ _hoisted by my own petard_
- [ ] 2D/HUD elements are not at good depth, and need adjustment to be pushed in
  - [x] Border is set to be toggleable
  - [x] Create _some_ sort of workaround for the main game
  - [ ] Fix the overhead map view
- [ ] Make the pencil effect a toggle