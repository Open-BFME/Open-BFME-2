// Target facts (code addresses are RVAs): allocation 0x006CF9D3 requests 0xB4 bytes, calls constructor 0x006E6060 at 0x006CF9F4 and stores its result in the shared pool global at VA 0x00E176D0 at 0x006CFA06. Constructor 0x006E6060 and nonvirtual destructor 0x006E6430 contain no vptr stores or base calls; +0 is an allocated array (0x006E6219), freed as storage at 0x006E64A9. This class has no virtual functions. Its lifetime rows use the opaque receiver name Rva006E6060Root; no constructor or destructor row bears Rva006E34D0. The four eight-byte members at +8/+0x18/+0x20/+0x28 have word count/capacity and pointer+4 (0x006E6082..0x006E6176), with destructor calls at 0x006E64F3/0x006E6500/0x006E650D/0x006E651D. The display member occupies +0x30 and calls 0x006F7FF0/0x006F84F0 through 0x006E6180/0x006E64E6.
// Target facts: constructor 0x006E6188..0x006E61A3 stores words +0xA4/+0xA8/+0xAC/+0xB0; 0x006E627D..0x006E628E supplies +0x14 with 0x1C-stride storage; 0x006E6291..0x006E62DA supplies +0x34 with 0x20-stride timers using rowed callbacks 0x006E3CF0/0x006E4F60. Stores 0x006E6342..0x006E63AC initialize pointer+0x40, words+4/+0x10/+0x38/+0x3C/+0x6C/+0x74/+0x78/+0x9C, byte+0x70 and AptValue pointers+0x44/+0x60/+0x64/+0x68; 0x006E6268 stores the action queue at +0xA0. Append 0x006E34D0 reads +0x3C/+0x40/+0xAC. Mark 0x006E47C0 reads the same arrays, values+0x6C/+0x9C and queue+0xA0. StartDrag 0x006EC900 stores pointer+0x44 and floats+0x48..+0x5C, and converts signed words+0x74/+0x78 to float. Command 0x006E4480 stores words+0x7C/+0x80/+0x8C/+0x90 and bytes+0x84/+0x94. Getter 0x006CD724..0x006CD72A reads the +0x30 pointer, its pointer+0 and that object's pointer+0x54; AptMid is the existing neutral pointee view of that chain. Other storage and member names remain neutral.
// Target facts: ledger methods 0x006E34D0 (RET 4), 0x006E3580 (RET 8), 0x006E3530 (RET 12), 0x006E4480 (RET 16) and 0x006E47C0 (RET 0) are nonvirtual thiscall bodies. Caller 0x006CC9F0 copies the sixteen-byte Rva006CC9F0Input record before calling 0x006E4480; the command body uses its two words, byte+8 and word+12. All five methods stay out of line.
#ifndef BFME2_RVA006E34D0_H
#define BFME2_RVA006E34D0_H

class AptCIH;
class AptValue;
class AptActionQueueC;
struct AptMid;
struct AptIntervalTimer;
struct Rva006CC9F0Input;
struct Entry1C;

class Rva006E34D0
{
public:
    void rva006E34D0(int);
    void rva006E3580(int, int);
    void rva006E3530(int, int, int);
    void rva006E4480(Rva006CC9F0Input);
    void rva006E47C0();

    AptCIH **m_field00;
    int m_field04;
    unsigned short m_field08;
    unsigned short m_field0A;
    AptValue **m_field0C;
    int m_field10;
    Entry1C *m_field14;
    unsigned short m_field18;
    unsigned short m_field1A;
    AptValue **m_field1C;
    unsigned short m_field20;
    unsigned short m_field22;
    AptValue **m_field24;
    unsigned short m_field28;
    unsigned short m_field2A;
    AptValue **m_field2C;
    AptMid *m_field30;
    AptIntervalTimer *m_field34;
    int m_field38;
    int m_field3C;
    int *m_field40;
    AptValue *m_field44;
    float m_field48;
    float m_field4C;
    float m_field50;
    float m_field54;
    float m_field58;
    float m_field5C;
    AptValue *m_field60;
    AptValue *m_field64;
    AptValue *m_field68;
    AptValue *m_field6C;
    bool m_field70;
    unsigned char m_pad71[3];
    int m_field74;
    int m_field78;
    int m_field7C;
    int m_field80;
    unsigned char m_field84;
    unsigned char m_pad85[7];
    int m_field8C;
    int m_field90;
    unsigned char m_field94;
    unsigned char m_pad95[7];
    AptValue *m_field9C;
    AptActionQueueC *m_fieldA0;
    int m_fieldA4;
    int m_fieldA8;
    int m_fieldAC;
    int m_fieldB0;
};

#endif
