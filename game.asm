IDEAL
MODEL small
STACK 100h

include 'moves.asm'

DATASEG

; @Input_Vars

prompt		db	10, '>>$'

sourcePosBuff	db	3, 4 dup (?)
destPosBuff	db	3, 4 dup (?)

; @Core_Vars

board	db	64 dup(0)
turn	db	0b

sourceAddr	dw	?
destAddr	dw	?

; @Txt_Vars

cursorSave	db	27d,'[s$'
cursorRestore	db	27d,'[u$'

lineErase	db	80 dup(' '), '$'

titleMsg	db	'~Chess', 10, '$'
helpMsg		db	"* Help Menu *", 10, 10, '$'

whiteTurn	db	"* Blue's Move *", 10, 10, '$'
blackTurn	db	"* Red's Move *", 10, 10, '$'

moveMsg		db	27d,'[s', 10, "It's your move. Type '?' for options.", 10, '>>$'
invalidMoveMsg	db	27d,'[u', 10, "Invalid move! Please try again.", 10, '>>   ',27d,'[3D$'


CODESEG

start:
	mov ax, @data
	mov ds, ax

	mov bx, 0A000h
	mov es, bx

	call initBoard

	textGame:
		mov ax, 4F02h
		mov bx, 100h
		int 10h

		mov ah, 9h
		mov dx, offset titleMsg
		int 21h

		cmp [turn], 1b
		je black

		white:
			mov ah, 9h
			mov dx, offset whiteTurn
			int 21h

			jmp colorSwitchEnd

		black:
			mov ah, 9h
			mov dx, offset blackTurn
			int 21h

		colorSwitchEnd:
			call printBoard

			mov ah, 9h
			mov dx, offset moveMsg
			int 21h

			call promptMove
			call initMove

			jmp textGame

	graphicMode:
		mov ax, 4F02h
		mov bx, 105h ; 1024x768
		int 10h

		call drwBlanks
		call drwBoard
		jmp exit


exit:
	mov ax, 4c00h
	int 21h

; @Core_Procs:

proc initBoard
	mov cx, 64
	cleanBoard:
		mov ax, cx
		dec ax

		mov bx, offset board
		add bx, ax
		mov [byte bx], 0

		loop cleanBoard

	mov cx, 8
	initPawns:
		mov ax, cx
		dec ax

		mov bx, offset board
		add bx, ax

		add bx, 8
		mov [byte bx], 1

		add bx, 40
		mov [byte bx], -1

		loop initPawns

	initRooks:
		mov bx, offset board

		mov [byte bx], 4
		mov [byte bx+7], 4

		add bx, 56

		mov [byte bx], -4
		mov [byte bx+7], -4

	initKnights:
		mov bx, offset board

		mov [byte bx+1], 2
		mov [byte bx+6], 2

		add bx, 56

		mov [byte bx+1], -2
		mov [byte bx+6], -2

	initBishops:
		mov bx, offset board

		mov [byte bx+2], 3
		mov [byte bx+5], 3

		add bx, 56

		mov [byte bx+2], -3
		mov [byte bx+5], -3

	initQueens:
		mov bx, offset board

		mov [byte bx+3], 5

		add bx, 56

		mov [byte bx+3], -5

	initKings:
		mov bx, offset board

		mov [byte bx+4], 6

		add bx, 56

		mov [byte bx+4], -6


	ret
endp

proc cordAddress
	; Col

	xor dx, dx

	mov dl, [bx+1]
	sub dl, 97

	; Row

	xor ax, ax

	mov al, [bx]

	sub ax, 48
	sub ax, 8
	neg ax

	mov dh, 8
	mul dh

	; Calc the offset

	xor dh, dh
	mov bx, offset board

	add bx, dx
	add bx, ax

	ret
endp

proc initMove

	mov si, [sourceAddr]
	mov di, [destAddr]

	mov ah, [si]
	mov [byte si], 0

	mov [di], ah

	mov al, [turn]
	xor al, 1
	mov [turn], al

	ret

endp

proc validateDest
	mov bx, [destAddr]
	
	mov ah, [turn]
	cmp ah, 1b
	je whiteDest

	; White's Move

	blackDest:
		mov ah, [bx]
		cmp ah, 0
		jl invalidDest

		call validateMove
		jc invalidDest

		jmp validateDestExit

	; Black's Move

	whiteDest:
		mov ah, [bx]
		cmp ah, 0
		jg invalidDest

		call validateMove
		jc invalidDest

		jmp validateDestExit

	invalidDest:
		jmp printInvalidMove

	validateDestExit:
		ret
endp

