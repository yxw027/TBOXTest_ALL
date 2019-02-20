#ifndef UARTCHECK_H
#define UARTCHECK_H
#include <QDebug>
#include <QString>
extern "C"
{
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <termios.h>
    #include <unistd.h>

}

class UartCheck
{
public:
    UartCheck();
    ~UartCheck();
    bool uart_open();
    int uart_set();
    bool uart_read();
    int uart_write();
    bool uart_close();
public:
    int fd;
};

#endif // UARTCHECK_H
