.set MAGIC, 0x1badb002           # Multiboot magic number
.set FLAGS, (1<<0 | 1<<1)         # Align modules, memory info
.set CHECKSUM, -(MAGIC + FLAGS)   # Checksum kontrolü

.section .multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

.section .text
.extern kernel_main
.global start

start:
    cli                           # Interrupt'ları kapat
    mov $kernel_stack_top, %esp   # Stack pointer'ını ayarla
    
    # Multiboot bilgilerini al
    push %eax                      # Multiboot magic
    push %ebx                      # Multiboot info pointer

    call kernel_main              # Kernel'e git
    
    hlt                           # CPU'yu durdur
    jmp start                     # Sonsuza kadar döngü

.section .bss
    .align 4096
    kernel_stack:
        .space 16384
    kernel_stack_top:
