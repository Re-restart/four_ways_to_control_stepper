# four_ways_to_control_stepper
一个低成本的，使用stm32精密控制步进电机的通用方案<br>

芯片选用的是stm32f103zet6,全程未使用编码器/PID,电机驱动器用的是最简单常见的TB6612,主打一个好复现且好上手。电机控制比较稳定，可以根据自己需要选择控制方式<br>

本来并没有作为项目准备，因此也并没有录什么视频。但最近确实做了一些工作，可以看成是在重新布局和完善这个项目：
https://github.com/Re-restart/A-low-cost-robotic-arm-automatic-sorting-line<br>

其他芯片原理类似，这里不再赘述。具体代码解析见我的csdn文章：
https://blog.csdn.net/weixin_53318879/article/details/145791412?spm=1001.2014.3001.5502


pulse_CCR_delaystop：定时器比较输出，延时控制停止<br>
pulse_CCR_IT_LeftRight：定时器比较输出，按钮切换正反转<br>
pulse_PWM_LeftRight：定时器pwm输出，按钮切换正反转<br>
vcc_gnd：模拟io控制<br>
zhongduan：定时器中断溢出方式控制电机<br>
