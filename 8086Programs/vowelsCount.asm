assume CS:code,DS:data

data SEGMENT
	str DB 'AEashiq$'
	msg1 DB 13,10,'string : $'
	msg2 DB 13,10, 'Number of Vowels : $'
	len EQU 8h
data ENDS         

code SEGMENT
start:	
	MOV AX,data
	MOV DS,AX
	
	CLD    
	XOR BX,BX
	MOV CX,len
	LEA SI,str
	
l1:
	CMP [SI],'a'
	JE vow

	CMP [SI],'e'
	JE vow
	
	CMP [SI],'i'
	JE vow
	
	CMP [SI],'o'
	JE vow
	
	CMP [SI],'u'
	JE vow
	
	CMP [SI],'A'
	JE vow
	
	CMP [SI],'E'
	JE vow

	CMP [SI],'I'
	JE vow
	
	CMP [SI],'O'
	JE vow
	
	CMP [SI],'U'
	JE vow

	JMP con  
	
vow:
	INC BX
	
con:
	INC SI
	LOOP l1

	ADD BL,30h
	ADD BH,30h
	
	LEA DX,msg1
	MOV AH,09h
	INT 21h
	
	LEA DX,str
	MOV AH,09h
	INT 21h
	
	LEA DX,msg2
	MOV AH,09h
	int 21h
	
	MOV DX,BX
	MOV AH,02h
	INT 21h
	
	MOV AH,4ch
	INT 21h
	
	

code ENDS
END start