global _start

_start:
    mov rax,rsi
    mov rbx,rdi
    jmp checkGreater

checkGreater:
    cmp rax,rbx
    jle lesser
    mov rax,1
    mov rdi,1
    mov rsi,message1
    mov rdx, 2
    syscall
    ret

lesser:
    mov rax,1
    mov rdi,1
    mov rsi,message2
    mov rdx,2
    syscall
    ret

message1: db "1",10
message2: db "0",10