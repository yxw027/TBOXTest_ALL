#include "uartcheck.h"
//https://www.cnblogs.com/xiaojianliu/p/8473116.html
//https://blog.csdn.net/baweiyaoji/article/details/72885633
#define UART2 ""
#define BAUDE B9600

UartCheck::UartCheck()
{
    if(uart_open())
    {
       uart_set();
       uart_write();
       sleep(1);
       if(uart_read())
       {
           qDebug()<<"串口测试成功";
       }
       uart_close();
    }
}

UartCheck::~UartCheck()
{}

bool UartCheck::uart_open()
{
    fd = open(UART2, O_RDWR, O_NONBLOCK);
    if(fd == -1)
    {
        qDebug()<<"############## uart_open uart is fail!!!";
        return false;
    }
    else
        return true;
}

int UartCheck::uart_set()
{
    struct termios options;
    if(tcgetattr(fd,&options) < 0)
    {
        qDebug()<<"############## uart_set 获取终端属性失败!!!";
        return -1;
    }
    cfsetispeed(&options,BAUDE);
    cfsetospeed(&options,BAUDE);
    options.c_cflag |= CLOCAL;//保证程序不占用串口
    //options.c_cflag |= CREAD;//保证程序可以从串口中读取数据

    options.c_cflag &= ~CRTSCTS;//不进行流控制---
    options.c_cflag &= ~CSIZE;//屏蔽其它标志位---

    options.c_cflag |= CS8;//数据位8位

    options.c_cflag &= ~PARENB;//无奇偶校验

    options.c_cflag &= ~CSTOPB;//CSTOPB：使用1位停止位

    if(tcsetattr(fd,TCSANOW,&options) < 0)
        {
            qDebug()<<"############## uart_set 配置终端属性失败!!!";
            return -1;
        }
}

bool UartCheck::uart_read()
{
    char r_buf[10];
    int r_num = read(fd, r_buf, 10);
    if(r_num < 0)
    {
      qDebug()<<"uart_read read buf if fail!!!";
    }
    QString str=r_buf;
    qDebug("uart_read r_buf=%s", r_buf);
    if(str.contains("hello"))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int UartCheck::uart_write()
{
    char* w_buf = "hello";
    int w_num = write(fd, w_buf, sizeof(w_buf));
    int re_num = 5 - w_num;
    while(re_num)
    {
       qDebug()<<"---";
       w_num = write(fd, w_buf+w_num, re_num);
       re_num = re_num-w_num;
    }
    return w_num;
}

bool UartCheck::uart_close()
{
    if( close(fd) != 0 )
    {
        return false;
    }
    return true;
}
