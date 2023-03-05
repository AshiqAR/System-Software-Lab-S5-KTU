data SEGMENT

opr1 DW 0f325h
opr2 DW 0e000h

data ENDS    


assume CS:code,DS:data

code SEGMENT

start:
	MOV AX,data
	MOV DS,AX
	
	MOV AX,opr1
	CLC
	ADD AX,opr2
	MOV CX,AX
	MOV AX,3000h
	MOV DS,AX
	MOV [2000h],CX
	
	JNC ext
	MOV [2002h],01h
	JMP l1
ext:
	MOV [2002h],00h
l1: 
	
	MOV AH,4ch
	INT 21h

code ENDS 
END start
