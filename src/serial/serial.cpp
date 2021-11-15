#include "serial.hpp"
#include <termios.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

Serial::Serial(const char* const port, const char* const parity, unsigned int baudrate, unsigned int stopBits, unsigned int numberOfBits)
{
    params = 
    {
        .m_port = port,
        .m_baudrate = baudrate,
        .m_parity = checkParity(parity),
        .m_numberOfBits = checkNumberOfBits(numberOfBits),
    };
    serial_open();
}

Serial::~Serial()
{
    std::cout << "Connection closed" << std::endl;
    close(fd);
}

Serial::Parity_t Serial::checkParity(const char* const parity)
{
    Parity_t ret;

    if(!strcmp("EVEN", parity))
    {
        ret = Parity_Even;
    }
    if(!strcmp("ODD", parity))
    {
        ret = Parity_Odd;
    }
    if(!strcmp("NONE", parity))
    {
        ret = Parity_Off;
    }
    return ret;
}

Serial::NumberOfBits_t Serial::checkNumberOfBits(unsigned int numberOfBits)
{
    NumberOfBits_t ret;

    switch (numberOfBits)
    {
        case 5:
            ret = NumberOfBits_5;
            break;
        case 6:
            ret = NumberOfBits_6;
            break;
        case 7:
            ret = NumberOfBits_7;
            break;
        case 8:
            ret = NumberOfBits_8;
            break;
    }
    return ret;
}

Serial::StopBits_t Serial::checkStopBits(unsigned int stopBits)
{
    StopBits_t ret;

    switch (stopBits)
    {
        case 1:
            ret = StopBits_1;
            break;
        case 2:
            ret = StopBits_2;
            break;
    }
    return ret;
}

int Serial::serial_open()
{
    struct termios tty = {0};

    fd = open(params.m_port, O_RDWR);

    if (fd > 0)
    {
        if (tcgetattr(fd, &tty) != 0)
        {
            fd = -1;
        }
        else
        {
            tty.c_cflag |= (CLOCAL | CREAD);
            tty.c_cflag &= ~CSIZE;

        switch (params.m_numberOfBits)
            {
                case NumberOfBits_5:
                    tty.c_cflag |= CS5;
                    break;
                case NumberOfBits_6:
                    tty.c_cflag |= CS6;
                    break;
                case NumberOfBits_7:
                    tty.c_cflag |= CS7;
                    break;
                case NumberOfBits_8:
                    tty.c_cflag |= CS8;
                    break;
            }

            switch (params.m_parity)
            {
                case Parity_Off:
                    tty.c_cflag &= ~PARENB;
                    break;
                case Parity_Odd:
                    tty.c_cflag |= PARENB;
                    tty.c_cflag |= PARODD;
                    break;
                case Parity_Even:
                    tty.c_cflag |= PARENB;
                    tty.c_cflag &= ~PARODD;
                    break;
            }
            
            switch (params.m_stopBits)
            {
                case StopBits_1:
                    tty.c_cflag &= ~CSTOPB;
                    break;
                case StopBits_2:
                    tty.c_cflag |= CSTOPB;
                    break;
            }

            tty.c_cflag &= ~CRTSCTS;

            tty.c_iflag &=
                ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
            tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
            tty.c_oflag &= ~OPOST;

            tty.c_cc[VTIME] = 0;
            tty.c_cc[VMIN]  = 1;

            if (tcsetattr(fd, TCSANOW, &tty) != 0)
            {
                fd = -1;
            }
            else
            {
                std::cout << "Connected with device on: " << params.m_port << std::endl;
            }
        }
    }
    return 0;
}


int Serial::serial_read(void* buffer, unsigned int size)
{
    return read(fd, buffer, size);
}

int Serial::serial_write(const void* const msg, unsigned int size)
{
    return write(fd, msg, size);
}