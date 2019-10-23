;=======================================================================
;   MSC-48 support for fasmg (19.01.2016)
;=======================================================================
element R

repeat 8 i:0
  element R#i? : R + i
end repeat
;-----------------------------------------------------------------------
macro register param
    if param relativeto param element 1 & \
       param scale 0 = 0
    	if param metadata 1 relativeto R
    		regnum = param metadata 1 - R
    	else
    		err "syntax error"
    	end if
    else
    	err "syntax error"
    end if
end macro
;-----------------------------------------------------------------------
irp <mnem,opcode>,JC?, 0F6h,JNC?, 0E6h,JZ?, 0C6h,JNZ?, 096h,\
                  JT0?,036h,JNT0?,026h,JT1?,056h,JNT1?,046h,\
                  JF0?,0B6h,JF1?, 076h,JTF?,016h,JNI?, 086h
  macro mnem dest
    if (dest and not 0FFh) = ($ and not 0FFh)
        dw opcode or (dest and 0FFh) shl 8
    else
        err "address is out of page"
    end if
  end macro
end irp
;-----------------------------------------------------------------------
irp <mnem,opcode>,JMP?,004h,CALL?,014h
  macro mnem dest
    if dest and not 07FFh
        err "address is out of range"
    else
       dw opcode or (dest shr 3 and 0E0h) or (dest and 0FFh) shl 8
    end if
  end macro
end irp
;-----------------------------------------------------------------------
macro JMPP? param
    match =@A?,param
        db 0B3h
    else
        err "syntax error"
    end match
end macro
;-----------------------------------------------------------------------
macro DJNZ? param,dest
    if (dest and not 0FFh) = ($ and not 0FFh)
        register param
        dw 0E8h or regnum or (dest and 0FFh) shl 8
    else
        err "address is out of page"
    end if
end macro
;-----------------------------------------------------------------------
repeat 8 i:0
  macro JB#i? dest
    if (dest and not 0FFh) = ($ and not 0FFh)
        dw 012h or i shl 5 or (dest and 0FFh) shl 8
    else
        err "address is out of page"
    end if
  end macro
end repeat
;-----------------------------------------------------------------------
irp <mnem,opcode>,NOP?,000h,RET?,083h,RETR?,093h
    macro mnem 
        db opcode
    end macro
end irp
;-----------------------------------------------------------------------
irp <mnem,opcode>,DA?,057h,RL?,0E7h,RLC?,0F7h,RR?,077h,RRC?,067h,SWAP,047h
    macro mnem param
        match =A?,param
            db opcode
        else
            err "syntax error"
        end match
    end macro
end irp
;-----------------------------------------------------------------------
macro MOV? dest,src
    match #data,src
        match =A?,dest
            db 023h
        else match =@R0?,dest
            db 0B0h
        else match =@R1?,dest
            db 0B1h
        else
            register dest
            db 0B8h or regnum
        end match
        db +(data)
    else match =A?,dest
        match =PSW?,src
            db 0C7h
        else match =T?,src
            db 042h
        else match =@R0?,src
            db 0F0h
        else match =@R1?,src
            db 0F1h
        else
            register src
            db 0F8h or regnum
        end match
    else match =A?,src
        match =PSW?,dest
            db 0D7h
        else match =T?,dest
            db 062h
        else match =@R0?,dest
            db 0A0h
        else match =@R1?,dest
            db 0A1h
        else 
            register dest
            db 0A8h or regnum
        end match
    else
        err "syntax error"
    end match
end macro
;-----------------------------------------------------------------------
macro MOVX? dest,src
    match =A?,dest
        match =@R0?,src
            db 080h
        else match =@R1?,src
            db 081h
        else
            err "syntax error"
        end match
    else match =A?,src
        match =@R0?,dest
            db 090h
        else match =@R1?,dest
            db 091h
        else
            err "syntax error"
        end match
    else
        err "syntax error"
    end match
end macro
;-----------------------------------------------------------------------
macro XCH? dest,src
    match =A?,dest
        match =@R0?,src
            db 020h
        else match =@R1?,src
            db 021h
        else 
            register src
            db 028h or regnum
        else
            err "syntax error"
        end match
    else
        err "syntax error"
    end match
end macro
;-----------------------------------------------------------------------
macro XCHD? dest,src
    match =A?,dest
        match =@R0?,src
            db 030h
        else match =@R1?,src
            db 031h
        else
            err "syntax error"
        end match
    else
        err "syntax error"
    end match
end macro
;-----------------------------------------------------------------------
macro MOVP? dest,src
    match =A?,dest
        match =@A?,src
            db 0A3h
        else
            err "syntax error"
        end match
    else
        err "syntax error"
    end match
end macro
;-----------------------------------------------------------------------
macro MOVP3? dest,src
    match =A?,dest
        match =@A?,src
            db 0E3h
        else
            err "syntax error"
        end match
    else
        err "syntax error"
    end match
end macro
;-----------------------------------------------------------------------
macro STRT? param
   match =T?,param
       db 055h
   else match =CNT?,param
       db 045h
   else
       err "syntax error"
   end match
end macro
;-----------------------------------------------------------------------
macro STOP? param
   match =TCNT?,param
       db 065h
   else
       err "syntax error"
   end match
end macro
;-----------------------------------------------------------------------
macro DIS? param
    match =TCNTI?,param
        db 035h
    else match =I?,param
        db 015h
    else
        err "syntax error"
    end match
end macro
;-----------------------------------------------------------------------
macro EN? param
    match =TCNTI?,param
        db 025h
    else match =I?,param
        db 005h
    else
        err "syntax error"
    end match
end macro
;-----------------------------------------------------------------------
macro ENT0? param
    match =CLK?,param
        db 075h
    else
        err "syntax error"
    end match
