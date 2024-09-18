#include "VLog.h"

Stream *VLog::mSerial = &Serial;
void (*VLog::pOnLogReceived)(const char *) = nullptr;

void VLog::init(Stream *serial)
{
    mSerial = serial;
}

void VLog::setOnLogReceived(void (*callback)(const char *))
{
    pOnLogReceived = callback;
}

void VLog::print(bool newline, const char *tag, const __FlashStringHelper *pFormat, ...)
{
    char buffer[VLOG_BUFFER_SIZE];
    char pcFormat[VLOG_FORMAT_SIZE];
    size_t prefixLength = 0;

    if (tag)
    {
        strcpy(buffer, "[");
        strcat(buffer, tag);
        strcat(buffer, "] ");
        prefixLength = strlen(buffer);
    }

    strncpy_P(pcFormat, (const char *)pFormat, sizeof(pcFormat));
    va_list pVlist;
    va_start(pVlist, pcFormat);
    vsnprintf(buffer + prefixLength, sizeof(buffer) - prefixLength - 1, pcFormat, pVlist);
    va_end(pVlist);

    if (newline && strlen(buffer) < VLOG_BUFFER_SIZE - 1)
    {
        size_t len = strlen(buffer);
        buffer[len] = '\n';
        buffer[len + 1] = '\0';
    }

    if (pOnLogReceived)
    {
        pOnLogReceived(buffer);
    }
    else if (mSerial)
    {
        mSerial->print(buffer);
    }
}