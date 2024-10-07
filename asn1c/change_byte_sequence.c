#include <stdint.h>

// 将2字节的小端整数转换为大端
uint16_t convert_2_bytes_little_to_big(uint16_t little_endian)
{
    return (little_endian >> 8) | (little_endian << 8);
}

// 将3字节的小端整数转换为大端
uint32_t convert_3_bytes_little_to_big(uint32_t little_endian)
{
    return ((little_endian & 0x0000FF) << 16) | // 提取第1个字节并移到最高位
           ((little_endian & 0x00FF00)) |       // 保持中间的字节不变
           ((little_endian & 0xFF0000) >> 16);  // 提取第3个字节并移到最低位
}

// 函数：将4字节的小端整数转换为大端
uint32_t convert_4_bytes_little_to_big(uint32_t little_endian)
{
    return ((little_endian & 0x000000FF) << 24) |
           ((little_endian & 0x0000FF00) << 8) |
           ((little_endian & 0x00FF0000) >> 8) |
           ((little_endian & 0xFF000000) >> 24);
}

// 函数：将8字节的小端整数转换为大端
uint64_t convert_8_bytes_little_to_big(uint64_t little_endian)
{
    return ((little_endian & 0x00000000000000FF) << 56) |
           ((little_endian & 0x000000000000FF00) << 40) |
           ((little_endian & 0x0000000000FF0000) << 24) |
           ((little_endian & 0x00000000FF000000) << 8) |
           ((little_endian & 0x000000FF00000000) >> 8) |
           ((little_endian & 0x0000FF0000000000) >> 24) |
           ((little_endian & 0x00FF000000000000) >> 40) |
           ((little_endian & 0xFF00000000000000) >> 56);
}