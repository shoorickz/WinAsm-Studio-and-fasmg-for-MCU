;=======================================================================
;     Macros to create tape header and tail
;     for emulator of some soviet computers 
;=======================================================================
;     Вычисление контрольной суммы
;     Корректно работает только с файлом с одним непрерывным сегментом
;-----------------------------------------------------------------------
macro rk_ks_
  rk_ks:
  .h=0
  .l=0
  .v=0
  repeat $ - $$
    load rk_ks.v : byte from $$ + % - 1
    rk_ks.l=rk_ks.l+rk_ks.v
    if $$ + % - 1 < $
      rk_ks.h=rk_ks.h+rk_ks.v
      if rk_ks.l shr 8
        rk_ks.h = rk_ks.h + 1
      end if
    end if
    rk_ks.l = rk_ks.l and 255
  end repeat
  rk_ks.h = rk_ks.h and 255
end macro
;-----------------------------------------------------------------------
;     Специалист
;-----------------------------------------------------------------------
macro RKS_START? param:0 ; параметр: адрес загрузки
  rks_org = param
  dw  rks_org   
  dw  rks_fin 
  org rks_org
end macro  
macro RKS_END?
  rks_fin = rks_org + $% - 5
  rk_ks_
  db rk_ks.l,rk_ks.h
end macro     
;=======================================================================
;     Радио-86РК
;-----------------------------------------------------------------------
macro RK_START? param:0 ; параметр: адрес загрузки
  rk_org = param
  db  rk_org shr 8, rk_org and 255   
  db  rk_fin shr 8, rk_fin and 255
  org rk_org
end macro  
macro RK_END?
  rk_fin = rk_org + $% - 5
  rk_ks_
  db rk_ks.h,rk_ks.l
end macro     
;=======================================================================
macro ENDM? top:65536 ; проверка перехода границы в 64кБ
    if $>top
        err "out of memory limit"
    end if
end macro
;=======================================================================
