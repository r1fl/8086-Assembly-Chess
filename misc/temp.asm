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