define GLOBSTR 1

virtual at GLOBSTR.baseaddr
        GLOBSTR.buffer::
end virtual

struc GLOBSTR data&
        virtual GLOBSTR.buffer
                . db data
        end virtual
end struc

macro GLOBSTR.here
        GLOBSTR.baseaddr db GLOBSTR.data
        GLOBSTR.where := GLOBSTR.baseaddr
end macro

postpone
        virtual GLOBSTR.buffer
                load GLOBSTR.data:$-$$ from $$
        end virtual
        if ~ defined GLOBSTR.where
                display 'Global string data has been placed automatically at the end of the executable.',13,10
                display 'To place it elsewhere, use "GLOBSTR.here" macro in the intended location.',13,10
                GLOBSTR.baseaddr db GLOBSTR.data
        end if
end postpone