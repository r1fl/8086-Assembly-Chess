DATASEG

board@engine		db	64 dup(0)
turn@engine			db	-1d

sourceAddr@engine	dw	0
destAddr@engine		dw	0

CODESEG

proc initBoard@engine
	mov cx, 64
	cleanBoard:
		mov ax, cx
		dec ax

		mov bx, offset board@engine
		add bx, ax
		mov [byte bx], 0

		loop cleanBoard

	mov cx, 8
	initPawns:
		mov ax, cx
		dec ax

		mov bx, offset board@engine
		add bx, ax

		add bx, 8
		mov [byte bx], 1

		add bx, 40
		mov [byte bx], -1

		loop initPawns

	initRooks:
		mov bx, offset board@engine

		mov [byte bx], 4
		mov [byte bx+7], 4

		add bx, 56

		mov [byte bx], -4
		mov [byte bx+7], -4

	initKnights:
		mov bx, offset board@engine

		mov [byte bx+1], 2
		mov [byte bx+6], 2

		add bx, 56

		mov [byte bx+1], -2
		mov [byte bx+6], -2

	initBishops:
		mov bx, offset board@engine

		mov [byte bx+2], 3
		mov [byte bx+5], 3

		add bx, 56

		mov [byte bx+2], -3
		mov [byte bx+5], -3

	initQueens:
		mov bx, offset board@engine

		mov [byte bx+3], 5

		add bx, 56

		mov [byte bx+3], -5

	initKings:
		mov bx, offset board@engine

		mov [byte bx+4], 6

		add bx, 56

		mov [byte bx+4], -6


	ret
endp



proc getOffset@engine
	pop dx

	mov ax, si
	shl ax, 3
	add ax, di

	pop bx
	add bx, ax

	push dx
	ret
endp



proc validateSource@engine
	cmp [turn@engine], 1d
	je blackMove@validateSource

	whiteMove@validateSource:
		cmp [byte bx], 0
		jge invalidMove@validateSource

		jmp validMove@validateSource

	blackMove@validateSource:
		cmp [byte bx], 0
		jle invalidMove@validateSource

		jmp validMove@validateSource

	invalidMove@validateSource:
		stc
		ret

	validMove@validateSource:
		cli
		ret
endp



proc validateDest@engine
	cmp [turn@engine], 1d
	je blackMove@validateDest

	whiteMove@validateDest:
		cmp [byte bx], 0
		jl invalidMove@validateDest

		jmp validMove@validateDest

	blackMove@validateDest:
		cmp [byte bx], 0
		jg invalidMove@validateDest

		jmp validMove@validateDest

	invalidMove@validateDest:
		stc
		ret

	validMove@validateDest:
		cli
		ret
endp



