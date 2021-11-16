class Serial
{
private:
    typedef enum StopBits_e
    {
        StopBits_1 = 1,
        StopBits_2
    } StopBits_t;

    typedef enum Parity_e
    {
        Parity_Off = 1,
        Parity_Even,
        Parity_Odd
    } Parity_t;

    typedef enum NumberOfBits_e
    {
        NumberOfBits_5 = 5,
        NumberOfBits_6,
        NumberOfBits_7,
        NumberOfBits_8
    } NumberOfBits_t;

    typedef struct Params_s
    {
        const char* m_port;
        unsigned int m_baudrate;
        StopBits_t m_stopBits;
        Parity_t m_parity;
        NumberOfBits_t m_numberOfBits;
    } Params_t;

    Params_t params;

    int fd;

private:
    Parity_t checkParity(const char* const parity);
    NumberOfBits_t checkNumberOfBits(unsigned int numberOfBits);
    StopBits_t checkStopBits(unsigned int stopBits);
    int serial_open();

public:
    Serial(
        const char* const port,
        const char* const parity,
        unsigned int baudrate,
        unsigned int stopBits,
        unsigned int numberOfBits);
    ~Serial();
    int serial_write(const void* const msg, unsigned int size);
    int serial_read(void* buffer, unsigned int size);
};