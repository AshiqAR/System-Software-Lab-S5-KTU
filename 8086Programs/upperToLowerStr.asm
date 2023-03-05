assume CS:code ,DS:data

data SEGMENT

str1 DB 'CoMpUTeR$'
msg1 DB 'uppercase string: $'
msg2 DB '	converted : $'
len EQU 09h

data ENDS


code SEGMENT
start:
	MOV AX,data
	MOV DS,AX
	
	LEA DX,msg1
	MOV AH,09h
	INT 21h
	
	LEA DX,str1
	MOV AH,09h
	INT 21h
	
	LEA DX,msg2
	MOV AH,09h
	INT 21h
	   
	LEA SI,str1   
	CLD
l1:	CMP [SI],'A'
	JGE l2
	JMP lower
l2: CMP [SI],'Z'
	JLE upper
	JMP lower
	
upper:
	ADD [SI],20h
lower:
	INC SI
	LOOP l1

	LEA DX,str1
	MOV AH,09h
	INT 21h
	
	MOV AH,4ch
	INT 21h
	



code ENDS
END start
