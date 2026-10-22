# <p align="center"><i><b>Phoenix Wright: Ace Attorney Trilogy</b></i></p>

_Ace Attorney_ is a series that I never played growing up when it came out. My friends had recommended it to me, but all I saw was "this must be some kind of legal game where I have to figure out logic puzzles with dialog or something weird," so I never bothered to try. I do vaguely remember a friend showing me the opening to the first game on their _DS-Xtreme_ flashcart when that was the hot new thing. Now here I am all these years later having played through the original trilogy as well as the Apollo Justice Collection

Inspired heavily by the work that masterotaku did for [Cuphead](https://helixmod.blogspot.com/2017/12/cuphead.html), I wanted to see how hard it would be to make an otherwise completely flat game 3D. And, surprisingly, it wasn't that hard here.

## Contents
- [Matching Texture Properties](./figuringthingsout_matchingtextures.md)
  - Filtering on various texture properties to force the game to do what we want
- [Matching More Specific Textures](figuringthingsout_matchingmorespecifictextures.md)
  - We can't always get what we want

### TODO
- [ ] Cutscenes with animations (with animations being a strong word) have textures that don't follow the patterns detailed here, so they will need to be captured separately
  - Cutscenes use composites like the characters for animations, and end up using the same texture hashes and setup, so they get blended into the general "character" override. Will need to decide if this is _ok enough_ or not
  - Similarly, courtroom animations (showing the victim/murderer in an overhead view) do the same thing
  - Both of these can be controlled with the character override key
- [ ] Courtroom chatter intermissions have different texture sizes, and will need to be dumped/adjusted like the others
- [ ] Witness Testimony fly-ins are above the text box in order, unsure if they should be pushed back
- [ ] Health bar is pushed in due to one of my overrides, and shouldn't be
- [x] Interactables appear as their own layer, and are annoying
  - Pushed into the same depth as the backgrounds
  - Included a commented out option if someone wants to "highlight" them more, but them not being at depth with the background is hard to look at in some cases
- [x] Magnifiying glass for investigation segments needs to be pushed in
  - Pushed in the same depth as characters