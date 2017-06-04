DATASEG

filename	db	'wPawn.bmp',0
filehandle	dw	?
Header		db	54 dup(0)
Palette		db	256*4 dup(0)
ScrLine		db  320 dup(0)
ErrorMsg	db	'error!!!$'

CODESEG

proc OpenFile
	; Open file

	mov ah, 3Dh
	xor al, al
	mov dx, offset filename
	int 21h
	jc openerror
	mov [filehandle], ax

	ret

	openerror:
		mov dx, offset ErrorMsg
		mov ah, 9h
		int 21h
		ret
endp OpenFile


proc ReadHeader
	; Read BMP file header, 54 bytes
	mov ah,3fh
	mov bx, [filehandle]
	mov cx,54
	mov dx,offset Header
	int 21h
	ret
endp ReadHeader


proc ReadPalette
	; Read BMP file color palette, 256 colors * 4 bytes (400h)
	mov ah,3fh
	mov cx,400h
	mov dx,offset Palette
	int 21h
	ret
endp ReadPalette



proc CopyPal
	; Copy the colors palette to the video memory
	; The number of the first color should be sent to port 3C8h
	; The palette is sent to port 3C9h
	mov si,offset Palette
	mov cx,256
	mov dx,3C8h
	mov al,0
	; Copy starting color to port 3C8h
	out dx,al
	; Copy palette itself to port 3C9h
	inc dx
	PalLoop:
		; Note: Colors in a BMP file are saved as BGR values rather than RGB.
		mov al,[si+2] ; Get red value.
		shr al,2 ; Max. is 255, but video palette maximal
		; value is 63. Therefore dividing by 4.
		out dx,al ; Send it.
		mov al,[si+1] ; Get green value.
		shr al,2 
		out dx,al ; Send it.
		mov al,[si] ; Get blue value.
		shr al,2 
		out dx,al ; Send it.
		add si,4 ; Point to next color.
		; (There is a null chr. after every color.)

		loop PalLoop
	ret
endp CopyPal



proc CopyBitmap
	; BMP graphics are saved upside-down.
	; Read the graphic line by line (200 lines in VGA format),
	; displaying the lines from bottom to top.
	mov ax, 0A000h
	mov es, ax
	mov cx,200

	PrintBMPLoop:
		push cx
		; di = cx*320, point to the correct screen line
		mov di,cx
		shl cx,6
		shl di,8
		add di,cx
		; Read one line
		mov ah,3fh
		mov cx,320
		mov dx,offset ScrLine
		int 21h
		; Copy one line into video memory
		cld
		; Clear direction flag, for movsb
		mov cx,320
		mov si,offset ScrLine

		rep movsb
		; Copy line to the screen
		;rep movsb is same as the following code:
		;mov es:di, ds:si
		;inc si
		;inc di
		;dec cx
		;loop until cx=0
		pop cx
		loop PrintBMPLoop

	ret
endp CopyBitmap


; #############################################################
; ----------------------- 2 -----------------------------------
; #############################################################

DATASEG

fileName@bmp		db	'bPawn.bmp',0
fileHeight@bmp		dw	75d
fileWidth@bmp		dw	75d

errorMsg@bmp		db	'Could not open file, program terminated. ERROR.0$'

fileHandle@bmp		dw	0

rowBuffer@bmp		db	1024 dup(0)
headerBuffer@bmp	db	54 	dup(0)

CODESEG

proc loadFile@bmp
	call getHandle@bmp

	call gotoData@bmp
	call loadBitmap@bmp

	ret
endp



proc getHandle@bmp
	mov ax, 3D00h

	mov dx, offset fileName@bmp
	int 21h

	call isFileError@bmp
	mov [fileHandle@bmp], ax

	ret
endp


proc gotoHeader@bmp
	mov ax, 4200h
	mov bx, [fileHandle@bmp]
	xor cx, cx
	xor dx, dx

	int 21h
	call isFileError@bmp

	ret
