# RocketStats

RocketStats is a Plugin working with bakkesmod, allowing you to display session information (MMR / Win and losses, streak) in game and/or in OBS.

## Installation

### Prerequisites
First, you'll need to install [Bakkesmod](https://www.bakkesmod.com/)

### Installing
In game, **press F2**, open the **plugins tab**, open the **plugin manager**, fill the box on the right with **30** and press **"Install By Id"**

## Overlay
RocketStats is provided with 2 types of overlay, one in-game, and one designed for streamers in OBS.

### In Game Overlay
![In Game Overlay](https://media.discordapp.net/attachments/681760010392436836/764021965488521246/unknown.png)

This is the In-Game overlay, rank image is dynamic, giving Rank, Division, MMR, MMR Changed, Win, Losses, and Current Streak. You can edit the images that are displayed in the in-game Overlay by changing them in **%appdata%\bakkesmod\bakkesmod\RocketStats\RocketStats_images**.

File used are:
- loose.png (for the red cross)
- win.png (for the trophy)
- crown.png (for the medal, used to be a crown)
- All the rank image, but keep their name as is or it will break the plugin

### OBS Overlay
![OBS Overlay](https://media.discordapp.net/attachments/593431328209371170/593803857448927232/tweet1.png)

This is an example of the OBS Overlay, you can display information on your stream and style it your way using custom video and font.

#### Installation
You can find the example background video by [Rimey](https://twitter.com/Rimey_) here : [Download link](https://drive.google.com/file/d/15ye_Iq-1lK_dkQKQvk_Ia5EwbTNEiViG/view?usp=sharing)

The font used for this overlay is [Azonix Regular](https://www.dafont.com/azonix.font)

Make a "media source" check "Local file" and point to where you stored the overlay video.

Keep in mind that the provided overlay is an example of what you can do, let your imagination create the overlay you love ! ;)

To display data such as win, loose, streak and MMRChange, make a "Text" source and select "Read from a file".

All the available data are gathered in text files which are located in the folder **%appdata%\bakkesmod\bakkesmod\RocketStats**.

![RocketStats_folder](https://cdn.discordapp.com/attachments/681760010392436836/764024258510454794/JIbl4j.png)

To display the image of your rank you need to make a "Browser" source and configure it like this:

![Rank](https://cdn.discordapp.com/attachments/681760010392436836/764024258443477002/wzE_RR.png)

The file is in **bakkesmod\RocketStats\RocketStats_images** and its name is "rank.html"

You can also animate your stream while boosting !

![BoostGif](https://cdn.discordapp.com/attachments/593431328209371170/600786830341832854/M1q6g5.gif)

Make a Browser source:

![Boost](https://cdn.discordapp.com/attachments/681760010392436836/764024263471923210/FkrpCU.png)

The file is in **bakkesmod\RocketStats\RocketStats_images** and its name is "boost.html"

You can change the logo displayed to put yours, you need two videos in the format ".webm" one named "boost.webm" and the other "noboost.webm".

## Community & Thanks :)

You can come and ask your questions or discuss with the community in our [discord](https://discord.gg/weBCBE4).

Thanks to all the people who helped us during the developpement

- [Maylie](https://www.twitch.tv/Maylie_tv) for ideas and support
- [Ekon](https://www.twitch.tv/ekonrl) for tests
- [Fuury](https://www.twitch.tv/FuuRy_Off) for tests

### Development Team & Contributors
- [Lyliya](https://twitter.com/Lyliiya)
- [Nusa](https://twitter.com/NuSa_yt)
- Larsluph#7713
- Th3Ant#9411

The plugin is now Open Source, you can find the source code [here](https://github.com/Lyliya/RocketStats)

This plugin is provided for free, but if you like our work, you can support us at the following address: https://www.paypal.me/rocketstats or by sending BTC (only BTC) at 19qWGhpFTc5E9t9gvBYRyNK5ybdR8BioyK
