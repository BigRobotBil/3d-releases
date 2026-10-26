# <p align="center"><i><b>Phoenix Wright: Ace Attorney Trilogy</b></i></p>

_Ace Attorney_ is a series that I never played growing up when it came out. My friends had recommended it to me, but all I saw was "this must be some kind of legal game where I have to figure out logic puzzles with dialog or something weird," so I never bothered to try (I don't think my friends knew what the term "visual novel" was to begin with, so they never really sold the gameplay to me, either). I do vaguely remember a friend showing me the opening to the first game on their _DS-Xtreme_ flashcart when that was the hot new thing. Now here I am all these years later, having played through the original trilogy as well as the Apollo Justice Collection. They're really wonderful games (aside from a few rough spots, my goodness), and I regret only playing them a few years ago.

This entire thing was inspired heavily by the work that masterotaku did for [Cuphead](https://helixmod.blogspot.com/2017/12/cuphead.html). I wanted to see how hard it would be to make an otherwise completely flat game 3D. And, surprisingly, it wasn't that hard here. _Tedious_ would be a better word for it, however.

---

> [!NOTE]
> All images captured for 3D viewing will have a yellow border due to having to use [SRLoom](https://github.com/effcol/SR-Loom) on my Samsung Odyssey monitor. The game does not play nice with geo-11's built in `simulated_reality` mode, unfortunately, and crashes
>
> Conversions were done using [StereoPhoto Maker](https://stereo.jpn.org/eng/stphmkr/)

---

## Contents
- [Matching Texture Properties](./figuringthingsout_matchingtextures.md)
  - Filtering on various texture properties to force the game to do what we want
- [Matching More Specific Textures](./figuringthingsout_matchingmorespecifictextures.md)
  - We can't always get what we want
- [Cutscenes](./figuringthingsout_cutscenes.md)
  - Special handling for cutscenes and cutscene accessories

## Info
Given the amount of specific overrides that I ended up having to make for this anyway, instead of infesting the primary `d3dx.ini` with them and making it harder than usual to get to, we'll say, "normal" settings and things, I elected to make a folder of `ini` files based on the specific thing they're targetting:
- `BackgroundLevelOverrides.ini`
  - Things that will be pushed furthest back
- `CharacterLevelOverrides.ini`
  - Things that will be in the mid-way point between screen level and the background level
- `SpecificObjectOverrides.ini`
  - Probably the largest of the bunch, but anything that gets caught in some filters (that are described in the markdowns linked below) that shouldn't be, or textures that need special handling
- `No3DTriggerOverrides.ini`
  - Stuff that, when it appears, should just completely kill the 3D effect

### TODO
- [x] Cutscenes with animations (with animations being a strong word) have textures that don't follow the patterns detailed here, so they will need to be captured separately
  - Cutscenes use composites like the characters for animations, and end up using the same texture hashes and setup, so they get blended into the general "character" override. Will need to decide if this is _ok enough_ or not
  - Similarly, courtroom animations (showing the victim/murderer in an overhead view) do the same thing
  - Both of these can be controlled with the character override key
    - Solution: Have a `toggle` to move the mid-level items to the same depth as the background
- [x] Courtroom chatter intermissions have different texture sizes, and will need to be dumped/adjusted like the others
  - Solution: Took the cheaper route and just dumped both hashes for the courtroom background, and made a specific override to adjust mid-level items to be the same as the background depth
- [x] Witness Testimony fly-ins are above the text box in order, unsure if they should be pushed back
  - These fly-ins function exactly the same as the character portraits, and with how I currently have things setup, can't be altered for a different depth
- [x] Health bar is pushed in due to one of my overrides, and shouldn't be
- [x] Interactables appear as their own layer, and are annoying
  - Pushed into the same depth as the backgrounds
  - Included a commented out option if someone wants to "highlight" them more, but them not being at depth with the background is hard to look at in some cases
- [x] Magnifiying glass for investigation segments needs to be pushed in
  - Pushed in the same depth as the background