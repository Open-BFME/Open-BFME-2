// Native constructor and destructor 0x005D4433 and 0x005D40A6 establish the
// complete 0x40-byte layout and five virtual slots shared by checklist items.
#ifndef CANONICAL_RVA005D40A6_H
#define CANONICAL_RVA005D40A6_H

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"
#include "Rva0052413E.h"

class DisplayString;
struct ChecklistFontDesc;
struct FloatPair;

class Rva00524265
{
public:
    Rva00524265();
    ~Rva00524265();

private:
    char m_pad[0x0c];
};

class Rva005D40A6
{
public:
    Rva005D40A6(int level, const AsciiString &name, const ChecklistFontDesc &fontDesc);
    void OnClicked(const char *);
    void OnRollOver(const char *);
    void OnRollOut(const char *);
    void RenderText(const FloatPair &, const FloatPair &, unsigned int, unsigned int);
    void UpdateHeight();
    void Update();
    void rva005D46E3(const UnicodeString &);
    void rva005D472C();

    virtual ~Rva005D40A6();
    virtual void rva0047A69C(float);
    virtual void rva000B3FD0Slot08();
    virtual void rva000B3FD0Slot0C();
    virtual void rva000B3FD0Slot10();

private:
    int m_04;
    AsciiString m_08;
    Rva0052413E m_0c;
    Rva00524265 m_18;
    DisplayString *m_24;
    UnicodeString m_28;
    unsigned int m_color2C;
    float m_float30;
    int m_word34;
    float m_float38;
    unsigned char flag0 : 1;
    unsigned char flag1 : 1;
    unsigned char flag2 : 1;
    unsigned char flag3 : 1;
    unsigned char flag4 : 1;
    unsigned char flag5 : 1;
    unsigned char flag6 : 1;
    unsigned char flag7 : 1;
};

#endif
