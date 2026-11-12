// Retail page view: constructor 0x0050EA74 and primary table 0x0086551C.
// Existing row-list consumers establish the show/hide slot order.
#ifndef RVA0050EA74_H
#define RVA0050EA74_H

#include "ascii_string.h"

class Rva0050EA74Base
{
public:
    Rva0050EA74Base() : m_04(0) {}
    __forceinline virtual ~Rva0050EA74Base() {}
    int m_04;
};

class Rva0050EA74 : public Rva0050EA74Base
{
public:
    Rva0050EA74(int a, const AsciiString &b);
    virtual ~Rva0050EA74();
    virtual void show();
    virtual void hide();
    virtual int v03(int message, int key, int state) { return 0; }
    virtual int v04(int message, int key, int state) { return 0; }
    // Native slot 5 remains to be recovered; this table is still bridged.

    int m_08;
    AsciiString m_0c;
    unsigned char m_10;
};

#endif
