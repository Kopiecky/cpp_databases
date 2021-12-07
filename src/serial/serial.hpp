#ifndef SRC_SERIAL
#define SRC_SERIAL

#include <string>

class Serial
{
private:
    static const size_t NUM_OF_PARITIES = 3;

    enum StopBits
    {
        StopBits_1 = 1,
        StopBits_2,
        StopBits_Error
    };
    enum Parity
    {
        ParityOff = 1,
        ParityEven,
        ParityOdd,
        Parity_Error
    };
    enum NumberOfBits
    {
        NumberOfBits_5 = 5,
        NumberOfBits_6 = 6,
        NumberOfBits_7 = 7,
        NumberOfBits_8 = 8,
        NumberOfBits_Error
    };

    struct Parameters
    {
        std::string m_port;
        std::string m_parity;
        unsigned long int m_baudrate;
        unsigned int m_stopBits;
        unsigned int m_numberOfBits;


        Parameters() :
            m_port(0), m_parity(0), m_baudrate(0), m_stopBits(0), m_numberOfBits(0) {};
        Parameters(
            std::string port,
            std::string parity,
            unsigned long int baudrate,
            unsigned int stopBits,
            unsigned int numberOfBits) :
            m_port(port),
            m_parity(parity),
            m_baudrate(baudrate),
            m_stopBits(stopBits),
            m_numberOfBits(numberOfBits) {};
        ~Parameters() {};
    };

    Parameters parameters;
    int fd;


private:
    Parity checkParity(std::string parity);
    NumberOfBits checkNumberOfBits(unsigned int numberOfBits);
    StopBits checkStopBits(unsigned int stopBits);

public:
    Serial(
        std::string port           = "/dev/ttyUSB0",
        std::string parity         = "off",
        unsigned long int baudrate = 9600,
        unsigned int stopBits     = 1,
        unsigned int numberOfBits = 8);
    ~Serial();
    int connect();
    int readFromPort(uint8_t* buffer, size_t size);
    int writeToPort(const uint8_t* const msg, size_t size);
    void flush();
};

#endif