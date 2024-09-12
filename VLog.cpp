#include "VLog.h"

VVector<Stream *> *VLog::mStreamList = nullptr;

void VLog::init(Stream *serial)
{
    if (mStreamList)
    {
        delete mStreamList;
        mStreamList = nullptr;
    }
    mStreamList = new VVector<Stream *>(1);
    mStreamList->push_back(serial ? serial : &Serial);
}

void VLog::init(const VVector<Stream *> &streamList)
{
    if (mStreamList)
    {
        delete mStreamList;
        mStreamList = nullptr;
    }
    mStreamList = new VVector<Stream *>();
    *mStreamList = streamList;
}

void VLog::print(bool newline, const char *tag, const __FlashStringHelper *pFormat, ...)
{
    if (!mStreamList)
    {
        return;
    }

    char mStringBuffer[VLOG_BUFFER_SIZE];
    char pcFormat[VLOG_FORMAT_SIZE];

    strncpy_P(pcFormat, (const char *)pFormat, sizeof(pcFormat));

    va_list pVlist;
    va_start(pVlist, pcFormat);
    vsnprintf(mStringBuffer, sizeof(mStringBuffer) - 1, pcFormat, pVlist);
    va_end(pVlist);

    for (int i = 0; i < mStreamList->size(); i++)
    {
        if (tag)
        {
            mStreamList->at(i)->print('[');
            mStreamList->at(i)->print(tag);
            mStreamList->at(i)->print("] ");
        }
        mStreamList->at(i)->print(mStringBuffer);
        if (newline)
        {
            mStreamList->at(i)->println();
        }
    }
}