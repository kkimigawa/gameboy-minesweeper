# gameboy-minesweeper
Minesweeper on gameboy  
Build by GBDK-2020

![mine-title](https://user-images.githubusercontent.com/13421166/123121027-cc646a00-d47f-11eb-9cd5-ade711e286fc.png)

## Setup

### GBDK
Install GBDK 2020  
https://github.com/gbdk-2020/gbdk-2020

## Build
Make .gb binary
```bash
$ make
```

Cleanup project
```bash
$ make clean
```

## Tools

### Gameboy emulator
https://bgb.bircd.org/

### Tile and Map builder
https://github.com/gbdk-2020/GBTD_GBMB

### Pic2Tiles
http://budmelvin.com/dev/index.html  
Title bitmap to tiles

## How to play

### Title

|Key|Description|
|:-:|:-|
|Start|Start game.|

### Game

|Key|Description|
|:-:|:-|
|Up|Cursor move up. Repeat move when hold down.|
|Down|Cursor move down. Repeat move when hold down.|
|Left|Cursor move left. Repeat move when hold down.|
|Right|Cursor move right. Repeat move when hold down.|
|A|Open block. Auto open around when key down on bomb number and bomb number equals checked around block number.|
|B|Check block. Can't open block when checked block.|

### Game end
Game clear or gameover

|Key|Description|
|:-:|:-|
|Start|Return to title.|
