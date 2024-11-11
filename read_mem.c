/*
 *  read_mem.c
 *  Created on: 2024年7月29日
 *  Author: lyk
 */
#include "read_mem.h"
#include <stdio.h>
#define _DEBUG_INFO_

#define INPUT_SIZE 1024
#define ARRAY_SIZE 256

void delay(volatile int count) {
    while (count--) {
        // 空循环，用于延时
    }
}
// 普通的位操作函数，使用常规的位操作来实现像素置换任务
int normal_case(uint32_t *input, uint32_t output[4][ARRAY_SIZE / 32]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        int bit_position = i * 4;
        int input_index = bit_position / 32;
        int bit_offset = bit_position % 32;

        // 提取第1, 5, 9, ... 位到 output[0]
        if (input[input_index] & (1 << bit_offset)) {
            output[0][i / 32] |= (1 << (i % 32));
        }

        // 提取第2, 6, 10, ... 位到 output[1]
        bit_position++;
        input_index = bit_position / 32;
        bit_offset = bit_position % 32;
        if (input[input_index] & (1 << bit_offset)) {
            output[1][i / 32] |= (1 << (i % 32));
        }

        // 提取第3, 7, 11, ... 位到 output[2]
        bit_position++;
        input_index = bit_position / 32;
        bit_offset = bit_position % 32;
        if (input[input_index] & (1 << bit_offset)) {
            output[2][i / 32] |= (1 << (i % 32));
        }

        // 提取第4, 8, 12, ... 位到 output[3]
        bit_position++;
        input_index = bit_position / 32;
        bit_offset = bit_position % 32;
        if (input[input_index] & (1 << bit_offset)) {
            output[3][i / 32] |= (1 << (i % 32));
        }
    }
    // 打印输出结果
    printf("Normal case output:\n");
    for (int j = 0; j < 4; j++) {
        printf("Output[%d]: ", j);
        for (int i = 0; i < ARRAY_SIZE / 32; i++) {
            printf("%08x ", output[j][i]);
        }
        printf("\n");
    }
}
// 自定义的位操作指令，使用协处理器的位操作单元来实现像素置换任务
int nice_case(unsigned int *data) {
    // 使用自定义协处理器指令实现位操作任务
	// 读取数据
	        read_mem(data);
		    // 延时等待数据读取完成
		    delay(100); // 根据需要调整延时值
		    // 位提取操作
			bit_extract(33,8);
		    delay(100); // 根据需要调整延时值
			bit_extract(8225,9);
		    delay(100); // 根据需要调整延时值
			bit_extract(16449,10);
		    delay(100); // 根据需要调整延时值
			bit_extract(24673,11);

		    delay(100); // 根据需要调整延时值
			bit_deposit(12,13);
		    delay(100); // 根据需要调整延时值
			bit_permute(14,15);
}
//  读数据指令
//unsigned int *start_addr,
void read_mem ( unsigned int *data) {
    custom_ddread((int)data);

}
// 调用自定义的汇编指令 custom_permute
int bit_permute(int rs1, int rs2)
{
    custom_permute(rs1, rs2);
    return 0;
}
// 调用自定义的汇编指令 custom_extract
int bit_extract(int rs1, int rs2)
{
    custom_extract(rs1, rs2);
    return 0;
}
// 调用自定义的汇编指令 custom_deposit
int bit_deposit(int rs1, int rs2)
{
    custom_deposit(rs1, rs2);
    return 0;
}