end macro
;-----------------------------------------------------------------------
macro SEL? param
    match =RB0?,param
        db 0C5h
    else match =RB1?,param
        db 0D5h
    else match =MB0?,param
        db 0E5h
    else match =MB1?,param
        db 0F5h
    else
        err "syntax error"
    end match
end macro
;-----------------------------------------------------------------------
macro ADD? dest,src
    match =A?,dest
        match #data,src
            db 003h,+(data)
        else match =@R0?,src
            db 060h
        else match =@R1?,src
            db 061h
        else
            register src
            db 068h or regnum
        end match
    else
        err "syntax error"
    end match
end macro
;-----------------------------------------------------------------------
macro ADDC? dest,src
    match =A?,dest
        match #data,src
            db 013h,+(data)
        else match =@R0?,src
            db 070h
        else match =@R1?,src
            db 071h
        else
            register src
            db 078h or regnum
        end match
    else
        err "syntax error"
    end match
end macro
;-----------------------------------------------------------------------
macro ANL? dest,src
    match =A?,dest
        match #data,src
            db 053h,+(data)
        else match =@R0?,src
            db 050h
        else match =@R1?,src
            db 051h
        else
            register src
            db 058h or regnum
        end match
    else match #data,src
        match =BUS?,dest
            db 098h
        else match =P1?,dest
            db 099h
        else match =P2?,dest
            db 09Ah
        else
            err "syntax error"
        end match
        db +(data)
    else
        err "syntax error"    
    end match
end macro
;-----------------------------------------------------------------------
macro ORL? dest,src
    match =A?,dest
        match #data,src
            db 043h,+(data)
        else match =@R0?,src
            db 040h
        else match =@R1?,src
            db 041h
        else
            register src
            db 048h or regnum
        end match
    else match #data,src
        match =BUS?,dest
            db 088h
        else match =P1?,dest
            db 089h
        else match =P2?,dest
            db 08Ah
        else
            err "syntax error"
        end match
        db +(data)
    else
        err "syntax error"    
    end match
end macro
;-----------------------------------------------------------------------
macro XRL? dest,src
    match =A?,dest
        match #data,src
            db 0D3h,+(data)
        else match =@R0?,src
            db 0D0h
        else match =@R1?,src
            db 0D1h
        else
            register src
            db 0D8h or regnum
        end match
    else
        err "syntax error"
    end match
end macro
;-----------------------------------------------------------------------
macro CLR? dest
    match =A?,dest
        db 027h
    else match =C?,dest
        db 097h
    else match =F0?,dest
        db 085h
    else match =F1?,dest
        db 0A5h
    else
        err "syntax error"
    end match
end macro    
;-----------------------------------------------------------------------
macro CPL? dest
    match =A?,dest
        db 037h
    else match =C?,dest
        db 0A7h
    else match =F0?,dest
        db 095h
    else match =F1?,dest
        db 0B5h
    else
        err "syntax error"
    end match
end macro    
;-----------------------------------------------------------------------
macro INC? dest
    match =A?,dest
        db 017h
    else match =@R0?,dest
        db 010h
    else match =@R1?,dest
        db 011h
    else 
        register dest
        db 018h or regnum
    end match
end macro
;-----------------------------------------------------------------------
macro DEC? dest
    match =A?,dest
        db 007h
    else match =@R0?,dest
        db 0C0h
    else match =@R1?,dest
        db 0C1h
    else 
        register dest
        db 0C8h or regnum
    end match
end macro
;-----------------------------------------------------------------------
macro INS? dest,src
    match =A?,dest
        match =BUS?,src
            db 008h
        else
            err "syntax error"
        end match
    else
        err "syntax error"
    end match
end macro
;-----------------------------------------------------------------------
macro IN? dest,src
    match =A?,dest
        match =P1?,src
            db 009h
        else match =P2?,src
            db 00Ah
        else
            err "syntax error"
        end match
    else
        err "syntax error"
    end match
end macro
;-----------------------------------------------------------------------
macro MOVD? dest,src
    match =A?,src
        match =P4?,dest
            db 00Ch or 0
        else match =P5?,dest
            db 00Ch or 1
        else match =P6?,dest
            db 00Ch or 2
        else match =P7?,dest
            db 00Ch or 3
        else
            err "syntax error"
        end match
    match =A?,dest
        match =P4?,src
            db 03Ch or 0
        else match =P5?,src
            db 03Ch or 1
        else match =P6?,src
            db 03Ch or 2
        else match =P7?,src
            db 03Ch or 3
        else
            err "syntax error"
        end match
    else
        err "syntax error"
    end match
end macro
;-----------------------------------------------------------------------
macro ANLD? dest,src
    match =A?,src
        match =P4?,dest
            db 09Ch or 0
        else match =P5?,dest
            db 09Ch or 1
        else match =P6?,dest
            db 09Ch or 2
        else match =P7?,dest
            db 09Ch or 3
        else
            err "syntax error"
        end match
    else
        err "syntax error"
    end match
end macro
;-----------------------------------------------------------------------
macro ORLD? dest,src
    match =A?,src
        match =P4?,dest
            db 08Ch or 0
        else match =P5?,dest
            db 08Ch or 1
        else match =P6?,dest
            db 08Ch or 2
        else match =P7?,dest
            db 08Ch or 3
        else
            err "syntax error"
        end match
    else
        err "syntax error"
    end match
end macro
;-----------------------------------------------------------------------
macro OUTL? dest,src
    match =A?,src
        match =BUS?,dest
            db 002h
        else match =P1?,dest
            db 039h
        else match =P2?,dest
            db 03Ah
        else
            err "syntax error"
        end match
    else
        err "syntax error"
    end match
end macro
;=======================================================================
