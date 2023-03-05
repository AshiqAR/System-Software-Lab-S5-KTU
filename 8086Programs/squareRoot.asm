data SEGMENT
start: 
	MOV AX,3000h
	MOV DS,AX
	
	MOV CX,000Ah
	MOV AX,0001h
	MOV BL,00h
	CMP CX,0000h
	JE equal
	INC BL
	
l1:
	CMP AX,CX
	JGE equal
	INC BL
	MOV AL,BL
	MOV AH,00h
	MUL BL
	JMP l1
	    
	
equal:	
	CMP AX,CX
	JE eq1
	DEC BL
eq1:
	MOV [4000h],BL
	
	MOV AH,4ch 
	INT 21h
	

data ENDS
END start