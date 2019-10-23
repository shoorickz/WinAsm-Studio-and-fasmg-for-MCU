;-----------------------------------------------------------------------
 macro struct? name
        macro ends?!
                        end namespace
                        iterate definition, args@struct
                                match name:value, definition
                                        store value at .name
                                else match name==value, definition
                                        store value at .name
                                else match value, definition
                                        err 'unnamed values not supported'
                                end match
                        end iterate
                end struc
                virtual at 0
                        name name
                        sizeof.name = $
                end virtual
                purge ends?
        end macro
        struc name args@struct&
                label . : sizeof.name
                namespace .
end macro
;-----------------------------------------------------------------------
;
; usage example:
;
;struct RECT
;  left   dd ?
;  top    dd ?
;  right  dd ?
;  bottom dd ?
;ends
;
;area RECT left:0,top:0,right:320,bottom:200

