# RocketStats - Themes

You can create your own theme by drawing inspiration from existing themes.

Add **texts**, **shapes**, or **images**, only with a JSON file.

## Tree structure

To create a theme, start by creating a folder here, with the name you want.
Then in this folder, create a `config.json` file (it's a text file with a different file extension) that will contain all your stuff.

Example theme tree (fonts are not yet functional):
```
theme_folder
├─── fonts
│    └─── Arial.ttf
├─── images
│    └─── background.png
├─── config.json
└─── screenshot.png
```

## Config file

The file is in **JSON** format.
This format is rather easy to understand, and consists of just a text file storing information. As long as the syntax is respected, the theme will be taken into account.

### Building the theme

You can see an example of an empty theme file, we will add the different elements to it later:

```json
{
	"author":	"Arubinu42",
	"version":	"v1.0.0",
	"date":		"07/29/2019",
	"x":		0.0,
	"y":		0.0,
	"width":	576,
	"height":	40,
	"font":		["myfont.ttf", 42],
	"scale":	1.0,
	"opacity":	1.0,
	"elements": [
	]
}
```

You find the name of the author of the theme (you), the version and the date of this one for the basic information.
Now the basic settings:
 - `x` et `y`: position (adjustable from the interface then, these are the only ones to be in percentage from 0.0 to 1.0)
 - `width` and `height`: size (allows you to use percentages)
 - `font`: if you want to use a specific font (the name of the file in the `fonts` folder followed by the desired base size)
 - `scale`: zoom (adjustable from the interface)
 - `rotate`: rotation (adjustable from the interface)
 - `opacity`: transparency (more or less visible, adjustable from the interface)

The last **elements** will include your **texts**, **shapes**, and **images**. Add a new line after this one to separate the opening and closing brackets.
Now you will be able to add the elements which are presented below (these must be separated by a comma, example at the very bottom).

## Elements

Each element has its own parameters, here are a few:
 - `name`: is not important at this time, but plan to differentiate your elements for later releases
 - `value`: is often used for texts, and can include variables (example: `{{MMR}}`)
 - `align`: takes three values for the horizontal alignment (left, center, right)
 - `valign`: takes three values for the vertical alignment (top, middle, bottom)
 - `color`: this color is in RGB or RGBA format (the alpha channel is in percentage from 0.0 to 1.0)
 - `fill`: fillable color of a shap (works the same as `color`)
 - `stroke`: outline color of a shape (works the same as `color`, centered on the contour so protrudes inside depending on the thickness)
 - `rotate`: the rotation is added to the global rotation (in degrees from -180 to 180)
 - `opacity`: the opacity is added to the global opacity, but also of each color (percentage from 0.0 to 1.0)

The `name` parameter is not important at this time, but plan to differentiate your elements for later releases.

Some parameters accept calculations (to allow you to play with percentages).

The main ones to accept the calculations are (they are all integers):
  - `x`: horizontal position
  - `y`: vertical position
  - `width`: mainly used for the rectangle
  - `height`: mainly used for the rectangle
  - `x[0-9]` and `y[0-9]`: used for example for a triangle (x1, y1, x2, y2, etc...)
  - `radius`: percentages are based on width

So either they are presented directly with an integer, or they are surrounded by double quotes (which is used for strings), take example on the elements above.

### Text

As you can see, the text includes a variable preceded by a title. You can arrange it however you like.

Here are the variables that are accepted (each variable depends on the selected mode):
 - `GameMode`: the current game mode (Duel, Chaos, etc.)
 - `Rank`: the current rank (Gold III, Champion_II, etc...)
 - `Div`: the current division of your rank (Div. 4, Div .1)
 - `MMR`: your points in each game mode (allows you to calculate your rank)
 - `MMRChange`: the difference in MMR between two parties
 - `MMRCumulChange`: the cumulative total difference
 - `Win`: the number of games won
 - `Loss`: the number of games lost
 - `Streak`: the number of games won or lost in a row
 - `Demolition`: the number of times you destroy opponents
 - `Death`: the number of times you've been destroyed

```json
{
	"name":			"mmr",
	"type":			"text",
	"value":		"My MMR: {{MMR}}",
	"x":			170,
	"y":			20,
	"align":		"right",
	"valign":		"middle",
	"color":		[ 255, 255, 255 ],
	"scale":		1.2
}
```

### Image

Images are loaded from the `images` folder in the theme folder:

```json
{
	"name":			"background",
	"type":			"image",
	"file":			"background.png",
	"x":			0,
	"y":			0,
	"rotate":		45.0,
	"scale":		1.5
}
```

However, it also accepts `{{Rank}}` which will replace this element with the image corresponding to your rank:

```json
{
	"name":			"rank",
	"type":			"image",
	"file":			"{{Rank}}",
	"x":			27,
	"y":			20,
	"align":		"center",
	"valign":		"middle",
	"scale":		0.85
}
```

### Line

Lines work by placing the start point and the end point.

The `x1` and `y1` parameters place the first point in height and in width, `x2` and `y2` allow to do the same with the second point.

```json
{
	"name":			"separator1",
	"type":			"line",
	"x1":			"170px + 13px",
	"y1":			8,
	"x2":			"170px + 13px",
	"y2":			"100% - 8px",
	"color":		[ 255, 0, 0, 0.1 ],
	"scale":		2.5
}
```

### Triangle

Similar to lines, triangles are made up of points, but this time there are three.

```json
{
	"name":			"right_triangle",
	"type":			"triangle",
	"x1":			"100%",
	"y1":			0,
	"x2":			"100% + 40px",
	"y2":			0,
	"x3":			"100%",
	"y3":			"100%",
	"fill":			[ 0, 0, 0, 0.82 ],
	"stroke":		false
}
```

### Rectangle

In this example, the rectangle will take the entire size specified for the theme.

The `rounding` parameter applies a rounding on the corners of the rectangle.

```json
{
	"name":			"box",
	"type":			"rectangle",
	"x":			0,
	"y":			0,
	"width":		"100%",
	"height":		"100%",
	"rounding":		5,
	"fill":			false,
	"stroke":		[ 127, 127, 127, 0.5 ]
}
```

### Circle

Circles are special because they have edges, which allows you to make for example octagons.

The position is of course in the center of the circle.

```json
{
	"name":			"box",
	"type":			"rectangle",
	"x":			0,
	"y":			0,
	"radius":		20,
	"segments":		"100%",
	"fill":			[ 127, 127, 127, 0.5 ],
	"stroke":		[ 255, 0, 0, 1.0 ]
}
```

## What else

There are a few more parameters that can be used in some cases:
 - `sign`: takes as value the name of a variable (without the braces) and allows to add the positive sign on the specified variable
 - `chameleon`: same as `sign`, this one will change from green to red if the variable is positive or negative
