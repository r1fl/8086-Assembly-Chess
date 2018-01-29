IDEAL
MODEL small
STACK 100h
P286

include 'graphics.inc'
include 'engine.inc'
include 'bmp.inc'
include 'io.inc'

DATASEG

; Error Messages

byUser@error	db	'Program closed by user.$'
blank@error		db	'Woops! nothing here.$'

; Directories

root@wd			db	'../', 0
pieces@wd		db	'assets', 0

; Selection

sourcePos@sel	dd	0
destPos@sel		dd	0
step@sel		dw	0

; Win Messages

white@win		db 'Game ended. White won!$'
black@win		db 'Game ended. Black won!$'

CODESEG

START:
	mov ax, @data
	mov ds, ax

	mov ah, 3Bh ; Set Working Dir
	mov dx, offset pieces@wd
	int 21h

	call initBoard@engine
	call initGraph@graphics

	mov al, 14h
	call cleanScreen@graphics
	call drawBoard@graphics

	mov di, 7
	mov si, 7
	mov al, [markColor@graphics]
	call markCube@graphics

	mov [markerCol@io], di
	mov [markerRow@io], si
	
	game@start:
		mov [step@sel], 0

		getSource@game:
			call getData@io

			push si
			push di
			inc [step@sel]

			push offset board@engine
			call getOffset@engine
			mov [sourceAddr@engine], bx

			call validateSource@engine
			jc invalid@game


		getDest@game:
			call getData@io

			push si
			push di
			inc [step@sel]

			push offset board@engine
			call getOffset@engine
			mov [destAddr@engine], bx

			call validateDest@engine
			jc invalid@game

		mov si, [sourceAddr@engine]
		mov di, [destAddr@engine]

		call validateMove@engine
		jc invalid@game

		cmp [byte di], 6
		je white_won@game

		cmp [byte di], -6
		je black_won@game

		call move@engine

		mov cx, [step@sel]
		updateBoard@game:
			pop di
			pop si

			push cx

			call getColor@graphics
			call drawCube@graphics

			pop cx
			loop updateBoard@game


		updateMark@game:
			mov di, [markerCol@io]
			mov si, [markerRow@io]

			mov al, [markColor@graphics]
			call markCube@graphics
		
		neg [turn@engine]
		jmp game@start

		invalid@game:
			add sp, [step@sel]
			add sp, [step@sel]

			mov di, [markerCol@io]
			mov si, [markerRow@io]

			mov al, 0Ch
			call markCube@graphics

			jmp game@start

		white_won@game:
			mov dx, offset white@win
			jmp exit_msg

		black_won@game:
			mov dx, offset black@win
			jmp exit_msg

	EXIT:
		mov dx, offset blank@error

	exit_msg:
		; Flush io buffer
		mov ah, 0Ch
		int 21h

		; Text Mode
		mov ax, 2h
		int 10h

		; Error Msg
		mov ah, 9h
		int 21h

		; Restore WD
		mov ah, 3Bh
		mov dx, offset root@wd
		int 21h

		; Terminate Program
		mov ax, 4c00h
		int 21h

END START