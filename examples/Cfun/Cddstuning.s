; DDStuning demo
; IgorM c 6/2015
;

	.pword  paddr(9b)+PFLASH
; Cdds
9:
	.byte   NFA|9
	.ascii  "ddstuning"
	.align  2
CDDS_:
	push	W0
	push	W1
	push	W2
	push 	W3
	push	W4
	push	W5
	push	W6
	push 	W7
	mov     [W14--], W7
	mov     [W14--], W6
	mov     [W14--], W5
	mov     [W14--], W4
	mov     [W14--], W3
	mov     [W14--], W2
	mov     [W14--], W1
	mov     [W14], W0
	.extern _Cddstune
	call  _Cddstune
	mov     W0, [W14++]
	mov     W1, [W14++]
	mov     W2, [W14++]
	mov     W3, [W14]   ; returns 64bit int
	pop     W7
	pop     W6
	pop     W5
	pop     W4
	pop     W3
	pop     W2
	pop     W1
	pop     W0
	return

