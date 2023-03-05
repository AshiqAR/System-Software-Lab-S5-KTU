assume CS:code


code SEGMENT
start:
  	MOV AX,3000h
  	MOV DS,AX
  	MOV DX,2456h
  	MOV AX,3456h
  	MOV BX,5320h
  	DIV BX
  	
  	MOV [2000h],AX
  	MOV [2002h],DX
  	MOV AH,4ch
  	INT 21h


code ENDS
END start