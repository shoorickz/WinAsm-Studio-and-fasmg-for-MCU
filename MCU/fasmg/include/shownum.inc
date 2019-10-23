;-----------------------------------------------------------------------
;   this macro lets to display label values with desired base
;-----------------------------------------------------------------------
;
;-----------------------------------------------------------------------
struc shownum value,base:10
        local x,sgn,dgt,txt
        x = value
        sgn = 0
        if x < 0
                x = -x
                sgn = 1
        end if
        txt = ''
        while x | ~txt
                dgt = x mod base
                x = x / base
                if dgt < 10
                        dgt = '0' + dgt
                else
                        dgt = 'A' + dgt - 10
                end if
                txt = txt shl 8 + dgt
        end while
        if sgn
                txt = txt shl 8 + '-'
        end if
        . = string txt
end struc
;-----------------------------------------------------------------------
;
;A shownum 1234567890
;B shownum 65535, 16
;C shownum 3003, 2
;
;display 'A = ',A,13,10
;display 'B = ',B,'h',13,10
;display 'C = ',C,'b',13,10
;
;D shownum 1 shl 512
;display 'D = ',D,13,10
;
;-----------------------------------------------------------------------

