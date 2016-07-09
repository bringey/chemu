#include "chemu/memory.h"

#include <string.h>
#include <stddef.h>

const uint8_t FONTSET[] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void chipmem_init(ChipMem *mem) {
    // copy the fontset
    memcpy(mem->reserved.fontset, FONTSET, sizeof(FONTSET) / sizeof(uint8_t));
    // clear the rest
    memset(mem->array + sizeof(ChipMem_reserved), 0, CHIP_END - sizeof(ChipMem_reserved));
}

inline uint8_t chipmem_read(ChipMem *mem, ChipAddress addr) {
    return (addr <= CHIP_END) ? mem->array[addr] : 0;
}

inline bool chipmem_write(ChipMem *mem, ChipAddress addr, uint8_t value) {
    // check if the address is not in the reserved portion of memory
    if (addr >= CHIP_PRGM_START) {
        mem->array[addr] = value;
        return true;
    }
    return false;
}


ChipAddress chipmem_get_font(ChipMem *mem, uint8_t digit) {
    return offsetof(ChipMem_reserved, fontset) + (digit * 5);
}
