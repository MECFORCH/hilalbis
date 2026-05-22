#include "kernel.h"

/* Kernel state */
static terminal_t terminal;

/* VGA color kodlaması */
static inline uint8_t vga_entry_color(vga_color_t fg, vga_color_t bg) {
    return fg | (bg << 4);
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t)uc | ((uint16_t)color << 8);
}

/* Terminal fonksiyonları */
void terminal_initialize(void) {
    terminal.row = 0;
    terminal.column = 0;
    terminal.color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    
    /* Ekranı temizle */
    uint16_t *vga_buffer = (uint16_t *)VGA_MEMORY;
    for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga_buffer[i] = vga_entry(' ', terminal.color);
    }
}

void terminal_putchar(char c) {
    uint16_t *vga_buffer = (uint16_t *)VGA_MEMORY;
    size_t index = terminal.row * VGA_WIDTH + terminal.column;
    
    if (c == '\n') {
        terminal.row++;
        terminal.column = 0;
        if (terminal.row >= VGA_HEIGHT) {
            terminal.row = VGA_HEIGHT - 1;
        }
    } else {
        vga_buffer[index] = vga_entry(c, terminal.color);
        terminal.column++;
        if (terminal.column >= VGA_WIDTH) {
            terminal.column = 0;
            terminal.row++;
            if (terminal.row >= VGA_HEIGHT) {
                terminal.row = VGA_HEIGHT - 1;
            }
        }
    }
}

void terminal_write(const char *data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        terminal_putchar(data[i]);
    }
}

void terminal_writestring(const char *data) {
    terminal_write(data, __builtin_strlen(data));
}

/* Kernel başlangıç */
void kernel_main(uint32_t magic, uint32_t addr) {
    terminal_initialize();
    
    terminal_writestring("=================================\n");
    terminal_writestring("  HilalBIS Operating System\n");
    terminal_writestring("=================================\n\n");
    
    terminal_writestring("Kernel basladi...\n");
    terminal_writestring("Multiboot Magic: 0x");
    
    /* Magic sayısını hex olarak yaz */
    for (int i = 7; i >= 0; i--) {
        uint8_t nibble = (magic >> (i * 4)) & 0xF;
        char hex_char = nibble < 10 ? '0' + nibble : 'A' + (nibble - 10);
        terminal_putchar(hex_char);
    }
    
    terminal_writestring("\n\nKernel calisiyorum...\n");
    terminal_writestring("Bekleyin...\n");
    
    /* Sonsuz döngü */
    while (1) {
        __asm__("hlt");
    }
}
