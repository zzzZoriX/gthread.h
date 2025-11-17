global gthread_switch

section .text
gthread_switch:

; save old gthread data
mov [rcx], rsp
mov [rcx + 8], rbp,
mov [rcx + 16], rbx
mov [rcx + 24], r12
mov [rcx + 32], r13
mov [rcx + 40], r14
mov [rcx + 48], r15

; load new gthread data
mov rsp, [rdx]
mov rbp, [rdx + 8]
mov rbx, [rdx + 16]
mov r12, [rdx + 24]
mov r13, [rdx + 32]
mov r14, [rdx + 40]
mov r15, [rdx + 48]