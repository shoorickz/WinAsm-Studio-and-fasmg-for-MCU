
Listing? = 1

namespace Listing
        base = $$  
        offset = $
        virtual at 0
                HexDigits:: db '0123456789ABCDEF'
        end virtual
end namespace

macro ? line&
        line
        rmatch =nolist?, line
                Listing? =: 0
        else rmatch =list?, line
                restore Listing?
        else
                if Listing
                        namespace Listing  
                                if ~ $$ eq base  
                                        base = $$  
                                        offset = $$  
                                end if  
                                bytes = $ - offset  
                                if $ - bytes < $$  
                                        bytes = $ - $$  
                                end if  
                                offset = $
                                address = (offset scale 0)-bytes
                                repeat 8
                                        load digit:byte from HexDigits:((address) shr ((%%-%) shl 2)) and 0Fh
                                        display digit
                                end repeat
                                display ': '
                                if bytes < 0
                                        bytes = 0
                                end if
                                while bytes > 0
                                        if bytes > 8
                                                bytes_in_row = 8
                                        else
                                                bytes_in_row = bytes
                                        end if
                                        if $ - bytes + bytes_in_row <= $@
                                                readable_bytes = bytes_in_row
                                        else if $ - bytes >= $@
                                                readable_bytes = 0
                                        else
                                                readable_bytes = bytes_in_row - ($ - $@)
                                        end if
                                        load data:readable_bytes from $ - bytes
                                        repeat readable_bytes
                                                load digit:byte from HexDigits:(data shr ((%-1) shl 3 + 4)) and 0Fh
                                                display digit
                                                load digit:byte from HexDigits:(data shr ((%-1) shl 3)) and 0Fh
                                                display digit,' '
                                        end repeat
                                        repeat bytes_in_row - readable_bytes
                                                display '?? '
                                        end repeat
                                        if bytes > bytes_in_row
                                                display 13,10,'          '
                                                bytes = bytes - bytes_in_row
                                        else
                                                break
                                        end if
                                end while
                                repeat 8-bytes
                                        display '   '
                                end repeat
                                display `line,13,10
                        end namespace
                end if
        end rmatch
end macro

macro nolist?
end macro

macro list?
end macro

postpone
        nolist 
end postpone