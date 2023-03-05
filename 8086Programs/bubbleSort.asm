assume CS:code, DS:data

data SEGMENT

	list DB 12h,05h,03h,56h,34h,09h
	len EQU 06h

data ENDS   

code SEGMENT 
start:
	MOV AX,data
	MOV DS,AX
	MOV CX,len-1
	
l1:
	LEA SI,list
	MOV BX,CX
l2:
	MOV AH,[SI]
	CMP AH,[SI+1]
	JL less
	MOV AL,[SI+1]
	MOV [SI],AL
	MOV [SI+1],AH
	
less:
	INC SI
	DEC BX
	JNZ l2
	
	LOOP l1      
	
	MOV AH,4ch
	INT 21h

code ENDS
END start