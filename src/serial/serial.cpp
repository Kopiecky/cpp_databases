#include "serial.hpp"

#include <fcntl.h>
#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>

Serial::Serial(
    std::string port,
    std::string parity,
    unsigned long int baudrate,
    unsigned int stopBits,
    unsigned int numberOfBits) :
    parameters(port, parity, baudrate, stopBits, numberOfBits), fd(0)
{
}

Serial::~Serial()
{
    close(fd);
}

Serial::Parity Serial::checkParity(std::string parity)
{
    Parity ret;
    if (!parity.compare("even"))
    {
        ret = ParityEven;
    }
    else if (!parity.compare("off"))
    {
        ret = ParityOff;
    }
    else if (!parity.compare("odd"))
    {
        ret = ParityOdd;
    }
    else
    {
        ret = Parity_Error;
    }
    return ret;
}

Serial::NumberOfBits Serial::checkNumberOfBits(unsigned int numberOfBits)
{
    NumberOfBits ret;
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
        default:
            ret = NumberOfBits_Error;
            break;
    }
    return ret;
}

Serial::StopBits Serial::checkStopBits(unsigned int stopBits)
{
    StopBits ret;
    switch (stopBits)
    {
        case 1:
            ret = StopBits_1;
            break;
        case 2:
            ret = StopBits_2;
            break;
        default:
            ret = StopBits_Error;
            break;
    }
    return ret;
}

int Serial::connect()
{
    struct termios tty = {0};

    int fd = open(parameters.m_port.c_str(), O_RDWR);

    if (fd > 0)
    {
        if (tcgetattr(fd, &tty) != 0)
        {
            fd = -1;
            std::cout << "Device doesn't exist\n";
        }
        else
        {
            tty.c_cflag |= (CLOCAL | CREAD);
            tty.c_cflag &= ~CSIZE;

            switch (checkNumberOfBits(parameters.m_numberOfBits))
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

            switch (checkParity(parameters.m_parity))
            {
                case ParityOff:
                    tty.c_cflag &= ~PARENB;
                    break;
                case ParityOdd:
                    tty.c_cflag |= PARENB;
                    tty.c_cflag |= PARODD;
                    break;
                case ParityEven:
                    tty.c_cflag |= PARENB;
                    tty.c_cflag &= ~PARODD;
                    break;
            }

            switch (checkStopBits(parameters.m_stopBits))
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

            switch (parameters.m_baudrate)
            {
                case 4800:
                    cfsetispeed(&tty, B4800);
                    cfsetospeed(&tty, B4800);
                    break;
                case 9600:
                    cfsetispeed(&tty, B9600);
                    cfsetospeed(&tty, B9600);
                    break;
                case 19200:
                    cfsetispeed(&tty, B19200);
                    cfsetospeed(&tty, B19200);
                    break;
                case 115200:
                    cfsetispeed(&tty, B115200);
                    cfsetospeed(&tty, B115200);
                    break;
                default:
                    cfsetispeed(&tty, B115200);
                    cfsetispeed(&tty, B115200);
            }

            if (tcsetattr(fd, TCSANOW, &tty) != 0)
            {
                fd = -1;
                std::cout << "Device doesn't exist\n";
            }
            else
            {
                std::cout << "Connected with device on: " << parameters.m_port << std::endl;
            }
        }
    }
    else
    {
        std::cout << "Device doesn't exist\n";
    }
    return fd;
}

int Serial::readFromPort(uint8_t* buffer, size_t size)
{
    if (fd >= 0)
    {
        return read(fd, buffer, size);
    }
    else
    {
        return fd;
    }
}

int Serial::writeToPort(const uint8_t* const msg, size_t size)
{
    if (fd >= 0)
    {
        return write(fd, msg, size);
    }
    else
    {
        return fd;
    }
}

void Serial::flush()
{
    sleep(1);
    tcflush(fd, TCIOFLUSH);
}