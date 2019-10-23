;-----------------------------------------------------------------------
 macro union?
        union?. = $
        macro endu?!
                purge ?,endu?
        end macro
        macro ? line&
                if $-union = 0
                        line
                else
                        virtual at union
                                line
                                local size
                                size = $-union
                        end virtual
                        if size > $-union
                                rb size-($-union)
                        end if
                end if
        end macro
end macro
;-----------------------------------------------------------------------

; usage example:

;union
;  x dd ?
;  left dd ?
;endu 

