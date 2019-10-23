;-----------------------------------------------------------------------
;   this macro lets use "\" to split line instead of combine
;-----------------------------------------------------------------------
macro recursive_split line&
        match first \ rest, line
                first
                recursive_split rest
        else
                line
        end match
end macro

macro ? line&
        recursive_split line
end macro 
;-----------------------------------------------------------------------
;
;include '80386.inc'
;
;mov ax,cx\ add ax,2\ mov cx,ax\ add ax,3\ jnc $+6\ cmc 
;