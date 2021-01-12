;=======================================================================
;   Замена символов кодировки СР1251 на КОИ-7 (v. 2.0)
;=======================================================================
virtual at 0
koi7lat::
    db 27h,41h,42h,43h,44h,45h,46h,47h,48h,49h,4Ah,4Bh,4Ch,4Dh,4Eh,4Fh
    db 50h,51h,52h,53h,54h,55h,56h,57h,58h,59h,5Ah,5Bh,5Ch,5Dh,5Eh,5Fh
end virtual    
;-----------------------------------------------------------------------
virtual at 0
koi7rus::
    db 61h,62h,77h,67h,64h,65h,76h,7Ah,69h,6Ah,6Bh,6Ch,6Dh,6Eh,6Fh,70h
    db 72h,73h,74h,75h,66h,68h,63h,7Eh,7Bh,7Dh,27h,79h,78h,7Ch,60h,71h
    db 61h,62h,77h,67h,64h,65h,76h,7Ah,69h,6Ah,6Bh,6Ch,6Dh,6Eh,6Fh,70h
    db 72h,73h,74h,75h,66h,68h,63h,7Eh,7Bh,7Dh,27h,79h,78h,7Ch,60h,71h
end virtual    
;-----------------------------------------------------------------------
macro DR? args& 
   local koi7ptr,koi7char 
   koi7ptr = $
   db args 
   while koi7ptr < $ 
     load koi7char:byte from koi7ptr 
     if koi7char > 0BFh 
       load  koi7char:byte from koi7rus:koi7char - 0C0h
       store koi7char:byte at koi7ptr
     else if (koi7char > 05Fh) & (koi7char < 080h) 
       load  koi7char:byte from koi7lat:koi7char - 060h
       store koi7char:byte at koi7ptr
     end if
     koi7ptr = koi7ptr + 1 
   end while 
end macro   
;=======================================================================
