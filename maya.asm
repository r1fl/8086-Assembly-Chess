IDEAL
MODEL small
STACK 100h
DATASEG

filename db 'maya.bmp',0
filename2 db 'maya1.bmp',0
filename3 db 'maya2.bmp',0
filename4 db 'maya3.bmp',0
filehandle dw ?
Header db 54 dup (0)
Palette db 256*4 dup (0)
ScrLine db 320 dup (0)
ErrorMsg db 'Error', 13, 10,'$'

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
proc OpenFile2
; Open file
mov ah, 3Dh
xor al, al
mov dx, offset filename2
int 21h
jc openerror2
mov [filehandle], ax
ret
openerror2:
mov dx, offset ErrorMsg
mov ah, 9h
int 21h
ret
endp OpenFile2
proc OpenFile3
; Open file
mov ah, 3Dh
xor al, al
mov dx, offset filename3
int 21h
jc openerror3
mov [filehandle], ax
ret
openerror3:
mov dx, offset ErrorMsg
mov ah, 9h
int 21h
ret
endp OpenFile3
proc OpenFile4
; Open file
mov ah, 3Dh
xor al, al
mov dx, offset filename4
int 21h
jc openerror3
mov [filehandle], ax
ret
openerror4:
mov dx, offset ErrorMsg
mov ah, 9h
int 21h
ret
endp OpenFile4
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
cld ; Clear direction flag, for movsb
mov cx,320
mov si,offset ScrLine
rep movsb ; Copy line to the screen
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
start:
mov ax, @data
mov ds, ax
; Graphic mode
mov ax, 13h
int 10h
; Process BMP file
call OpenFile
call ReadHeader
call ReadPalette
call CopyPal
call CopyBitmap
; Wait for key press
mov ah,1
int 21h
call OpenFile2
call ReadHeader
call ReadPalette
call CopyPal
call CopyBitmap
; Wait for key press
mov ah,1
int 21h
call OpenFile3
call ReadHeader
call ReadPalette
call CopyPal
call CopyBitmap
; Wait for key press
mov ah,1
int 21h
call OpenFile4
call ReadHeader
call ReadPalette
call CopyPal
call CopyBitmap
; Wait for key press
mov ah,1
int 21h
; Back to text mode
mov ah, 0
mov al, 2
int 10h
s1 db 's1.bmp' ,0
s2 db 's2.bmp' ,0
s3 db 's3.bmp' ,0
srart db 'start.bmp',0
p1 db '1.bmp',0
p2 db '2.bmp',0
p3 db '3.bmp',0
p4 db '4.bmp',0
p5 db '5.bmp',0
p6 db '6.bmp',0
p7 db '7.bmp',0
p8 db '8.bmp',0
p9 db '9.bmp',0
p10 db '10.bmp',0
p11 db '11.bmp',0
p12 db '12.bmp',0
p13 db '13.bmp',0
p14 db '14.bmp',0
picture1 dw 18 dup (start,s3 , p1, p2, p3, p4, p5, p6, p7, p8, p9, start, p10, p11, p12, p13, p14, start )
picture2 dw 18 dup (start,s2 , p14, p13, p12, p11, p10, start, p9, p8, p7, p6, p5, p1, p2, p3, p4, start )
picture3 dw 18 dup (start,s2 , p10, p11, p12, p13, p14, start, p1, p2, p3, p4, p5, p6, p7, p8, p9, start )
picture4 dw 18 dup (start,s1 , p5, p6, p7, p8, p9, start, p10, p11, p12, p13, p14, p1, p2, p3, p4, start )
picture5 dw 18 dup (start,s2 , p1, p2, p3, p4, p5, p6, p7, p8, p9, start, p10, p11, p12, p13, p14, start )
picture6 dw 18 dup (start,s3 , p10, p11, p12, p13, p14, start, p1, p2, p3, p4, p5, p6, p7, p8, p9, start )
picture7 dw 18 dup (start,s2 , p5, p6, p7, p8, p9, start, p10, p11, p12, p13, p14, p1, p2, p3, p4, start )
picture8 dw 18 dup (start,s1 , p14, p13, p12, p11, p10, start, p9, p8, p7, p6, p5, p1, p2, p3, p4, start )
openpicture1:
; Wait for key press
mov ah,1
int 21h
 ;check if there is a a new key in buffer
 cmp al, '1'
je opens1
proc openfile5
; Open file
mov ah, 3Dh
xor al, al
mov dx, offset won
int 21h
jc openerror5
mov [filehandle], ax
ret
openerror5:
mov dx, offset ErrorMsg
mov ah, 9h
int 21h
ret
endp opefile5
; Wait for key press
mov ah,1
int 21h
 ;check if there is a a new key in buffer
 cmp al, '9'
jmp exit
cmp al, '0'
je openpicture2
cmp al, '2'
je opens1
proc opefile6
; Open file
mov ah, 3Dh
xor al, al
mov dx, offset lose
int 21h
jc openerror6
mov [filehandle], ax
ret
openerror6:
mov dx, offset ErrorMsg
mov ah, 9h
int 21h
ret
endp Openfile6
; Wait for key press
mov ah,1
int 21h
 ;check if there is a a new key in buffer
 cmp al, '9'
jmp exit
cmp al, '0'
je openpicture2
jmp WaitForKey
exit:
mov ax, 4c00h
int 21h
END start