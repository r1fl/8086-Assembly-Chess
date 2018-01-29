CODESEG

proc validateMove
	mov si, [sourceAddr]

	xor ah, ah
	mov al, [si]

	cmp al, 0
	jge switchMoves

	neg al

	switchMoves:
		shl ax, 1
		mov bx, ax

		jmp [word movesTable + bx]

	movesTable:
		dw exit
		dw validatePawn
		dw validateKnight
		dw validateBishop
		dw validateRook
		dw validateQueen
		dw validateKing

	validatePawn:
		call pawnMoves
		jmp isValid

	validateKnight:
		call knightMoves
		jmp isValid

	validateBishop:
		call bishopMoves
		jmp isValid

	validateRook:
		mov ah, 2h
		mov dl, '4'
		
		int 21h
		jmp exit

	validateQueen:
		mov ah, 2h
		mov dl, '5'
		
		int 21h
		jmp exit

	validateKing:
		mov ah, 2h
		mov dl, '6'
		
		int 21h
		jmp exit

	isValid:
		mov di, [destAddr]

		isValidLoop:
			pop bx
			cmp bx, [word destAddr]

			je validMove
			loop isValid

		stc
		ret

	validMove:
		mov ax, cx
		mov dl, 2

		mul dl
		add sp, ax

		clc
		ret

endp

; #################################################

proc pawnMoves
	pop bx

	xor cx, cx

	mov ah, [turn]
	cmp ah, 0
	je whitePawn

	jmp blackPawn

	whitePawn:
		whitePawn1:
			mov di, si
			sub di, 8


			cmp [byte di], 0
			jg whitePawn3

			push di
			inc cx

		whitePawn2:
			mov ax, si
			sub ax, offset board

			mov dl, 8
			div dl

			cmp al, 6
			jne whitePawn3

			mov di, si
			sub di, 16


			cmp [byte di], 0
			jg whitePawn3

			push di
			inc cx

		whitePawn3:
			mov di, si
			sub di, 7


			cmp [byte di], 0
			jle whitePawn4

			push di
			inc cx

		whitePawn4:
			mov di, si
			sub di, 9


			cmp [byte di], 0
			jle pawnMovesExit

			push di
			inc cx


		jmp pawnMovesExit

	blackPawn:
		blackPawn1:
			mov di, si
			add di, 8


			cmp [byte di], 0
			jl blackPawn3

			push di
			inc cx

		blackPawn2:
			mov ax, si
			sub ax, offset board

			mov dl, 8
			div dl

			cmp al, 1
			jne blackPawn3

			mov di, si
			add di, 16


			cmp [byte di], 0
			jl blackPawn3

			push di
			inc cx

		blackPawn3:
			mov di, si
			add di, 7


			cmp [byte di], 0
			jge blackPawn4

			push di
			inc cx

		blackPawn4:
			mov di, si
			add di, 9


			cmp [byte di], 0
			jge pawnMovesExit

			push di
			inc cx

		jmp pawnMovesExit

	pawnMovesExit:
		push bx
		ret
endp

; #################################################

proc knightMoves
	pop bx

	xor cx, cx

	mov ah, [turn]
	cmp ah, 0
	je whiteKnight

	jmp blackKnight

	whiteKnight:
		; Up\Left
		whiteKnight1:
			mov di, si
			sub di, 17

			cmp [byte di], 0
			jl whiteKnight2

			push di
			inc cx

		; Up\Right
		whiteKnight2:
			mov di, si
			sub di, 15

			cmp [byte di], 0
			jl whiteKnight3

			push di
			inc cx

		; Down\Left
		whiteKnight3:
			mov di, si
			add di, 15

			cmp [byte di], 0
			jl whiteKnight4

			push di
			inc cx

		; Down\Right
		whiteKnight4:
			mov di, si
			add di, 17

			cmp [byte di], 0
			jl whiteKnight5

			push di
			inc cx

		; Left\Up
		whiteKnight5:
			mov di, si
			sub di, 10

			cmp [byte di], 0
			jl whiteKnight6

			push di
			inc cx

		; Right\Up
		whiteKnight6:
			mov di, si
			sub di, 6

			cmp [byte di], 0
			jl whiteKnight7

			push di
			inc cx

		; Left\Down
		whiteKnight7:
			mov di, si
			add di, 10

			cmp [byte di], 0
			jl whiteKnight8

			push di
			inc cx

		; Right\Down
		whiteKnight8:
			mov di, si
			add di, 6

			cmp [byte di], 0
			jl knightMovesExit

			push di
			inc cx

	blackKnight:
		; Up\Left
		blackKnight1:
			mov di, si
			sub di, 17

			cmp [byte di], 0
			jg blackKnight2

			push di
			inc cx

		; Up\Right
		blackKnight2:
			mov di, si
			sub di, 15

			cmp [byte di], 0
			jg blackKnight3

			push di
			inc cx

		; Down\Left
		blackKnight3:
			mov di, si
			add di, 15

			cmp [byte di], 0
			jg blackKnight4

			push di
			inc cx

		; Down\Right
		blackKnight4:
			mov di, si
			add di, 17

			cmp [byte di], 0
			jg blackKnight5

			push di
			inc cx

		; Left\Up
		blackKnight5:
			mov di, si
			sub di, 10

			cmp [byte di], 0
			jg blackKnight6

			push di
			inc cx

		; Right\Up
		blackKnight6:
			mov di, si
			sub di, 6

			cmp [byte di], 0
			jg blackKnight7

			push di
			inc cx

		; Left\Down
		blackKnight7:
			mov di, si
			add di, 10

			cmp [byte di], 0
			jg blackKnight8

			push di
			inc cx

		; Right\Down
		blackKnight8:
			mov di, si
			add di, 6

			cmp [byte di], 0
			jg knightMovesExit

			push di
			inc cx


	knightMovesExit:
		push bx
		ret

endp

; #################################################

proc bishopMoves
	pop bx
	xor dx, dx

	mov cx, 7

	; Top\Right
	bishopMove1:
		mov di, si

		mov ax, 8
		sub ax, cx
		add di, ax

		shl ax, 3 ; ax * 8
		sub di, ax

		push di
		inc dx

		loop bishopMove1

	push dx
	
	push bx
	ret

endp

; proc bishopMoves
; 	pop bx

; 	xor dx, dx

; 	mov ah, [turn]
; 	cmp ah, 0

; 	je whiteBishop
; 	jmp blackBishop

; 	whiteBishop:
; 		; Top\Right
; 		whiteBishop1:
; 			mov cx, 7
; 			xor ax, ax

; 			whiteBishop1loop:
; 				inc ax

; 				mov ax, di
; 				shl di, 3 ; dx = dx * 8
; 				neg di

; 				add di, ax
; 				add di, si

; 				push di
; 				inc dx

; 			push dx
				

; 				; mov ax, dx

; 				; add di, ax

; 				; cmp [byte di], 0
; 				; jg knightMovesExit

; 				; push di
; 				; inc cx	

; 		jmp bishopMovesExit


; 	blackBishop:
; 		jmp bishopMovesExit

; 	bishopMovesExit:
; 		push bx
; 		ret

; endp