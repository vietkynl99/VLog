#ifndef _VLOG_H_
#define _VLOG_H_

#include <Arduino.h>

#define VLOG_PRINT(...)     VLog::print(false, nullptr, __VA_ARGS__);
#define VLOG_PRINTLN(...)   VLog::print(true, nullptr, __VA_ARGS__);
#define VLOG(...)           VLog::print(true, TAG, __VA_ARGS__);

#define VLOG_BUFFER_SIZE    128
#define VLOG_FORMAT_SIZE    64

class VLog
{
private:
    static Stream *mSerial;

public:
    static void init(Stream *serial);
    static void print(bool newline, const char *tag, const __FlashStringHelper *pFormat, ...);
};
#endif