;-----------------------------------------------------------------------
;   these macros add local unnamed labels:
;-----------------------------------------------------------------------
;@@:         ; m1
;    ...
;    jz   @F ; nearest forward  -> m2
;    inr  a
;    jz   @B ; nearest backward -> m1
;@@:         ; m2
;    ...
;-----------------------------------------------------------------------
macro @@ tail
        match label, @f?
                label tail
                define @b? label
        end match
        local anonymous
        define @f? anonymous
end macro

define @f?
@@  

;-----------------------------------------------------------------------
                   