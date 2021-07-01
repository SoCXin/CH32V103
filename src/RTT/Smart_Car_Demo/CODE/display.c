#include "headfile.h"
#include "encoder.h"
#include "display.h"





void display_entry(void *parameter)
{
    uint32 count=0;

    while(1)
    {
        ips114_displayimage032(mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
        count++;

        ips114_showint16(0, 4, icm_gyro_x);
        ips114_showint16(0, 5, icm_acc_x);
        ips114_showint16(0, 6, encoder_data[0]);
        ips114_showint32(0, 7, count, 10);
    }
    
}





void display_init(void)
{
    rt_thread_t tid1;

    //初始化屏幕
    ips114_init();
    
    //创建显示线程 优先级设置为6 
    tid1 = rt_thread_create("display", display_entry, RT_NULL, 1024, 6, 50);
    
    //启动显示线程
    if(RT_NULL != tid1)
    {
        rt_thread_startup(tid1);
    }
}
