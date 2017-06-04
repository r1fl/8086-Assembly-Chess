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



proc move@engine
	mov ah, [byte si]

	mov [byte di], ah
	mov [byte si], 0

	ret
endp

