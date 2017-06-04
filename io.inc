DATASEG

buffer@io		db	0

; Marker

markerCol@io	dw	0
markerRow@io	dw	0

CODESEG


proc getData@io
	mov ah, 0h
	int 16h

	cmp ah, 20h
	ja undefinedKey@getData

	xor bh, bh
	mov bl, ah
	shl bx, 1

	jmp [word binds@io + bx]

	undefinedKey@getData:
		jmp getData@io

	binds@io:
	 	dw undefinedKey@getData 		 ; UNDEFINED
		dw quit@userAction				 ; Esc[1d]
		dw 15d dup(undefinedKey@getData) ; UNDEFINED
		dw markerUp@userAction 			 ; W[17d]
		dw 10d dup(undefinedKey@getData) ; UNDEFINED
		dw submit@userAction 			 ; Enter[28d]
		dw undefinedKey@getData 		 ; UNDEFINED
		dw markerLeft@userAction 		 ; A[30d]
		dw markerDown@userAction 		 ; S[31d]
		dw markerRight@userAction 		 ; D[32d]

endp



proc userAction
	quit@userAction:
		mov dx, offset byUser@error
		jmp exit_msg

	submit@userAction:
		ret

	markerUp@userAction:
		mov si, [markerRow@io]
		mov di, [markerCol@io]

		cmp si, 0d
		je exit@markerUp

		decRow@markerUp:
			call getColor@graphics
			call markCube@graphics

			dec si
			mov al, [markColor@graphics]
			call markCube@graphics

			mov [markerCol@io], di
			mov [markerRow@io], si

		exit@markerUp:
			jmp getData@io

	markerDown@userAction:
		mov si, [markerRow@io]
		mov di, [markerCol@io]

		cmp si, 7d
		je exit@markerDown

		incRow@markerDown:
			call getColor@graphics
			call markCube@graphics

			inc si
			mov al, [markColor@graphics]
			call markCube@graphics

			mov [markerCol@io], di
			mov [markerRow@io], si

		exit@markerDown:
			jmp getData@io

	markerRight@userAction:
		mov si, [markerRow@io]
		mov di, [markerCol@io]

		cmp di, 7d
		je incRow@markerRight

		incCol@markerRight:
			call getColor@graphics
			call markCube@graphics

			inc di
			mov al, [markColor@graphics]
			call markCube@graphics

			mov [markerCol@io], di
			jmp exit@markerRight

		incRow@markerRight:
			cmp si, 7d
			je exit@markerRight

			call getColor@graphics
			call markCube@graphics

			inc si
			xor di, di
			mov al, [markColor@graphics]
			call markCube@graphics

			mov [markerCol@io], di
			mov [markerRow@io], si
			jmp exit@markerRight

		exit@markerRight:
			jmp getData@io

	markerLeft@userAction:
		mov si, [markerRow@io]
		mov di, [markerCol@io]

		cmp di, 0d
		je decRow@markerLeft

		decCol@markerLeft:
			call getColor@graphics
			call markCube@graphics

			dec di
			mov al, [markColor@graphics]
			call markCube@graphics

			mov [markerCol@io], di
			jmp exit@markerLeft

		decRow@markerLeft:
			cmp si, 0d
			je exit@markerLeft
			
			call getColor@graphics
			call markCube@graphics

			dec si
			mov di, 7d
			mov al, [markColor@graphics]
			call markCube@graphics

			mov [markerCol@io], di
			mov [markerRow@io], si
			jmp exit@markerLeft

		exit@markerLeft:
			jmp getData@io

endp