// See LICENSE for license details.
// 这是定义了三条位操作指令以及读ddr指令的工程。
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "hbird_sdk_soc.h"
#include "read_mem.h"

#define INPUT_SIZE 1024
#define ARRAY_SIZE 256
// 输入数据为1024位，这里用一个uint32_t数组来表示
uint32_t data_in[INPUT_SIZE / 32];
// 输出的4个256位数组，每个数组为256位，可以用uint32_t数组表示
uint32_t output_normal[4][ARRAY_SIZE / 32];
uint32_t output_nice  [4][ARRAY_SIZE / 32];


int main(void)
{

	    unsigned int write_data[32] = {21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,
	    37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52};
//	    // 读取数据
//	    read_mem(write_data);
//
//	    // 延时等待数据读取完成
//	    delay(1000); // 根据需要调整延时值
//	    // 位提取操作
//		bit_extract(33,8);
//	    delay(1000); // 根据需要调整延时值
//		bit_extract(8225,9);
//	    delay(1000); // 根据需要调整延时值
//		bit_extract(16449,10);
//	    delay(1000); // 根据需要调整延时值
//		bit_extract(24673,11);
//
//	    delay(1000); // 根据需要调整延时值
//		bit_deposit(12,13);
//	    delay(1000); // 根据需要调整延时值
//		bit_permute(14,15);

    // 初始化输入数据 data_in，随机生成1024位数据
			srand(time(NULL));
			for (int i = 0; i < INPUT_SIZE / 32; i++) {
				data_in[i] = rand();
			}
		    unsigned int begin_instret, end_instret, instret_normal, instret_nice;
		    unsigned int begin_cycle, end_cycle, cycle_normal, cycle_nice;

		    printf("**********************************************\n");
		    printf("** begin to process the pixel displacement task using ordinary bit operation\n");

		    begin_instret = __get_rv_instret();
		    begin_cycle = __get_rv_cycle();

		    normal_case(data_in, output_normal);

		    end_instret = __get_rv_instret();
		    end_cycle = __get_rv_cycle();

		    instret_normal = end_instret - begin_instret;
		    cycle_normal = end_cycle - begin_cycle;

		    printf("\n");

		    printf("**********************************************\n");
		    printf("** begin to process the pixel displacement task using nice bit operation\n");

		    begin_instret = __get_rv_instret();
		    begin_cycle = __get_rv_cycle();

		    nice_case(write_data);

		    end_instret = __get_rv_instret();
		    end_cycle = __get_rv_cycle();

		    instret_nice = end_instret - begin_instret;
		    cycle_nice = end_cycle - begin_cycle;

		    printf("**********************************************\n");
		    printf("** performance list \n");

		    printf("\t normal: \n");
		    printf("\t      instret: %d, cycle: %d \n", instret_normal, cycle_normal);
		    printf("\t nice  : \n");
		    printf("\t      instret: %d, cycle: %d \n", instret_nice, cycle_nice);

		    printf("**********************************************\n\n");
		    return 0;
}

//rs1编码格式，0-4bit共5位代表第几行，5-12bit共8bit代表在那一行的第几个32位位置，13-31共19位代表我要放到暂存寄存器组的第几个位置
