DSEG SEGMENT
Node	STRUC
anss	DW 0
value	DW 0
Node	ENDS

num	DW 0
j	DB ' '
year	DW 0
cc	DW 3 DUP (0)
str	DB 10 DUP (' ')
a	DW 0
i	DW 0
b	DW 0
ppp	Node	<,>
DSEG ENDS

SSEG SEGMENT STACK
SKTOP DB 20 DUP(0)
SSEG ENDS

CSEG SEGMENT
ASSUME CS:CSEG ,DS:DSEG, SS:SSEG
find	PROC
.L1:		mov i,	ax
.L2:		mov ax,	2
.L3:		mov cx,	num
.L4:		mul 	cx
.L5:		mov num,	ax
		RET
find	ENDP

START:
		mov ax,	DSEG
		mov ds,	ax
		mov ax,	SSEG
		mov ss,	ax
		mov sp,	LENGTH SKTOP
.L6:		mov al,	'c'
.L7:		mov j,	al
.L8:		mov ax,	365
.L9:		mov year,	ax
.L10:		lea bx,	cc
.L11:		mov ax,	1
.L12:		mov [bx],	ax
.L13:		lea bx,	cc
.L14:		mov ax,	2
.L15:		mov [bx+4],	ax
.L16:		mov ax,	2
.L17:		mov b,	ax
.L18:		lea bx,	cc
.L19:		mov ax,	3
.L20:		mov [bx+8],	ax
.L21:		lea bx,	str
.L22:		mov al,	's'
.L23:		mov [bx],	al
.L24:		lea bx,	str
.L25:		mov al,	'y'
.L26:		mov [bx+4],	al
.L27:		lea bx,	str
.L28:		mov al,	'r'
.L29:		mov [bx+8],	al
.L30:		lea bx,	str
.L31:		mov al,	'e'
.L32:		mov [bx+12],	al
.L33:		mov ax,	5
.L34:		mov a,	ax
.L35:		lea bx,	ppp
.L36:		mov ax,	5
.L37:		mov [bx].anss,	ax
.L38:		mov ax,	10
.L39:		mov i,	ax
.L40:		lea bx,	ppp
.L41:		mov ax,	7
.L42:		mov [bx].value,	ax
.L43:		mov ax,	10
.L44:		cmp ax,	7
.L45:		jnb 	.L49
.L46:		lea bx,	ppp
.L47:		mov ax,	[bx].anss
.L48:		mov a,	ax
.L49:		mov ax,	i
.L50:		cmp ax,	5
.L51:		jnb 	.L56
.L52:		lea bx,	ppp
.L53:		mov ax,	[bx].value
.L54:		mov a,	ax
.L55:		jmp 	.L60
.L56:		mov ax,	a
.L57:		mov cx,	4
.L58:		mul 	cx
.L59:		mov a,	ax
.L60:		mov ax,	0
.L61:		mov i,	ax
.L62:		mov ax,	i
.L63:		cmp ax,	100
.L64:		jna 	.L72
.L65:		mov ax,	i
.L66:		add ax,	1
.L67:		mov i,	ax
.L68:		mov ax,	a
.L69:		add ax,	2
.L70:		mov a,	ax
.L71:		jmp 	.L64
.L72:		mov ax,	a
.L73:		cmp ax,	50
.L74:		jnb 	.L79
.L75:		mov ax,	a
.L76:		sub ax,	5
.L77:		mov a,	ax
.L78:		jmp 	.L72
.L79:		mov ax,	a
.L80:		mov num,	ax
.L81:		mov ax,	i
.L82:		mov cx,	a
.L83:		xor dx,	dx
.L84:		div 	cx
.L85:		mov b,	ax
.L86:		call 	find
.L87:		mov b,	ax
.L88:		mov ah,	4ch
.L89:		int 	21h
CSEG ENDS
END START
