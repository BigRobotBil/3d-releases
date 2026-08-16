# <p align="center"><i><b>Pac-Man Championship Edition 2</b></i></p>

This was one of the first games [I tried to get working eons ago](https://www.nvidia.com/en-us/geforce/forums/3d-vision/41/239325/span-classhighlightpacspan-span-classhighlightmans/) with 3D Vision. Thankfully, it just works out of the box. The only issue is that there's many sections where the FOV gets all wild due to the camera angles. This was an issue then (iirc) and it's still an issue now. We can mostly fix it by detecting specific textures and altering the 3D at those points. The big one is when Pac-Man goes "3D" himself when eating ghosts and the transition between mazes. The former we can automate, but the latter, eh, we might be boned.

## Contents
- [Conditional Texture](./figuringthingsout_conditionaltexture.md)
  - Only rendering shader adjustments if a texture is present