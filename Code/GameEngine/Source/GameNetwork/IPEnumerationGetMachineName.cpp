// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// BFME1 GameNetwork/IPEnumeration.cpp donor for the machine-name lookup: WSA
// startup once (version 2.2 checked by byte), then gethostname into a stack
// buffer. Every failure returns the shared empty string; success copies the
// fresh hostname. The copy routes to the StringBase<char> copy pin, the fresh
// name to the PBD row, so this TU needs no string bodies of its own.

#define LOBYTE(w) ((unsigned char)(w))
#define HIBYTE(w) ((unsigned char)(((unsigned short)(w) >> 8) & 0xff))

struct WSADataBlock
{
    unsigned short version;
    unsigned short highVersion;
    char details[0x18A];
};

class AsciiString;

#include "ascii_string.h"


class EnumeratedIP;

class IPEnumeration
{
public:
    AsciiString getMachineName(void);

private:
    EnumeratedIP *m_IPlist;
    bool m_isWinsockInitialized;
};

extern "C" {
    __declspec(dllimport) int __stdcall WSAStartup(unsigned short version, WSADataBlock *data);
    __declspec(dllimport) int __stdcall WSACleanup(void);
    __declspec(dllimport) int __stdcall gethostname(char *name, int len);
}

// ?getMachineName@IPEnumeration@@QAE?AVAsciiString@@XZ
AsciiString IPEnumeration::getMachineName(void)
{
    if (!m_isWinsockInitialized)
    {
        WSADataBlock data;
        if (WSAStartup(0x202, &data) != 0)
            return AsciiString::TheEmptyString;
        if (LOBYTE(data.version) != 2 || HIBYTE(data.version) != 2)
        {
            WSACleanup();
            return AsciiString::TheEmptyString;
        }
        m_isWinsockInitialized = true;
    }
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) != 0)
        return AsciiString::TheEmptyString;
    return AsciiString(hostname);
}
