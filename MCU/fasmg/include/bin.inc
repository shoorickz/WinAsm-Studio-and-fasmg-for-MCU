;-----------------------------------------------------------------------
;   converts output into binary text
;-----------------------------------------------------------------------
define BIN

macro BIN.byte value
	local digit
	digit = '0' + (value) shr 7 and 1
    db digit
	digit = '0' + (value) shr 6 and 1
    db digit
	digit = '0' + (value) shr 5 and 1
    db digit
	digit = '0' + (value) shr 4 and 1
    db digit,"-"
	digit = '0' + (value) shr 3 and 1
    db digit
	digit = '0' + (value) shr 2 and 1
    db digit
	digit = '0' + (value) shr 1 and 1
    db digit
	digit = '0' + (value) shr 0 and 1
	db digit
end macro

macro BIN.line address,value
	BIN.byte (address) shr 8
	db "-"
	BIN.byte (address) and 0FFh
    db " : "
	BIN.byte value
	db 13,10
end macro

macro BIN.seg address:0
	virtual at address
end macro

macro BIN.endseg
	local code,address,size,bytes
	code:: address = $$
	       size = $-$$
	end virtual
	while size
		load bytes:1 from code:address
		BIN.line address,bytes
		address = address + 1
		size = size - 1
	end while
end macro

macro ORG? address
	if $ <> address
		BIN.endseg
		BIN.seg address
	end if
end macro

BIN.seg

postpone
	BIN.endseg
	db 13,10
end postpone
