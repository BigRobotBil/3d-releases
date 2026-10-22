# Matching More Specific Texture

While the filters setup in the previous markdown got us pretty far, there's still plenty of nitpicking we need to do to get the game "mostly ok" to "mostly good." Namely there's UI elements and other, miscellaneous textures that don't happen to get caught up in the filter (_or_ there's textures that get caught in the filter that need to be adjusted differently).

I am not going to go over _every_ example here, but some of the major ones that popped up. You can view the finished `d3dx.ini` that's included in the fix for all of them.

<sub>I want to say my notes in there are good, but, well, I am a bit biased</sub>

## Interactable Objects

- screenshot of the basement section, since I made a save there

This screen is hard to look at, and there's no real good way to mitigate other than to move these objects to the same depth as the background. Dumping this scene, we can see that the textures are all over the place for this, which isn't a good sign. However, if we press on anyway, we can apply:

```ini
[TextureOverride_Interactables]
match_type = Texture2D
match_format = R8G8B8A8_UNORM
match_bind_flags = -render_target -depth_stencil
filter_index = 30
```

And, everything looks fine there--

- screenshot of the movement dialog

Er, whelp. What we have to decide is if we want to hardcode for all the various interactable objects (warranting having to _play_ this entire three game trilogy again) or do the opposite: assuming everything but the menu system needs to be pushed in. Since I am from the future, I went with the latter:

```ini
[TextureOverride_Interactables]
match_type = Texture2D
match_width = !332
match_height = !294
match_format = R8G8B8A8_UNORM
match_bind_flags = -render_target -depth_stencil
filter_index = 30
```

That width/height matches the selection dialog texture, and now:

- screenshot of those looking good again

That's great, so that mea--

- screenshot of the item highlight being wrong

_This is gonna take awhile, huh_

What we're going to have to do from this point on is assign textures we come across that shouldn't be caught up in the filter a specific `filter_index` so they don't get pushed to a depth we don't want. So for example, the item highlight box:

```ini
[TextureOverride_ItemHighlight]
match_type = Texture2D
match_width = 450
match_height = 450
match_format = R8G8B8A8_UNORM
match_bind_flags = -render_target -depth_stencil
filter_index = 99
```