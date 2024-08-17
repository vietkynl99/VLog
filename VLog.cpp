#include "VLog.h"

Stream *VLog::mSerial = &Serial;

void VLog::init(Stream *serial)
{
    mSerial = serial;
}

void VLog::print(bool newline, const char *tag, const __FlashStringHelper *pFormat, ...)
{
    char mStringBuffer[VLOG_BUFFER_SIZE];
    char pcFormat[VLOG_FORMAT_SIZE];

    strncpy_P(pcFormat, (const char*)pFormat, sizeof(pcFormat));

    va_list pVlist;
    va_start(pVlist, pcFormat);
    vsnprintf(mStringBuffer, sizeof(mStringBuffer) - 1, pcFormat, pVlist);
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