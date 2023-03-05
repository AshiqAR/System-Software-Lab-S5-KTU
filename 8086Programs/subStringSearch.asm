assume CS:code,DS:data

data SEGMENT

str1 DB 'computer$'
str2 DB 'terr$'
len1 EQU 04h
len DB 09h  

msg1 DB 13,10,'String : $'
msg2 DB 13,10,'substring to be searched: $' 

msg3 DB 13,10,'is a substring$'
msg4 DB 13,10,'is not a substring$'


data ENDS         

code SEGMENT
start:	
	MOV AX,data
	MOV DS,AX
	MOV ES,AX
	
	
	MOV DX,OFFSET msg1
	MOV AH,09h
	INT 21h
	
	LEA DX,str1
	MOV AH,09h
	INT 21h
	
	LEA DX,msg2
	MOV AH,09h
	INT 21h
	
	LEA DX,str2
	MOV AH,09h
	INT 21h
	
	
	LEA SI,str1
l1: 
	CLD
	MOV CX,len1
	LEA DI,str2
	REPE CMPSB
	JE ext1
	
	INC SI
	DEC len
	CMP len,00h
	JE ext2
	JMP l1

	
ext1:
	LEA DX,msg3
	MOV AH,09h
	INT 21h
	JMP ext
	
ext2:
	LEA DX,msg4
	MOV AH,09h
	INT 21h
	
ext:
	MOV AH,4ch
	INT 21h
	
	
code ENDS
END start