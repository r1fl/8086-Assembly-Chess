DATASEG

; White Pieces

whitePawn@graphics		db	'wPawn.bmp',0
whiteKnight@graphics	db	'wKnight.bmp',0
whiteBishop@graphics	db	'wBishop.bmp',0
whiteRook@graphics		db	'wRook.bmp',0
whiteQueen@graphics		db	'wQueen.bmp',0
whiteKing@graphics		db	'wKing.bmp',0

whiteTable@graphics		dw	0
						dw  whitePawn@graphics
						dw  whiteKnight@graphics
						dw  whiteBishop@graphics
						dw  whiteRook@graphics
						dw  whiteQueen@graphics
						dw  whiteKing@graphics

; Black Pieces

blackPawn@graphics		db	'bPawn.bmp',0
blackKnight@graphics	db	'bKnight.bmp',0
blackBishop@graphics	db	'bBishop.bmp',0
blackRook@graphics		db	'bRook.bmp',0
blackQueen@graphics		db	'bQueen.bmp',0
blackKing@graphics		db	'bKing.bmp',0

blackTable@graphics		dw	0
						dw  blackPawn@graphics
						dw  blackKnight@graphics
						dw  blackBishop@graphics
						dw  blackRook@graphics
						dw  blackQueen@graphics
						dw  blackKing@graphics


cubeColor@graphics	db 	28 dup(?), 31d, 2 dup(?), 28d
cubeSize@graphics	dw	75d

marginX@graphics	dw	3d
marginY@graphics	dw	1d

whiteCube@graphics	db	31d
blackCube@graphics	db	28d

markColor@graphics	db	33h

CODESEG

proc initGraph@graphics
	mov ax, 4F02h
	mov bx, 105h ; 1024x768
	int 10h

	ret
endp



proc drawBoard@graphics
	mov al, 31d

	xor di, di
	loopX@printBoard:
		mov bx, offset cubeColor@graphics
		add bl, al
		mov al, [byte bx]

		xor si, si
		loopY@printBoard:
			mov bx, offset cubeColor@graphics
			add bl, al
			mov al, [byte bx]

			drawCube@printBoard:
				call drawCube@graphics

				inc si
				cmp si, 8
				jne loopY@printBoard

		inc di
		cmp di, 8
		jne loopX@printBoard

	ret
endp



proc drawCube@graphics
	push si
	push di

	add di, [marginX@graphics]
	add si, [marginY@graphics]

	mov ah, 0Ch

	mov cx, ax

	mov dx, [cubeSize@graphics]
	mov ax, si
	mul dx
	mov si, ax

	mov dx, [cubeSize@graphics]
	mov ax, di
	mul dx
	mov di, ax

	mov ax, cx

	mov cx, [cubeSize@graphics]
	loopX@drawCube:

		mov dx, [cubeSize@graphics]
		loopY@drawCube:
			add dx, si
			add cx, di

			int 10h

			sub dx, si
			sub cx, di

			cmp dx, 0
			dec dx
			jne loopY@drawCube

	loop loopX@drawCube

	pop di
	pop si

	mov [fileHeight@bmp], 76d
	mov [fileWidth@bmp], 76d

	mov bx, si
	shl bx, 3

	add bx, di
	add bx, offset board@engine

	mov ah, [bx]
	xor bh, bh
	cmp ah, 0
	je exit@drawCube
	jl whitePiece@drawCube

	blackPiece@drawCube:
		mov bl, ah
		shl bl, 1
		mov dx, [word blackTable@graphics + bx]
		call drawFile@bmp
		jmp exit@drawCube

	whitePiece@drawCube:
		neg ah
		mov bl, ah
		shl bl, 1
		mov dx, [word whiteTable@graphics + bx]
		call drawFile@bmp

	exit@drawCube:
		ret
endp



proc markCube@graphics
	push si
	push di

	add di, [marginX@graphics]
	add si, [marginY@graphics]

	mov ah, 0Ch
	xor bx, bx

	push ax

	mov dx, [cubeSize@graphics]
	mov ax, si
	mul dx
	mov si, ax

	mov dx, [cubeSize@graphics]
	mov ax, di
	mul dx
	mov di, ax

	pop ax

	; Top Line
	mov dx, si
	mov cx, [cubeSize@graphics]
	loop1@markCube:
		add cx, di
		int 10h

		inc dx
		int 10h

		inc dx
		int 10h
		sub cx, di
		dec dx
		dec dx

		loop loop1@markCube

	; Bottom Line
	mov dx, si
	add dx, 75d
	mov cx, [cubeSize@graphics]
	loop2@markCube:
		add cx, di
		int 10h

		dec dx
		int 10h
		sub cx, di
		inc dx

		loop loop2@markCube

	mov cx, di
	mov dx, [cubeSize@graphics]
	loop3@markCube:
		add dx, si
		int 10h

		inc cx
		int 10h

		sub dx, si	
		dec cx

		cmp dx, 0
		dec dx
		jne loop3@markCube

	mov cx, di
	add cx, 75d
	mov dx, [cubeSize@graphics]
	loop4@markCube:
		add dx, si
		int 10h

		dec cx
		int 10h

		sub dx, si	
		inc cx

		cmp dx, 0
		dec dx
		jne loop4@markCube

	pop di
	pop si
	
	ret
endp



proc getColor@graphics
		mov ax, si
		shr ax, 1

		jc oddRow@getColor

		evenRow@getColor:
			mov ax, si
			shl ax, 3
			add ax, di

			shr ax, 1
			jc blackCube@evenRow

			whiteCube@evenRow:
				mov al, [whiteCube@graphics]
				jmp exit@getColor

			blackCube@evenRow:
				mov al, [blackCube@graphics]
				jmp exit@getColor

		oddRow@getColor:
			mov ax, si
			shl ax, 3
			add ax, di

			shr ax, 1
			jnc blackCube@evenRow

			whiteCube@oddRow:
				mov al, [whiteCube@graphics]
				jmp exit@getColor

			blackCube@oddRow:
				mov al, [blackCube@graphics]
				jmp exit@getColor

		exit@getColor:
			ret
endp


proc cleanScreen@graphics
	mov ah, 0Ch

	mov cx, 1024d
	loopX@cleanBoard:

		mov dx, 768d
		loopY@cleanBoard:
			int 10h

			cmp dx, 0
			dec dx
			jne loopY@cleanBoard
			
	loop loopX@cleanBoard

	ret
endp