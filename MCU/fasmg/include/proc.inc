;-----------------------------------------------------------------------
;   these macros let define procedures with proc/endp keywords
;-----------------------------------------------------------------------
;   if procedure is not used,
;   its code is not included into the output file
;-----------------------------------------------------------------------
;example:
;    call myproc
;    call myproc2.m1 ; 
;    ...             
;.dummy = myproc2    ; dummy definition to explicit use of myproc2,
;                    ; so label myproc2.m1 becomes available              
;-----------------------------------------------------------------------
;proc myproc
;    xchg
;    ret
;endp
;-----------------------------------------------------------------------
;proc myproc2
;    dcr e
;.m1:             ; <-- myproc2.m1
;    jnz myproc2
;    ret
;endp
;-----------------------------------------------------------------------
;proc not_in_use  ; there is no call to this procedure,
;    nop          ; therefore these commands will not be included
;    ret          ; into the output file
;endp
;-----------------------------------------------------------------------
if ~ defined proc_v

    restore proc_v      ; this ensures that symbol cannot be forward-referenced
    proc_v = 1

    macro proc name
            name:
            if used name
    end macro


    macro endp!
            end if
;no listing  
            .end:
;listing back            

    end macro

;    display "proc is defined",13,10

end if
;-----------------------------------------------------------------------
