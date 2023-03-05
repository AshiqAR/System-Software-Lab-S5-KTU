assume CS:code, DS:data

data SEGMENT

	list DB 12h,05h,03h,56h,34h,09h
	len EQU 06h
	msg DB 'The second largest element : $'

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
	JG great
	MOV AL,[SI+1]
	MOV [SI],AL
	MOV [SI+1],AH
		
great:
	INC SI
	DEC BX
	JNZ l2
	
	LOOP l1      
	       
	MOV SI,OFFSET list
	MOV AL,[SI]
	MOV CX,len
lop:
	CMP AL,[SI]
	JG ext
	INC SI
	LOOP lop
 
ext: 
	MOV AL,[SI]
	MOV BL,AL
	AND BL,0fh
	
	MOV BH,AL
	AND BH,0f0h 
	SHR BH,04h
	
	ADD BX,3030h  
	
	LEA DX,msg
	MOV AH,09h
	INT 21h
	
	MOV DL,BH
	MOV AH,02h
	INT 21h
	
	MOV DL,BL
	MOV AH,02h
	INT 21h
	
	
	MOV AH,4ch
	INT 21h

code ENDS
END start