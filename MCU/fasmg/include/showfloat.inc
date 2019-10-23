;-----------------------------------------------------------------------
struc showfloat value,precision:2
        local x,i,pos,sgn,dgt,txt
        x = value
        x = x * 1e#precision
        sgn = 0
        if x < 0
                x = -x
                sgn = 1 
        end if 
        i = trunc x
        if x - i >= float 1/2
                i = i + 1
        end if
        pos = 0
        txt = ''
        while i | pos <= precision
                dgt = i mod 10
                i = i / 10
                txt = txt shl 8 + '0' + dgt
                pos = pos + 1
                if pos = precision
                        txt = txt shl 8 + '.'
                end if
        end while 
        if sgn 
                txt = txt shl 8 + '-' 
        end if 
        . = string txt 
end struc
;-----------------------------------------------------------------------
;
;f = 1
;e = f
;repeat 33
;        f = f * %
;        e = e + 1f/f
;end repeat
;out showfloat e, 37
;display out
;
;-----------------------------------------------------------------------