proc validateSource
	mov bx, [sourceAddr]
	mov al, [turn]

	cmp al, 1b
	je blackSource

	whiteSource:
		mov ah, [bx]
		cmp ah, 0
		jge printInvalidMove

		ret

	blackSource:
		mov ah, [bx]
		cmp ah, 0
		jle printInvalidMove

		ret
endp

; @Input_Procs (txt):

proc promptMove
	mov ah, 0Ah
	mov dx, offset sourcePosBuff
	int 21h

	call validateInput

	mov bx, dx
	add bx, 2

	call cordAddress
	mov [sourceAddr], bx

	call validateSource

	; Prompt Move

	mov ah, 9h
	mov dx, offset prompt
	int 21h

	; ** Dest Input

	mov ah, 0Ah
	mov dx, offset destPosBuff
	int 21h

	call validateInput

	mov bx, dx
	add bx, 2

	call cordAddress
	mov [destAddr], bx

	call validateDest

	ret
endp

proc validateInput
	mov bx, dx
	mov ax, [bx+2]

	cmp al, 33d
	je userInterrupt

	cmp ah, 33d
	je userInterrupt

	cmp al, 49d
	jb printInvalidMove

	cmp al, 56d
	ja printInvalidMove

	cmp ah, 97d
	jb printInvalidMove

	cmp ah, 104d
	ja printInvalidMove

	ret

	userInterrupt:
		mov ax, 4c00h
		int 21h

endp

; @Txt_Procs:

proc printInvalidMove
	mov ah, 9h
	mov dx, offset cursorRestore
	int 21h

	mov ah, 2h
	mov dl, 10
	int 21h

	mov ah, 9h
	mov dx, offset lineErase
	int 21h

	mov ah, 2h
	mov dl, 10
	int 21h

	mov ah, 9h
	mov dx, offset lineErase
	int 21h

	mov dx, offset invalidMoveMsg
	int 21h

	add sp, 2
	jmp promptMove

	ret
endp

proc printBoard
	mov dl, ' '
	mov ah, 2h
	int 21h
	int 21h

	mov cx, 8
	printCords:
		mov ah, 2h
		mov dl, ' '
		int 21h

		mov al, cl
		sub al, 8
		neg al
		add al, 97

		mov dl, al

		mov ah, 2h
		int 21h

		loop printCords

	mov ah, 2h
	mov dx, 10
	int 21h
	int 21h

	mov cx, 8
	printRow:
		; Save the current row and the offset

		mov ax, cx
		sub ax, 8
		neg ax

		push ax

		mov si, 8
		mul si
		mov si, ax
		add si, offset board

		; Print current row number

		mov dl, cl
		add dl, 48
		mov ah, 2h
		int 21h

		; Print Dash

		mov dl, ' '
		int 21h
		int 21h

		pop ax

		push cx
		mov cx, 8

		printCol:
			; Save the column
			mov ax, cx
			sub ax, 8
			neg ax

			; Calc the offset
			mov bx, si
			add bx, ax

			mov ax, [bx]
			call printPiece

			loop printCol


		; Print Dash

		mov dl, ' '
		int 21h
		int 21h

		; Print current row number

		pop cx

		mov dl, cl
		add dl, 48
		mov ah, 2h
		int 21h

		; New Line

		mov ah, 2h
		mov dx, 10
		int 21h

		loop printRow

	mov ah, 2h
	mov dx, 10
	int 21h

	mov dl, ' '
	mov ah, 2h
	int 21h
	int 21h

	mov cx, 8
	printCords1:
		mov ah, 2h
		mov dl, ' '
		int 21h

		mov al, cl
		sub al, 8
		neg al
		add al, 97

		mov dl, al

		mov ah, 2h
		int 21h

		loop printCords1

	mov ah, 2h
	mov dx, 10
	int 21h

	ret
endp

proc printPiece
		cmp al, 0

		jl negativePrint
		jg positivePrint

		zeroPrint:
			mov ah, 2h
			mov dl, 'x'
			int 21h

			mov dl, ' '
			int 21h

			ret


		positivePrint:
			mov ah, 0Eh
			add al, 48
			xor bh, bh
			mov bl, 12
			int 10h

			mov dx, ' '
			mov ah, 2h
			int 21h

			ret

		negativePrint:
			neg al

			mov ah, 0Eh
			add al, 48
			xor bh, bh
			mov bl, 9
			int 10h

			mov dx, ' '
			mov ah, 2h
			int 21h

			ret

endp

; @Graph_Procs

proc drwBlanks
	pop si

	mov ah, 0Ch
	mov al, 4
	xor bl, bl

	pop cx
	drwClsRow:
		mov dx, cx

		pop cx
		push cx

		drwClsCol:
			int 10h
			loop drwClsCol

		mov cx, dx
		loop drwClsRow

	pop cx

	push si
	ret
endp

proc drwBoard
endp

END start