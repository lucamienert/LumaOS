.section .text

.global syscall
syscall:
    mov 4(%esp), %eax
    int $0x30
    ret

.global syscall1
syscall1:
    push %ebx
    mov 8(%esp), %eax
    mov 12(%esp), %ebx
    int $0x30
    pop %ebx
    ret

.global syscall2
syscall2:
    push %ebx
    push %ecx
    mov 12(%esp), %eax
    mov 16(%esp), %ebx
    mov 20(%esp), %ecx
    int $0x30
    pop %ecx
    pop %ebx
    ret

.global syscall3
syscall3:
    push %ebx
    push %ecx
    push %edx
    mov 16(%esp), %eax
    mov 20(%esp), %ebx
    mov 24(%esp), %ecx
    mov 28(%esp), %edx
    int $0x30
    pop %edx
    pop %ecx
    pop %ebx
    ret