# Death Star -- game files
### Nathaniel Yerage -- 10/4/26


I'm adding some new binary file formats into this engine, for all kinds of uses. For right now, I'm just doing image formats (plus the palette), 
but eventually, there'll be stuff for all kinds of game data. 

For these files, I'll use a common file header, denoting some info on the type of file, size, and other stuff. 

## Common Header (8 bytes)

| Field         | Size (bytes) | Description                        |
| ------------- | ------------ | ---------------------------------- |
| Magic numbers | 2 chars      | 'NY' always                        |
| Version       | 1            | for modifications                  |
| File type     | 1            | denotes data (tile,room,etc.)      |
| File size     | 4            | size of full file excluding header |


### Header values

The NYHeader (the above header) needs some specific values (that aren't self-explanatory) in order to work. 

**Magic numbers:** always 'NY'. Denotes that this file is, in fact, one of my own files. 
**Version:** stick to 0 for now, but if I mess with any of the data, I'll have a way to boot it out if I'm loading a depreciated file.
**File type:** denotes the specific type of file (see the next section for value), to clarify this is what I want to load (there'll also be file extensions, but yeah)
**File size:** the size (in bytes, I guess) of the file (minus the 8 byte header). Useful.


### The Types

As of right now, I have **six** file types sharing this header:  
    - Palettes
    - Tiles
    - Rooms
    - Tilemaps
    - Bigmaps
    - Regular images

**Palettes** consist of a list of up to 255 colors (8 bit unsigned int max, excluding 0 for no color). Users refer to the palette for
drawing tiles to the screen.  
    **type:** PL
    **extension:** .palette

**Tiles** are square (8x8 initially) images, with each pixel being a u8, referring to a palette index. 
    **type:** TL
    **extension:** .tile

**Rooms** are the tile layout of a level. Each "pixel" refers to a tile index (in a tilemap, see below). For now, these will be square
and 16x16 tiles, but later on this may change. The pixels, like tiles, will be u8s. 
    **type:** RM
    **extension:** .room

**Tilemaps** are a full "palette" of tiles, for use when drawing rooms. They store a group of tiles (up to 255, 0 means no tile), and 
are loaded into memory and used for quick access when loading/drawing a room, sprite, or object. (may split room tiles and sprites into separate tilemaps, not sure).
They have the same bpp as tiles, but a larger image size (many tiles).
    **type:** TM
    **extension:** .tilemap

**Bigmaps** are the room equivalent of tilemaps. They compile a bunch of separate rooms into one chunk of memory, and are stored in a buffer when loaded for quick access
when playing the game. 
    **type:** BM
    **extension:** .bigmap

**Images** are just any normal image, using the 16 bpp format, and are basically the same as the og .nymg format (with a few changes). 
    **type:** MG
    **extension:** .nymg


**Side note.** Palettes, tilemaps, and bigmaps are probably going to be loaded only once in a program, with the memory being allocated statically. You only need one of each.
Palettes may be an exception, but we'll see. 



## Type info headers

These headers -- there must be a better name -- have data specific to the individual type. After them, there's just the data. 

### Palette (2 bytes)
| count | 2            | number of colors in list |

This is the palette data header, which indicates how many colors follow. 


### Tile (4 bytes)
| format | 2            | 8x8, stuff like that  |
| flags  | 2            | user-defined flags    | 

Not really sure about this guy, but yeah? The format describes the type of tile it is, 
which I guess is already covered in the "version", but whatever. I'm not running outta bits here.  

The "flags" thing is user-defined, and I'll probably just set to 0 for now. Those will help with collision
stuff, so a "spike" tile could be denoted as something that kills ya, and a platform might allow you to jump through it. 


### Room (4 bytes)
| width  | 2            | width of the room (in tiles)  |
| height | 2            | height of the room (in tiles) |

For now, they'll all be 16x16, but that may change with the implementation of scrolling rooms. 


### Tilemap (2 bytes)
| tile count      | 2            | number of tiles in file |

This guy is basically the same as the palette, so yeah. Just the number (max 255) of tiles in the file. 
In the tilemap file, there will be both the pixel data and the tile metadata list, which are both of length count (the pixel data is count * 8 * 8, obviously)


### Bigmap (2 bytes)
| map count     | 2     | number of maps in the file    | 

This guy, gets iffy. If scrolling rooms make an appearance, this is gonna get pretty hairy. Idk how I'll do that, lol. 
Well, maybe I'll just add a lookup table of some kind? Works. That's a later problem anyway.


### Image (10 bytes)
| bpp       | 2     | bits per pixel    |
| width     | 4     | width in pixels   |
| height    | 4     | height in pixels  |

This is from the og .nymg format, which for some reason used 32 bit ints as width/height (probably bc I was doing big images, lol). So yeah, it's a tad
different. I also added a bits-per-pixel field. It'll usually be 16, but idk man, maybe I'll go nuts. 


## The Data

This is the easy part, and I'm tired. This is just a blob of data which actually refers to the pixels or colors or indices or whatever.  

Also, for **tilemaps**, there is also the metadata array, which comes **before** the pixel data. Yeah. 


## Closing thoughts

Idk how useful this file is, but it was useful to write. Follow this to a t, and hopefully I'll be fine. 
Make changes as needed, and maybe make it less scatterbrained. Lol. 

I had another thing, which I forget now :(. Porting .nymg tiles to .tile is gonna be a shitshow. Maybe..dont? Lol, idk. 

Oh! I remember now. The point of these files is to ease development. They won't be used in the final game, at least not really. 
Instead, the plan is to combine these files into one big binary file -- not sure of the name -- which will be made up of these guys. Like wads. 

A very similar idea to converting tiles into tilemaps. So...yeah. 


