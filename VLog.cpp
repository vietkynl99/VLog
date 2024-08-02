#include "VLog.h"

Stream *VLog::mSerial = &Serial;

void VLog::init(Stream *serial)
{
    mSerial = serial;
}

void VLog::print(bool newline, const char *tag, const char *pFormat, ...)
{
    if (mSerial == nullptr)
    {
        return;
    }

    char mStringBuffer[VLOG_BUFFER_SIZE];
    va_list pVlist;
    va_start(pVlist, pFormat);
    vsnprintf(mStringBuffer, sizeof(mStringBuffer) - 1, pFormat, pVlist);
    va_end(pVlist);

    if (tag)
    {
        mSerial->print('[');
        mSerial->print(tag);
        mSerial->print(']');
    }
    mSerial->print(mStringBuffer);
    if (newline)
    {
        mSerial->println();
    }
}