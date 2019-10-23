;-----------------------------------------------------------------------
include "8051.inc"
;-----------------------------------------------------------------------
macro ORGX? addr,filler=0 ; org with padding (aka align)
  if ~ (addr = $) 
    db (addr - $) dup (filler)
  end if
end macro  
;-----------------------------------------------------------------------
macro SELECT_BANK? n ; select working register bank
   if n>3
     err "Wrong bank number!"
   end if
   if n and 1
     setb RS0
   else
     clr  RS0
   end if
   if n and 2
     setb RS1
   else
     clr  RS1
   end if
end macro
;-----------------------------------------------------------------------
LAST_FLAG_ADDR=1Fh
;-----------------------------------------------------------------------
macro FLAG? new_flag        ; define a flag in the bit-addressable area
    if ~ defined LAST_FLAG
      restore LAST_FLAG
      LAST_FLAG=0
    else
      LAST_FLAG=LAST_FLAG+1
    end if
    if LAST_FLAG > 7Fh
      err "Too many flags!"
    end if
    
    new_flag := LAST_FLAG
    
    LAST_FLAG_ADDR=LAST_FLAG shr 3 + 20h
    
end macro
;-----------------------------------------------------------------------
macro DATA? new_data,bytes=1 ; define byte(s) from the top
    if ~ defined MEM_TOP     ; of the scratchpad 
      restore MEM_TOP        ; by default is not including
      MEM_TOP=80h            ; range above 7Fh (i8052)
    end if
    if ~ defined MEM_BOTTOM
      restore MEM_BOTTOM
      MEM_BOTTOM=30h ; 20h..2Fh - bitfield area (flags)
    end if
    MEM_TOP=MEM_TOP-bytes
    if MEM_TOP<MEM_BOTTOM
      err "DATA declaration address is below MEM_BOTTOM"
    end if
    
    new_data := MEM_TOP
    
end macro
;-----------------------------------------------------------------------
    STACK=2Fh
    STACK_SIZE=16
;-----------------------------------------------------------------------
    DATA_BOTTOM=STACK+STACK_SIZE+1  
;-----------------------------------------------------------------------
