/*
 * read_mem.h
 *
 *  Created on: 2024年7月30日
 *      Author: pc
 */

#ifndef APPLICATION_READ_MEM_H_
#define APPLICATION_READ_MEM_H_

#include <hbird_sdk_soc.h>

#define INPUT_SIZE 1024
#define ARRAY_SIZE 256


// custom ddread
__STATIC_FORCEINLINE void custom_ddread(int addr)
{
    int zero = 0;
    
    asm volatile (
       ".insn r 0x7b, 2, 7, x0, %1, x0"
           :"=r"(zero)
           :"r"(addr)
     );
}
// custom_permute
__STATIC_FORCEINLINE void custom_permute(int rs1,int rs2)
{
    int zero = 0;

    asm volatile (
       ".insn r 0x7b, 3, 8, x0, %1, %2"
           :"=r"(zero)
           :"r"(rs1),"r"(rs2)
     );
}
// custom_extract
__STATIC_FORCEINLINE void custom_extract(int rs1,int rs2)
{
    int zero = 0;

    asm volatile (
       ".insn r 0x7b, 3, 9, x0, %1, %2"
           :"=r"(zero)
           :"r"(rs1),"r"(rs2)
     );
}
// custom_deposit
__STATIC_FORCEINLINE void custom_deposit(int rs1,int rs2)
{
    int zero = 0;

    asm volatile (
       ".insn r 0x7b, 3, 10, x0, %1, %2"
           :"=r"(zero)
           :"r"(rs1),"r"(rs2)
     );
}
void read_mem( unsigned int *data);//unsigned int *start_addr,
int bit_permute(int rs1, int rs2);
int bit_extract(int rs1, int rs2);
int bit_deposit(int rs1, int rs2);

// normal test case without NICE accelerator.
int normal_case(uint32_t *input, uint32_t output[4][ARRAY_SIZE / 32]);

// teat case using NICE accelerator.
int nice_case(unsigned int *data);

#endif /* APPLICATION_READ_MEM_H_ */
