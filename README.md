# 8086-Assembly-Chess

#### File stracture

	|   bmp.inc 		# Framework for displaying bmp
	|   engine.inc 		# Board matrix, moves, validation
	|   graphics.inc 	# Display the board
	|   io.inc 			# Keyboard interrupts
	|   project.asm 	# Main file
	|
	+---assets 			# Game pieces; b = black; w = white
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
	|       VGA.gpl 		# Color scheme
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