proc validateMove@engine
	pusha

	xor ah, ah
	mov al, [si]

	cmp al, 0
	jg switchMoves@validateMove

	neg al

	switchMoves@validateMove:
		shl ax, 1
		mov bx, ax

		jmp [word jt@switchMoves + bx]

		jt@switchMoves:
			dw ?
			dw pawn@moves
			dw knight@moves
			dw bishop@moves
			dw rook@moves
			dw queen@moves
			dw king@moves


	moves@validateMove:
		pawn@moves:
			xor cx, cx

			cmp [byte si], 0
			jg black@pawn

			white@pawn:
				pawn1@white:
					mov bx, si
					sub bx, 8d

					cmp [byte bx], 0
					jne pawn2@white

					push bx
					inc cx

				pawn2@white:
					mov bx, offset board@engine
					add bx, 48d

					cmp si, bx
					jb pawn3@white

					mov bx, offset board@engine
					add bx, 55d

					cmp si, bx
					ja pawn3@white

					mov bx, si
					sub bx, 16d
					push bx
					inc cx

				pawn3@white:
					mov bx, si
					sub bx, 7d

					cmp [byte bx], 0
					je pawn4@white

					push bx
					inc cx

				pawn4@white:
					mov bx, si
					sub bx, 9d

					cmp [byte bx], 0
					je pawn5@white

					push bx
					inc cx

				pawn5@white:
					jmp isValid@validateMove

			black@pawn:
				pawn1@black:
					mov bx, si
					add bx, 8d

					cmp [byte bx], 0
					jne pawn2@black

					push bx
					inc cx

				pawn2@black:
					mov bx, offset board@engine
					add bx, 8d

					cmp si, bx
					jb pawn3@black

					mov bx, offset board@engine
					add bx, 15d

					cmp si, bx
					ja pawn3@black

					mov bx, si
					add bx, 16d

					push bx
					inc cx

				pawn3@black:
					mov bx, si
					add bx, 7d

					cmp [byte bx], 0
					je pawn4@black

					push bx
					inc cx

				pawn4@black:
					mov bx, si
					add bx, 9d

					cmp [byte bx], 0
					je pawn5@black

					push bx
					inc cx

				pawn5@black:
					jmp isValid@validateMove

		knight@moves:
			xor cx, cx

			knight1@knight:
				mov bx, si
				sub bx, 17d

				push bx
				inc cx

			knight2@knight:
				mov bx, si
				sub bx, 15d

				push bx
				inc cx

			knight3@knight:
				mov bx, si
				add bx, 15d

				push bx
				inc cx

			knight4@knight:
				mov bx, si
				add bx, 17d

				push bx
				inc cx

			knight5@knight:
				mov bx, si
				add bx, 6d

				push bx
				inc cx

			knight6@knight:
				mov bx, si
				sub bx, 10d

				push bx
				inc cx

			knight7@knight:
				mov bx, si
				add bx, 10d

				push bx
				inc cx

			knight8@knight:
				mov bx, si
				sub bx, 6d

				push bx
				inc cx

			knight9@knight:
				jmp isValid@validateMove

		bishop@moves:
			xor cx, cx

			bishop1@bishop:
				mov bx, si
				mov dx, 7d
				loopMoves@bishop1:
					sub bx, 8d
					dec bx

					push bx
					inc cx

					cmp [byte bx], 0
					jne bishop2@bishop

					cmp dx, 0
					dec dx
					jne loopMoves@bishop1

			bishop2@bishop:
				mov bx, si
				mov dx, 7d
				loopMoves@bishop2:
					sub bx, 8d
					inc bx

					push bx
					inc cx

					cmp [byte bx], 0
					jne bishop3@bishop

					cmp dx, 0
					dec dx
					jne loopMoves@bishop2

			bishop3@bishop:
				mov bx, si
				mov dx, 7d
				loopMoves@bishop3:
					add bx, 8d
					dec bx

					push bx
					inc cx

					cmp [byte bx], 0
					jne bishop4@bishop

					cmp dx, 0
					dec dx
					jne loopMoves@bishop3

			bishop4@bishop:
				mov bx, si
				mov dx, 7d
				loopMoves@bishop4:
					add bx, 8d
					inc bx

					push bx
					inc cx

					cmp [byte bx], 0
					jne bishop5@bishop

					cmp dx, 0
					dec dx
					jne loopMoves@bishop4

			bishop5@bishop:
				jmp isValid@validateMove

		rook@moves:
			xor cx, cx

			rook1@rook:
				mov bx, si
				mov dx, 7d
				loopMoves@rook1:
					sub bx, 8d

					push bx
					inc cx

					cmp [byte bx], 0
					jne rook2@rook

					cmp dx, 0
					dec dx
					jne loopMoves@rook1

			rook2@rook:
				mov bx, si
				mov dx, 7d
				loopMoves@rook2:
					add bx, 8d

					push bx
					inc cx

					cmp [byte bx], 0
					jne rook3@rook

					cmp dx, 0
					dec dx
					jne loopMoves@rook2

			rook3@rook:
				mov bx, si
				mov dx, 7d
				loopMoves@rook3:
					dec bx

					push bx
					inc cx

					cmp [byte bx], 0
					jne rook4@rook

					cmp dx, 0
					dec dx
					jne loopMoves@rook3

			rook4@rook:
				mov bx, si
				mov dx, 7d
				loopMoves@rook4:
					inc bx

					push bx
					inc cx

					cmp [byte bx], 0
					jne rook5@rook

					cmp dx, 0
					dec dx
					jne loopMoves@rook4

			rook5@rook:
				jmp isValid@validateMove

		queen@moves:
			xor cx, cx

			queen1@queen:
				mov bx, si
				mov dx, 7d
				loopMoves@queen1:
					sub bx, 8d
					dec bx

					push bx
					inc cx

					cmp [byte bx], 0
					jne queen2@queen

					cmp dx, 0
					dec dx
					jne loopMoves@queen1

			queen2@queen:
				mov bx, si
				mov dx, 7d
				loopMoves@queen2:
					sub bx, 8d
					inc bx

					push bx
					inc cx

					cmp [byte bx], 0
					jne queen3@queen

					cmp dx, 0
					dec dx
					jne loopMoves@queen2

			queen3@queen:
				mov bx, si
				mov dx, 7d
				loopMoves@queen3:
					add bx, 8d
					dec bx

					push bx
					inc cx

					cmp [byte bx], 0
					jne queen4@queen

					cmp dx, 0
					dec dx
					jne loopMoves@queen3

			queen4@queen:
				mov bx, si
				mov dx, 7d
				loopMoves@queen4:
					add bx, 8d
					inc bx

					push bx
					inc cx

					cmp [byte bx], 0
					jne queen5@queen

					cmp dx, 0
					dec dx
					jne loopMoves@queen4

			queen5@queen:
				mov bx, si
				mov dx, 7d
				loopMoves@queen5:
					sub bx, 8d

					push bx
					inc cx

					cmp [byte bx], 0
					jne queen6@queen

					cmp dx, 0
					dec dx
					jne loopMoves@queen5

			queen6@queen:
				mov bx, si
				mov dx, 7d
				loopMoves@queen6:
					add bx, 8d

					push bx
					inc cx

					cmp [byte bx], 0
					jne queen7@queen

					cmp dx, 0
					dec dx
					jne loopMoves@queen6

			queen7@queen:
				mov bx, si
				mov dx, 7d
				loopMoves@queen7:
					dec bx

					push bx
					inc cx

					cmp [byte bx], 0
					jne queen8@queen

					cmp dx, 0
					dec dx
					jne loopMoves@queen7

			queen8@queen:
				mov bx, si
				mov dx, 7d
				loopMoves@queen8:
					inc bx

					push bx
					inc cx

					cmp [byte bx], 0
					jne queen9@queen

					cmp dx, 0
					dec dx
					jne loopMoves@queen8

			queen9@queen:
				jmp isValid@validateMove

		king@moves:
			xor cx, cx

			king1@king:
				mov bx, si
				sub bx, 8d

				push bx
				inc cx

			king2@king:
				mov bx, si
				add bx, 8d

				push bx
				inc cx

			king3@king:
				mov bx, si
				dec bx

				push bx
				inc cx

			king4@king:
				mov bx, si
				inc bx

				push bx
				inc cx

			king5@king:
				mov bx, si
				sub bx, 9d

				push bx
				inc cx

			king6@king:
				mov bx, si
				sub bx, 7d

				push bx
				inc cx

			king7@king:
				mov bx, si
				add bx, 7d

				push bx
				inc cx

			king8@king:
				mov bx, si
				add bx, 9d

				push bx
				inc cx

			king9@king:
				jmp isValid@validateMove




	isValid@validateMove:
		cmp cx, 0
		je invalidMove@validateMove

		loopMoves@isValid:
			dec cx

			pop bx
			cmp bx, di
			je validMove@isValid

			cmp cx, 0
			jne loopMoves@isValid

		jmp invalidMove@validateMove

		validMove@isValid:
			add sp, cx
			add sp, cx
			jmp validMove@validateMove


	invalidMove@validateMove:
		popa
		stc
		ret

	validMove@validateMove:
		popa
		cli
		ret
endp


proc move@engine
	mov ah, [byte si]

	mov [byte di], ah
	mov [byte si], 0

	ret
endp