endp



proc gotoData@bmp
	call gotoHeader@bmp

	mov ax, 3F00h
	mov cx, 54d
	mov dx, offset headerBuffer@bmp
	int 21h
	call isFileError@bmp

	mov bx, offset headerBuffer@bmp
	mov dx, [bx+10d]
	mov cx, [bx+12d]

	mov ax, 4200h
	mov bx, [fileHandle@bmp]
	int 21h

	ret
endp


proc loadBitmap@bmp	
	mov si, [fileHeight@bmp]
	loopY@loadBitmap:
		mov bx, [fileHandle@bmp]

		mov ah, 3Fh
		mov cx, [fileWidth@bmp]
		mov dx, offset rowBuffer@bmp
		int 21h

		mov di, [fileWidth@bmp]
		loopX@loadBitmap:
			mov bx, offset rowBuffer@bmp
			add bx, di

			mov al, [byte bx]

			mov ah, 0Ch
			xor bl, bl
			mov cx, di
			mov dx, si
			int 10h

			cmp di, 0
			dec di
			jne loopX@loadBitmap

		cmp si, 0
		dec si
		jne loopY@loadBitmap

	ret
endp



proc isFileError@bmp
	jc fileError@isFileError
	ret
	
	fileError@isFileError:
		mov ah, 9h
		mov dx, offset errorMsg@bmp
		int 21h

		mov ah, 2h
		mov dl, al
		add dl, 48d
		int 21h

		mov ax, 4c00h
		int 21h
endp

DATASEG

fileName@bmp		db	'bPawn.bmp',0
fileHeight@bmp		dw	75d
fileWidth@bmp		dw	75d

errorMsg@bmp		db	'Could not open file, program terminated. ERROR.0$'

fileHandle@bmp		dw	0

rowBuffer@bmp		db	1024 dup(0)
headerBuffer@bmp	db	54 	dup(0)

CODESEG

proc loadFile@bmp
	call getHandle@bmp

	call gotoData@bmp
	call loadBitmap@bmp

	ret
endp



proc getHandle@bmp
	mov ax, 3D00h

	mov dx, offset fileName@bmp
	int 21h

	call isFileError@bmp
	mov [fileHandle@bmp], ax

	ret
endp


proc gotoHeader@bmp
	mov ax, 4200h
	mov bx, [fileHandle@bmp]
	xor cx, cx
	xor dx, dx

	int 21h
	call isFileError@bmp

	ret
endp



proc gotoData@bmp
	call gotoHeader@bmp

	mov ax, 3F00h
	mov cx, 54d
	mov dx, offset headerBuffer@bmp
	int 21h
	call isFileError@bmp

	mov bx, offset headerBuffer@bmp
	mov dx, [bx+10d]
	mov cx, [bx+12d]

	mov ax, 4200h
	mov bx, [fileHandle@bmp]
	int 21h

	ret
endp


proc loadBitmap@bmp	
	mov si, [fileHeight@bmp]
	loopY@loadBitmap:
		mov bx, [fileHandle@bmp]

		mov ah, 3Fh
		mov cx, [fileWidth@bmp]
		mov dx, offset rowBuffer@bmp
		int 21h

		mov di, [fileWidth@bmp]
		loopX@loadBitmap:
			mov bx, offset rowBuffer@bmp
			add bx, di

			mov al, [byte bx]

			mov ah, 0Ch
			xor bl, bl
			mov cx, di
			mov dx, si
			int 10h

			cmp di, 0
			dec di
			jne loopX@loadBitmap

		cmp si, 0
		dec si
		jne loopY@loadBitmap

	ret
endp



proc isFileError@bmp
	jc fileError@isFileError
	ret
	
	fileError@isFileError:
		mov ah, 9h
		mov dx, offset errorMsg@bmp
		int 21h

		mov ah, 2h
		mov dl, al
		add dl, 48d
		int 21h

		mov ax, 4c00h
		int 21h
endp