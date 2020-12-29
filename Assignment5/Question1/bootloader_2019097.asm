bits 16
org 0x7c00

boot:
	mov ax, 0x2401
	int 0x15
	mov ax, 0x3
	int 0x10
	cli
	lgdt [gdt_pointer_struct]
	mov eax, cr0
	or eax,0x1
	mov cr0, eax
	jmp CODE_SEG:boot2
gdt_begin:
	dq 0x0
gdt_code:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10011010b
	db 11001111b
	db 0x0
	
gdt_data:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10010010b
	db 11001111b
	db 0x0
gdt_end:
gdt_pointer_struct:
	dw gdt_end - gdt_begin
	dd gdt_begin

CODE_SEG equ gdt_code - gdt_begin
DATA_SEG equ gdt_data - gdt_begin

bits 32
boot2:
	mov ax, DATA_SEG
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov edx,cr0
	mov ecx, 32
	mov ebx,000B8c14h
.writeContent:
	mov eax, 00000130h
	shr edx,1
	adc eax,0
	mov [ebx], ax
	add ebx,2
	dec ecx
	jnz .writeContent
	
suffix:
	mov esi,suffixStatement
	mov ecx,000B8c00h
	
.writeSuffix:
	lodsb
	or al,al
	jz nextLine
	or eax,0x0100
	mov word [ecx],ax
	add ecx,2
	jmp .writeSuffix
	
nextLine:
	mov esi,hello
	mov edx,0xb801e
	
.writeHello:
	lodsb
	or al,al
	jz exit
	or eax,0x0100
	mov word [edx], ax
	add edx,2
	jmp .writeHello	
	
exit:

	cli
	hlt
	
hello: db "Hello world   ",0
suffixStatement: db "CR0: ",0
times 510 - ($-$$) db 0
dw 0xaa55
