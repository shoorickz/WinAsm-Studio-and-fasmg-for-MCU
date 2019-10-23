;=======================================================================
; XTAL ~ 14 MHz
;-----------------------------------------------------------------------
include "8048.inc"
;-----------------------------------------------------------------------
            DIS TCNTI
LOOP1:
            MOV  R1,#PATTERN
LOOP:
            MOV  A,R1
            MOVP A,@A
            OUTL P1,A
            INC  R1
            MOV  A,R1
            MOVP A,@A
            JZ   LOOP1
            CALL DELX
            INC  R1
            JMP  LOOP
;-----------------------------------------------------------------------
DELX:      
            MOV R2,A
DELXLOOP:   
            CALL DEL05
            DJNZ R2,DELXLOOP
            RET            
;-----------------------------------------------------------------------
DEL05:       
            MOV R0,#60 
DEL05LOOP:   
            CALL DELAY
            DJNZ R0,DEL05LOOP
            RET            
;-----------------------------------------------------------------------
DELAY:       
            CLR A
            MOV T,A
            STRT T
DELOOP:      
            JTF DELOK
            JMP DELOOP
DELOK:       
            STOP TCNT
            RET                        
;=======================================================================
PATTERN:    
            DB 0xFB,8
            DB 0xF9,4
            DB 0xFE,4
            DB 0xFF,1
            DB 0xFE,1
            DB 0xFF,1
            DB 0xFE,1
            DB 0xFD,4
            DB 0xFF,0
;=======================================================================
            