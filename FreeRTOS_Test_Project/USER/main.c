#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"

/**
 * @description: ��ʼ������������
 * @param  {*}
 * @return {*}
 */
#define Start_task_PRIO 1				//����������Ҫʹ�����ȼ�0��һ��������ʹ�ã���ߵ����ȼ�31Ҳ����ʹ��
#define Start_task_SIZE 128				//�����ջ��С
TaskHandle_t Start_task_Hander;			//������
void Start_task(void *pvParameters);	//��ʼ����������


/**
 * @description:����һ��������
 * @param  {*}
 * @return {*}
 */
#define Task1_PRIO	2					//����һ���ȼ�
#define Tsak1_SIZE	50					//����һ��ջ��С
TaskHandle_t Task1_Hander;				//����һ������
void Task1_task(void *pvParameters);	//����һ������

/**
 * @description: �������������
 * @param  {*}
 * @return {*}
 */
#define Task2_PRIO	3					//��������ȼ�
#define Tsak2_SIZE	50					//�������ջ��С
TaskHandle_t Task2_Hander;				//�����������
void Task2_task(void *pvParameters);	//�����������

/**
 * @description: ����������
 * @param  {*}
 * @return {*}
 */
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);			//����ϵͳ�ж����ȼ�����4	 
	delay_init();	    									//��ʱ������ʼ��	  
	uart_init(115200);										//��ʼ������
	LED_Init();		  										//��ʼ��LED
	
    xTaskCreate((TaskFunction_t	)	Start_task,				//������
			   (char *			) 	"start_task",			//��������
			   (uint16_t		) 	Start_task_SIZE,		//�����ջ��С
			   (void *			) 	NULL,					//���ݸ��������Ĳ���
			   (UBaseType_t		) 	Start_task_PRIO,		//�������ȼ�
			   (TaskHandle_t *	) 	&Start_task_Hander);	//������
			   
	vTaskStartScheduler();         						 	//�����������  
}

/**
 * @description: ��ʼ����ִ�к���
 * @param  {*}
 * @return {*}
 * @param {void} *pvParameters
 */
void Start_task(void *pvParameters)							//��ʼ����ִ�к���
{
	//����task1
	xTaskCreate((TaskFunction_t	)	Task1_task,				//������
			   (char *			) 	"task1_task",			//��������
			   (uint16_t		) 	Tsak1_SIZE,				//�����ջ��С
			   (void *			) 	NULL,					//���ݸ��������Ĳ���
			   (UBaseType_t		) 	Task1_PRIO,				//�������ȼ�
			   (TaskHandle_t *	) 	&Task1_Hander);			//������	
	//����task2
	xTaskCreate((TaskFunction_t	)	Task2_task,				//������
			   (char *			) 	"task2_task",			//��������
			   (uint16_t		) 	Tsak2_SIZE,				//�����ջ��С
			   (void *			) 	NULL,					//���ݸ��������Ĳ���
			   (UBaseType_t		) 	Task2_PRIO,				//�������ȼ�
			   (TaskHandle_t *	) 	&Task2_Hander);			//������

	vTaskDelete(Start_task_Hander);							//ɾ������
}
/**
 * @description: ����һ������
 * @param  {*}
 * @return {*}
 * @param {void} *pvParameters
 */
void Task1_task(void *pvParameters)
{
	while (1)
	{
		LED0 = ~LED0;
		vTaskDelay(1000);			//�˴���Ӧʱ�ӽ��ģ�1ms���˴���Ϊ500ms
	}
	
}
	
/**
 * @description: �����������
 * @param  {*}
 * @return {*}
 * @param {void} *pvParameters
 */
void Task2_task(void *pvParameters)
{
	while (1)
	{
		LED1 = 1;
		vTaskDelay(1000);			//�˴���Ӧʱ�ӽ��ģ�1ms���˴���Ϊ500ms
		LED1 = 0;
		vTaskDelay(500);
	}
	
}

////��ʼ����������
//void start_task(void *pvParameters)
//{
//    taskENTER_CRITICAL();           //�����ٽ���
//    //����LED0����
//    xTaskCreate((TaskFunction_t )led0_task,     	
//                (const char*    )"led0_task",   	
//                (uint16_t       )LED0_STK_SIZE, 
//                (void*          )NULL,				
//                (UBaseType_t    )LED0_TASK_PRIO,	
//                (TaskHandle_t*  )&LED0Task_Handler);   
//    //����LED1����
//    xTaskCreate((TaskFunction_t )led1_task,     
//                (const char*    )"led1_task",   
//                (uint16_t       )LED1_STK_SIZE, 
//                (void*          )NULL,
//                (UBaseType_t    )LED1_TASK_PRIO,
//                (TaskHandle_t*  )&LED1Task_Handler);         
//    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
//    taskEXIT_CRITICAL();            //�˳��ٽ���
//}

////LED0������ 
//void led0_task(void *pvParameters)
//{
//    static float float_num=0.01;
//    while(1)
//    {
//        float_num+=0.01f;
//        taskENTER_CRITICAL();           //�����ٽ���
//        printf("float_num��ֵΪ: %.4f\r\n",float_num);   /*���ڴ�ӡ���*/
//        taskEXIT_CRITICAL();            //�˳��ٽ���
//        vTaskDelay(1000);
//    }
//}   

////LED1������
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
