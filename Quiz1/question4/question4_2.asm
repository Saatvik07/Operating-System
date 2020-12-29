global long_add

long_add:
    mov rax,rdi
    add rax,rsi
    add rax,rdx
    add rax,rcx
    ret 