# 8086-Assembly-Chess

#### Table of Contents

* [Introduction](#introduction)
* [Getting Started](#getting-started)
	* [Dependencies](#dependencies)
	* [Building from Source](#building-from-source)
	* [Playing the game](#playing-the-game)
* [File tree](#file-tree)

#### Introduction

Chess game written in Assembly

[![game screenshot](https://i.imgur.com/cYwtXcp.png)](https://imgur.com/YIadbsH)


Getting started
---------------

#### Dependencies

* 8086 16bit Emulator ([Dosbox](https://www.dosbox.com/))
* A compiler with 16bit support ([Tasm](https://drive.google.com/file/d/1pwyM8Pnza5dO_Zh7tBEKYHQxOG0kfmZt/view?usp=sharing))


#### Building from source

To download the source files type the following command in terminal:

	$ git clone https://github.com/itamarx22/8086-Assembly-Chess

Afterwards you should have a folder 8086-Assembly-Chess somewhere in your pc.  
To get there type the following commands in the dosbox terminal:

	> mount <disk> <disk>:/
	> cd <path>/8086-Assembly-Chess

Finally compile the project using tasm and tlink with these commands:

	> tasm /zi /m project.asm
	> tlink /v project.obj


#### Playing the game

1. Change your current directory to 8086-Assembly chess as instructed in the building from source section.
2. Run project.exe

IMPORTANT: make sure the assets folder is in the same directory as the executable files in order for the game to run properly.

Hit w, a, s, d to move the cursor and enter to lock it in place.

#### File tree

	|   bmp.inc 		# Framework for displaying bmp
	|   engine.inc 		# Board matrix, moves, validation
	|   graphics.inc 	# Display the board
	|   io.inc  		# Keyboard interrupts
	|   project.asm 	# Main file
	|
	+---assets 		# Game pieces; b = black; w = white
	|   |   bBishop.bmp
	|   |   bKing.bmp
	|   |   bKnight.bmp
	|   |   bPawn.bmp
	|   |   bQueen.bmp
	|   |   bRook.bmp
	|   |   wBishop.bmp
	|   |   wKing.bmp
	|   |   wKnight.bmp
	|   |   wPawn.bmp
	|   |   wQueen.bmp
	|   |   wRook.bmp
	|   |
	|   \---svg 
	|           blackBishop.svg
	|           blackKing.svg
	|           blackKnight.svg
	|           blackPawn.svg
	|           blackQueen.svg
	|           blackRook.svg
	|           whiteBishop.svg
	|           whiteKing.svg
	|           whiteKnight.svg
	|           whitePawn.svg
	|           whiteQueen.svg
	|           whiteRook.svg
	|
	+---docs
	|       docs.txt
	|       VGA.gpl 	# Color scheme
	|       VGAAlpha.gpl 	# Color scheme w\ alpha
	|
	\---release
	    |   PROJECT.EXE
	    |   TEXT.EXE
	    |
	    \---pieces
	        |   bBishop.bmp
	        |   bg.bmp
	        |   bKing.bmp
	        |   bKnight.bmp
	        |   bPawn.bmp
	        |   bQueen.bmp
	        |   bRook.bmp
	        |   PROJECT.TR
	        |   TDCONFIG.TD
	        |   wBishop.bmp
	        |   wKing.bmp
	        |   wKnight.bmp
	        |   wPawn.bmp
	        |   wQueen.bmp
	        |   wRook.bmp
	        |
	        \---svg
	                blackBishop.svg
	                blackKing.svg
	                blackKnight.svg
	                blackPawn.svg
	                blackQueen.svg
	                blackRook.svg
	                whiteBishop.svg
	                whiteKing.svg
	                whiteKnight.svg
	                whitePawn.svg
	                whiteQueen.svg
	                whiteRook.svg
