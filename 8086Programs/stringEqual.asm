assume CS:code,DS:data

data SEGMENT
	str1 DB 'string$'
	str2 DB 'strong$'
	str3 DB 'string$'
    len EQU 7h
 	msg1 DB 'equal$'
 	msg2 DB 'not equal$'
 	   
data ENDS         

code SEGMENT
start:
	MOV AX,data
	MOV DS,AX
	MOV ES,AX
	
	MOV CX,len
	CLD
	LEA SI,str1
	LEA DI,str2
	REPE CMPSB
	JNZ ne

	LEA DX,msg1
	MOV AH,09h
	INT 21h
	JMP ext
	
ne:
	LEA DX,msg2
	MOV AH,09h
	INT 21h
	
ext:
	MOV AH,4ch
	INT 21h	

code ENDS
END start