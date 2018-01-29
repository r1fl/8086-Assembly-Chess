# 8086-Assembly-Chess-TEXTMODE

#### Table of Contents

* [Introduction](#introduction)
* [Getting Started](#getting-started)
	* [Dependencies](#dependencies)
	* [Building from Source](#building-from-source)

#### Introduction

Chess game written in Assembly

[![game screenshot](https://i.imgur.com/RnPbQdJ.png)](https://i.imgur.com/AKEmZx6.png)


Getting started
---------------

#### Dependencies

* 8086 16bit Emulator ([Dosbox](https://www.dosbox.com/))
* A compiler with 16bit support ([Tasm](https://drive.google.com/file/d/1pwyM8Pnza5dO_Zh7tBEKYHQxOG0kfmZt/view?usp=sharing))


#### Building from source

To download the source files type the following command in terminal:

	$ git clone https://github.com/itamarx22/8086-Assembly-Chess

Afterwords you should have a folder 8086-Assembly-Chess somewhere in your pc.  
To get there type the following commands in the dosbox terminal:

	> mount <disk> <disk>:/
	> cd <path>/8086-Assembly-Chess

Finally compile the project using tasm and tlink with these commands:

	> tasm /zi /m project.asm
	> tlink /v project.obj
