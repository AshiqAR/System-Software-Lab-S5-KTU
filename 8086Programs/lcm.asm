	XOR AX,AX
	XOR BX,BX
	XOR CX,CX
	XOR DX,DX
	
	MOV CL,08h
	MOV DL,02h
	CMP CL,DL
	JG great
	JMP con
great:
	XCHG CX,DX

con:
	MOV BL,DL
l1:
	MOV AX,BX
	DIV CL
	CMP AH,00h
	JE found
	ADD BX,DX
	JMP l1
	
found:
	MOV [2000h],BX
	MOV AH,4ch
	INT 21h
