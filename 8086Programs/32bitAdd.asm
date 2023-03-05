assume CS:code

code SEGMENT
start:
	MOV AX,3000h
	MOV DS,AX
	
	CLC
	
	MOV AX,7ecah
	ADD AX,5678h
	MOV [1000h],AX
	MOV AX,4545h
	ADC AX,3645h
	MOV [1002h],AX
	
	MOV AH,4ch
	INT 21h

code ENDS
END start
