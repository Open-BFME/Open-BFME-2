// Target facts (code addresses are RVAs; tables are VAs): allocation 0x002A63ED pushes 0x54 before operator new 0x002A63F9 and constructor call 0x002A640C. Constructor 0x004E6C34 installs 0x00C62440 at 0x004E6C57; destructor 0x004E6A9B restores it at 0x004E6AAC, destroys members, then stores five-purecall table 0x00C078DC at 0x004E6B28. The final store is abstract-base teardown, not the concrete table. Purecall folding does not establish a registered parent identity; this declaration models the primary five-slot ABI. The destructor is nonvirtual: no table slot points to it, and scalar deleting destructor 0x0029B235 calls it directly at 0x0029B238.
// Table 0x00C62440 contains exactly five code pointers: 0x00578522, 0x004E6B7D, 0x004E725F, 0x004E6B9B and 0x004E6882; the next word is the string "Hide". Their ledger spellings prove the declarations below, including DoClose at slot 3. Getter 0x00578522 reads byte +0x50. Constructor stores at 0x004E6C49/0x004E6C5D establish dwords +4/+8; calls 0x004E6C60/0x004E6C6C/0x004E6C78/0x004E6C84 initialize twelve-byte members at +0x0C/+0x18/+0x24/+0x30. Destructor calls 0x004E6B20/0x004E6B14/0x004E6B08/0x004E6AFC identify their teardown as 0x0052413E/0x005241B0/0x00524265/0x005242D7. Only the first member has a registered header; the other member identities remain opaque.
// Stores 0x004E6C8C..0x004E6C97 establish float +0x3C and dwords +0x40/+0x44/+0x48; 0x004E6CB6..0x004E6CBC establish the display-string pointer +0x4C and bytes +0x50/+0x51. Destructor calls 0x004E6AE4/0x004E6AF0 clear the four-byte owners +0x44/+0x40 through 0x004E6A1D; only their pointer storage is exposed here. Nonvirtual method rows: rva004E67D0 0x004E67D0, ExternMessageWidth 0x004E6801, OnInitialized 0x004E67A3, RenderMessage 0x004E6898, CloseImmediately 0x004E6B38, OnClosed 0x004E6BD2, Open 0x004E6F30, rva004E7019 0x004E7019, UpdateNotice 0x004E701E. All rowed methods remain out-of-line declarations.
#ifndef BFME2_INGAMENOTIFICATIONBOXMOVIECLIP_H
#define BFME2_INGAMENOTIFICATIONBOXMOVIECLIP_H

#include "../Common/Rva0052413E.h"

class UnicodeString;
class Rva002217EA;
class Coord2D;
class DisplayString;

class InGameNotificationBoxMovieClip
{
public:
    InGameNotificationBoxMovieClip();
    ~InGameNotificationBoxMovieClip();

    virtual unsigned char rva00578522() const;
    virtual void rva004E6B7D(bool);
    virtual void rva004E725F(const UnicodeString &, const Rva002217EA &, int);
    virtual void DoClose();
    virtual int rva004E6882();

    void rva004E67D0(int);
    void ExternMessageWidth(int, const char *, bool);
    void OnInitialized(unsigned int);
    void RenderMessage(const Coord2D *, const Coord2D *, void *, void *);
    void CloseImmediately();
    void OnClosed(unsigned int);
    void Open(const UnicodeString &, const Rva002217EA &, int, bool, int);
    void rva004E7019();
    void UpdateNotice();

private:
    int m_04;
    int m_field08;
    Rva0052413E m_field0C;
    __declspec(align(4)) char m_field18[12];
    __declspec(align(4)) char m_field24[12];
    __declspec(align(4)) char m_field30[12];
    float m_field3C;
    void *m_field40;
    void *m_field44;
    unsigned int m_field48;
    DisplayString *m_field4C;
    unsigned char m_field50;
    bool m_field51;
};

#endif
