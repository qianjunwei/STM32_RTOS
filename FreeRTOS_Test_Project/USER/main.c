#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"

/**
 * @description: 开始任务声明部分
 * @param  {*}
 * @return {*}
 */
#define Start_task_PRIO 1				//空闲任务需要使用优先级0，一般任务不能使用，最高的优先级31也不能使用
#define Start_task_SIZE 128				//任务堆栈大小
TaskHandle_t Start_task_Hander;			//任务句柄
void Start_task(void *pvParameters);	//开始任务函数声明


/**
 * @description:任务一声明部分
 * @param  {*}
 * @return {*}
 */
#define Task1_PRIO	2					//任务一优先级
#define Tsak1_SIZE	50					//任务一堆栈大小
TaskHandle_t Task1_Hander;				//任务一任务句柄
void Task1_task(void *pvParameters);	//任务一任务函数

/**
 * @description: 任务二声明部分
 * @param  {*}
 * @return {*}
 */
#define Task2_PRIO	3					//任务二优先级
#define Tsak2_SIZE	50					//任务二堆栈大小
TaskHandle_t Task2_Hander;				//任务二任务句柄
void Task2_task(void *pvParameters);	//任务二任务函数

/**
 * @description: 主函数部分
 * @param  {*}
 * @return {*}
 */
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);			//设置系统中断优先级分组4	 
	delay_init();	    									//延时函数初始化	  
	uart_init(115200);										//初始化串口
	LED_Init();		  										//初始化LED
	
    xTaskCreate((TaskFunction_t	)	Start_task,				//任务函数
			   (char *			) 	"start_task",			//任务名称
			   (uint16_t		) 	Start_task_SIZE,		//任务堆栈大小
			   (void *			) 	NULL,					//传递给任务函数的参数
			   (UBaseType_t		) 	Start_task_PRIO,		//任务优先级
			   (TaskHandle_t *	) 	&Start_task_Hander);	//任务句柄
			   
	vTaskStartScheduler();         						 	//开启任务调度  
}

/**
 * @description: 开始任务执行函数
 * @param  {*}
 * @return {*}
 * @param {void} *pvParameters
 */
void Start_task(void *pvParameters)							//开始任务执行函数
{
	//创建task1
	xTaskCreate((TaskFunction_t	)	Task1_task,				//任务函数
			   (char *			) 	"task1_task",			//任务名称
			   (uint16_t		) 	Tsak1_SIZE,				//任务堆栈大小
			   (void *			) 	NULL,					//传递给任务函数的参数
			   (UBaseType_t		) 	Task1_PRIO,				//任务优先级
			   (TaskHandle_t *	) 	&Task1_Hander);			//任务句柄	
	//创建task2
	xTaskCreate((TaskFunction_t	)	Task2_task,				//任务函数
			   (char *			) 	"task2_task",			//任务名称
			   (uint16_t		) 	Tsak2_SIZE,				//任务堆栈大小
			   (void *			) 	NULL,					//传递给任务函数的参数
			   (UBaseType_t		) 	Task2_PRIO,				//任务优先级
			   (TaskHandle_t *	) 	&Task2_Hander);			//任务句柄

	vTaskDelete(Start_task_Hander);							//删除任务
}
/**
 * @description: 任务一任务函数
 * @param  {*}
 * @return {*}
 * @param {void} *pvParameters
 */
void Task1_task(void *pvParameters)
{
	while (1)
	{
		LED0 = ~LED0;
		vTaskDelay(1000);			//此处对应时钟节拍，1ms。此处即为500ms
	}
	
}
	
/**
 * @description: 任务二任务函数
 * @param  {*}
 * @return {*}
 * @param {void} *pvParameters
 */
void Task2_task(void *pvParameters)
{
	while (1)
	{
		LED1 = 1;
		vTaskDelay(1000);			//此处对应时钟节拍，1ms。此处即为500ms
		LED1 = 0;
		vTaskDelay(500);
	}
	
}

////开始任务任务函数
//void start_task(void *pvParameters)
//{
//    taskENTER_CRITICAL();           //进入临界区
//    //创建LED0任务
//    xTaskCreate((TaskFunction_t )led0_task,     	
//                (const char*    )"led0_task",   	
//                (uint16_t       )LED0_STK_SIZE, 
//                (void*          )NULL,				
//                (UBaseType_t    )LED0_TASK_PRIO,	
//                (TaskHandle_t*  )&LED0Task_Handler);   
//    //创建LED1任务
//    xTaskCreate((TaskFunction_t )led1_task,     
//                (const char*    )"led1_task",   
//                (uint16_t       )LED1_STK_SIZE, 
//                (void*          )NULL,
//                (UBaseType_t    )LED1_TASK_PRIO,
//                (TaskHandle_t*  )&LED1Task_Handler);         
//    vTaskDelete(StartTask_Handler); //删除开始任务
//    taskEXIT_CRITICAL();            //退出临界区
//}

////LED0任务函数 
//void led0_task(void *pvParameters)
//{
//    static float float_num=0.01;
//    while(1)
//    {
//        float_num+=0.01f;
//        taskENTER_CRITICAL();           //进入临界区
//        printf("float_num的值为: %.4f\r\n",float_num);   /*串口打印结果*/
//        taskEXIT_CRITICAL();            //退出临界区
//        vTaskDelay(1000);
//    }
//}   

////LED1任务函数
//void led1_task(void *pvParameters)
//{
//    while(1)
//    {
//        LED1=0;
//        vTaskDelay(200);
//        LED1=1;
//        vTaskDelay(800);
//    }
//}
