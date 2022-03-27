# RocketStats

__RocketStats__ is a Plugin working with __BakkesMod__, allowing you to display session information (MMR, win, loss, streak, eg.) __in game__ and/or __in OBS__.

![RocketStats_menu](screenshot.png)

### Prerequisites

First, you'll need to install [Bakkesmod](https://www.bakkesmod.com/) and make sure it's running.

### Installing

In game, __press F2__, open the __plugins tab__, open the __plugin manager__, fill the box on the right with __30__ and press "__Install By Id__"

### Access the menu

To open the menu, use the button to the left of the "__Play__" button.

But you can also do it with keyboard shortcuts.
To do this, go to the BakkesMod menu (__press F2__) called "__Bindings__".
Then click on __Add__, then on __None__ and press the key you want to use to show/hide the overlay or menu.

To finish, double-click on the first line of the list, type one of the commands below, before clicking twice on __Save__:
 - __All RocketStats__ (overlay and menu): `togglemenu rocketstats`
 - __Menu only__: `toggle cl_rocketstats_settings 0 1`

## Overlay

RocketStats is provided with 2 types of overlay:
 - __In-game__: Check out the [tutorial](RocketStats_themes) to modify or create a theme,
 - __OBS__: Designed for streamers (use the "__Open folder__" button in the menu).

We offer two solutions for OBS:
 - Media Source by __[Rimey](https://twitter.com/Rimey_)__: [download video](https://drive.google.com/file/d/15ye_Iq-1lK_dkQKQvk_Ia5EwbTNEiViG/view?usp=sharing), [download font](https://www.dafont.com/azonix.font)
 - Browser Source: [download and tutorial](https://github.com/Arubinu/Overlay4RocketStats)

#### OBS Overlay

![BoostGif](https://cdn.discordapp.com/attachments/593431328209371170/600786830341832854/M1q6g5.gif)

You can find "__rank.html__" and "__boost.html__" in "__RocketStats_images__" to show rank image as well as boost usage on OBS.

You can change the logo displayed to put yours, you need two videos in the format "__.webm__" one named "__boost.webm__" and the other "__noboost.webm__".

## Community & Thanks :)

You can come and ask your questions or discuss with the community in our [discord](https://discord.gg/weBCBE4).

Thanks to all the people who helped us during the development.

- [Maylie](https://www.twitch.tv/Maylie_tv) for ideas and support
- [Ekon](https://www.twitch.tv/ekonrl) for tests
- [Fuury](https://www.twitch.tv/FuuRy_Off) for tests

#### Development Team & Contributors

- [Lyliya](https://twitter.com/Lyliiya)
- [Nusa](https://twitter.com/NuSa_yt)
- [Arubinu42](https://www.twitch.tv/arubinu42)
- Larsluph#7713
- Th3Ant#9411

The plugin is now Open Source, you can find the source code [here](https://github.com/Lyliya/RocketStats)

This plugin is provided for free, but if you like our work, you can support us at the following address: https://www.paypal.me/rocketstats or by sending BTC (only BTC) at _19qWGhpFTc5E9t9gvBYRyNK5ybdR8BioyK_
