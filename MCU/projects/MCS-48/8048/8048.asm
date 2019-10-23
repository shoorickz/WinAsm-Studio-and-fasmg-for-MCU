;=======================================================================
; This program runs "zero" forward and backward through pins of port P1,
; so, if LEDs are connected, you can see running light point with it.
; More clear: http://www.youtube.com/watch?v=i91OEn-BB1I
; Used quartz is around 14 MHz
;-----------------------------------------------------------------------
INCLUDE "8048.INC"
;-----------------------------------------------------------------------
INCLUDE "switch.inc" ; use this for text output instead of binary,
                     ; ready to use with manual rom programmer
;=======================================================================
            ORG 0
            MOV  A,#0x55 ; at first output for SS (single step) debugger
            OUTL P1,A
            RL   A
            OUTL P1,A
;-----------------------------------------------------------------------
            DIS TCNTI
            MOV  R1,#NOT 1
LOOP2:
            MOV  A,R1
            RL   A
            MOV  R1,A
            OUTL P1,A
            CALL TODEL05
            JMP  LOOP2
;-----------------------------------------------------------------------
TODEL05:
            DW -1 ; JMP  XDEL05
;-----------------------------------------------------------------------
XDEL05:       
            MOV R0,#60 
XDEL05LOOP:   
            CALL XDELAY
            DJNZ R0,XDEL05LOOP
            RET            
;-----------------------------------------------------------------------
XDELAY:       
            CLR A
            MOV T,A
            STRT T
XDELOOP:      
            JTF XDELOK
            JMP XDELOOP
XDELOK:       
            STOP TCNT
            RET                        
;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
