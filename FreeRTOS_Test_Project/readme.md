### 实验器材:

战舰STM32F103 V3开发板

### 实验目的:

学习FreeRTOS在STM32F103上的移植

### 硬件资源:

DS0(连接在PB5)，DS1(连接在PE5上)

串口1(波特率:115200,PA9/PA10连接在板载USB转串口芯片CH340上面) 	

### 实验现象:

本实验在STM32F103开发板上移植了FreeRTOS，版本为V9.0.0。例程中创建了三个任务来测试移植是否成功。

start_task任务创建其他两个测试任务，led0_task任务中LED0闪烁，led1_task任务中LED1闪烁。

### 注意事项:

无. 

参考资料：STM32F103 FreeRTOS开发手册.pdf 第二章


-------------------------------------------------------------------------------------------



