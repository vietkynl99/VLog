#ifndef _VLOG_H_
#define _VLOG_H_

#include <Arduino.h>

#define VLOG_SERIAL         Serial

#define VLOG_PRINT(...)     VLOG_SERIAL.print(__VA_ARGS__);
#define VLOG_PRINTLN(...)   VLOG_SERIAL.println(__VA_ARGS__);

#define VLOG(...)           VLog::print(TAG, __VA_ARGS__);
#define VLOG_NO_TAG(...)    VLog::print(nullptr, __VA_ARGS__);

class VLog
{
public:
    static void print(const char *tag, const char *pFormat, ...)
    {
        static char mStringBuffer[150];
        va_list pVlist;
        va_start(pVlist, pFormat);
        vsnprintf(mStringBuffer, sizeof(mStringBuffer) - 1, pFormat, pVlist);
        va_end(pVlist);

        if (tag)
        {
            VLOG_SERIAL.print('[');
            VLOG_SERIAL.print(tag);
            VLOG_SERIAL.print(']');
        }
        VLOG_SERIAL.println(mStringBuffer);
    }
};
#endif