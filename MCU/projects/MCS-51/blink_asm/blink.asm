; LED Blink Example program, for use with the PJRC 8051
; Development Circuit Board, Rev 4.
;
;  http://www.pjrc.com/tech/8051/board4/blink_as31.html


;This line configures where the program will go into memory.
;2000 to 7FFF is RAM, which is the best place to download
;while testing your code.  Memory from 8000 to F7FF is Flash
;ROM, which is non-volatile.  You MUST ERASE the flash rom
;if the area you will use already has data in it.  Unlike
;easily re-writable RAM, writing to flash rom can only change
;1's into 0's.  To change the 0's back into 1's, you must
;erase the flash (which turns a section or all of it into
;0xFFs to all you to download again).

.equ    locat, 0        ;Location for this program



;82C55 memory locations, Rev 4
.equ    port_a, 0xF800		;access port A
.equ    port_b, 0xF801		;access port B
.equ    port_c, 0xF802		;access port C
.equ    port_abc_pgm, 0xF803	;configure in/out of all three ports
.equ    port_d, 0xF900		;access port D
.equ    port_e, 0xF901		;access port E
.equ    port_f, 0xF902		;access port F
.equ    port_def_pgm, 0xF903	;configure in/out of all three ports


; Useful routines in PAULMON2 that you can call.  When you
; later want a stand-alone application, you can copy them
; from the PAULMON2 source code (or write you own if you like).
.equ    cout, 0x0030		;print byte in acc to serial port
.equ    cin, 0x0032 		;get byte from serial port into acc
.equ    phex, 0x0034 		;print acc in hex (2 digits)
.equ    phex16, 0x0036		;print dptr in hex (4 digits)
.equ    pstr, 0x0038 		;print a string @dptr
.equ	esc, 0x003E		;paulmon2's check for esc key
.equ    newline, 0x0048		;print a newline (CR and LF)
.equ    pint8u, 0x004D		;print acc as unsigned int (0 to 255)
.equ    pint16u, 0x0053		;print dptr as unsigned int (0 to 65535)


;Program Header.  This is what PAULMON2 looks for to display the
;program in its memory usage and run menus.  You would normally
;run this program with 'R', but you can also jump to 2040 (or
.org    locat
.db     0xA5,0xE5,0xE0,0xA5     ;signiture bytes
.db     35,255,0,0              ;id (35=prog)
.db     0,0,0,0                 ;prompt code vector
.db     0,0,0,0                 ;reserved
.db     0,0,0,0                 ;reserved
.db     0,0,0,0                 ;reserved
.db     0,0,0,0                 ;user defined
.db     255,255,255,255         ;length and checksum (255=unused)
.db     "Blink LEDs",0          ;max 31 characters, plus the zero
.org    locat+64                ;executable code begins here



;Finally, the actual code.... much shorter than all these comments
;that try to explain how to set everything up!
startup:
	mov	dptr, #port_def_pgm
	mov	a, #128
	movx	@dptr, a	;make all D-E-F port pins outputs

begin:
	mov	dptr, #table	;DPTR will keep track of which entry in
				;the table we will do next
loop:
	clr	a
	movc	a, @a+dptr	;get pattern to display
	acall	update
	inc	dptr
	lcall	esc		;abort if the user presses ESC
	jc	exit
	clr	a
	movc	a, @a+dptr	;get time to display this pattern
	jz	begin		;restart when we hit the end of the table
	acall	delay
	inc	dptr
	sjmp	loop		;keep doing the animation....

exit:	ljmp	0




	;write the bit pattern in Acc to port E.  We need to
	;save DPTR (holding our position in the table) before
	;using DPTR to access the 82C55 chip.
update:
	push	dph
	push	dpl
	mov	dptr, #port_e
	movx	@dptr, a
	pop	dpl
	pop	dph
	ret



	;delay for a number of ms (specified by acc)
delay:
	mov	r0, a
dly2:	mov	r1, #230
dly3:	nop
	nop
	nop			;6 NOPs + DJNZ is 4.34 us
	nop			;with the 22.1184 MHz crystal
	nop
	nop
	djnz	r1, dly3	;repeat 230 times for 1 ms
	djnz	r0, dly2	;repeat for specified # of ms
	ret



	;The data table that is read by the MOVC instructions above.
table:	.db	01111111b, 90
	.db	00111111b, 70
	.db	00011111b, 50
	.db	10001111b, 40
	.db	11000111b, 40
	.db	11100011b, 40
	.db	11110001b, 40
	.db	11111000b, 50
	.db	11111100b, 70
	.db	11111110b, 90
	.db	11111100b, 70
	.db	11111000b, 50
	.db	11110001b, 40
	.db	11100011b, 40
	.db	11000111b, 40
	.db	10001111b, 40
	.db	00011111b, 50
	.db	00111111b, 70
	.db	255,0		;zero marks end of table


