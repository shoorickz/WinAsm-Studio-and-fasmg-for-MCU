;-----------------------------------------------------------------------
if ~ defined warn_v

    restore  warn_v
    define   warn_v 1

    macro warn msg*
            repeat 1 num:__LINE__
                    display __FILE__,' [',`num,']',13,10
            end repeat
            display 'Warning: ',msg,'.',13,10
    end macro 
    
end if
;-----------------------------------------------------------------------
;warn 'something is fishy here'