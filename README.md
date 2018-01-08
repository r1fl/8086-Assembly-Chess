# 8086-Assembly-Chess

#### Table of Contents

* [Introduction](#introduction)
* [Getting Started](#getting-started)
	* [Dependencies](#dependencies)
	* [Building from Source](#building-from-source)

#### Introduction

Getting started
---------------

#### Dependencies

* 8086 16bit Emulator ([Dosbox](https://www.dosbox.com/))
* A compiler with 16bit support ([Tasm](https://drive.google.com/file/d/1pwyM8Pnza5dO_Zh7tBEKYHQxOG0kfmZt/view?usp=sharing))


#### Building from source	

	$ git clone https://github.com/itamarx22/8086-Assembly-Chess
	$ dosbox

	> mount <disk> <disk>:/
	> cd <path>

	> tasm /zi project.asm
	> tlink /v project.obj


#### File stracture

	|   bmp.inc 		# Framework for displaying bmp
	|   engine.inc 		# Board matrix, moves, validation
	|   graphics.inc 	# Display the board
	|   io.inc  	# Keyboard interrupts
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
