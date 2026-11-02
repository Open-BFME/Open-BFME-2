// Target facts (code addresses are RVAs; table addresses are VAs):
// Constructors 0x00409C3D and 0x00409D4D install 0x00C38D88 at 0x00409C5D and 0x00409D67. Destructor 0x00409285 restores it at 0x00409297, destroys the members, then stores Snapshot's 0x00BBB554 at 0x00409342. The latter is the base destruction table, not a second CreateAHeroData table. Snapshot occupies +0..+4.
// Table 0x00C38D88 has five code entries followed by the CreateAHeroData string: slot 0=0x00409D31 (deleting destructor calling 0x00409285), 1=0x000B3FD0 (empty loadPostProcess), 2=0x00409353 (const GetSnapshotName), 3=0x00408C11 (rowed DoXfer on CreateAHeroHero), 4=0x004083FF (rowed bool Update(int) on CreateAHeroHero). The inherited xfer declaration occupies Snapshot's slot 3 with the same one-pointer ABI.
// Factory 0x00219251 pushes 0x140 for operator new before calling 0x00409C3D at 0x0021928A. Constructor stores at 0x00409C63..0x00409CA8 prove dwords +4/+0xC/+0x10/+0x2C/+0x30/+0x34/+0x38; +0x38 starts at 0x2FF. StringBase<unsigned short> copy 0x00037050 is called on +8 at 0x00409C66; StringBase<char> copy 0x000365F0 is called on +0x4C at 0x00409DE5.
// Container receivers in copy constructor 0x00409D4D are +0x14/+0x20 (0x0021CF2C), +0x3C (0x000BC07E), +0x50 (0x0040884B), +0x5C (0x00389413), +0x74 (0x0021E146). Their storage spans are 12/12/12/12/20/12 bytes, delimited by the next member. Opaque storage preserves these spans without selecting conflicting private template spellings.
// Byte stores at 0x00409CB4/0x00409CD9/0x00409CDC prove +0x48/+0x70/+0x71. Constructor 0x00409CFD constructs fifteen 12-byte elements at +0x80 with callbacks 0x005C39DE and 0x0048BA39; destructor 0x004092D5 destroys that same array. Assignment 0x00406E22 proves each element contains an AsciiString and two scalar words; application names are unknown, so its 0xB4-byte storage remains opaque here.
// Constructor 0x00409D07..0x00409D13 clears dwords +0x134/+0x138/+0x13C; copy 0x00409E42..0x00409E64 copies them. Object::getObjectSelectedPortraitImage (0x002946AB) returns the hero's Image pointer at +0x138.
// Out-of-line rows: value constructor 0x00409C3D, copy constructor 0x00409D4D, destructor 0x00409285, assignment 0x00409359, GetSnapshotName 0x00409353, loadPostProcess 0x000B3FD0, GetStat 0x004080DD, GetStatValue 0x00408109, WriteNamedHeroAtRva004074CF 0x004074CF, rva0040732C 0x0040732C, rva00408A55 0x00408A55, rva004099CA 0x004099CA. Lifetime and assignment bodies are declared only.
#ifndef BFME2_CREATEAHERODATA_H
#define BFME2_CREATEAHERODATA_H

#if defined(BFME_SNAPSHOT_NONCONST_NAME_SLOT) || defined(BFME_SNAPSHOT_CAPITALIZED_SLOTS)
#error CreateAHeroData requires the const name getter and lowercase Snapshot slots.
#endif
#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"

class Image;
enum NameKeyType;

class CreateAHeroData : public Snapshot
{
public:
    CreateAHeroData(int, int, int, const UnicodeString &, int, int, int);
    CreateAHeroData(const CreateAHeroData &);
    virtual ~CreateAHeroData();
    CreateAHeroData &operator=(const CreateAHeroData &);

#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *);
    virtual bool Update(int);

    bool GetStat(const AsciiString &, unsigned int *);
    unsigned int GetStatValue(const NameKeyType *);
    bool WriteNamedHeroAtRva004074CF();
    bool rva0040732C();
    bool rva00408A55();
    bool rva004099CA(AsciiString *, bool);

protected:
    virtual void loadPostProcess();

public:
    int field04;
    UnicodeString field08;
    int m_0c;
    int m_10;
    unsigned char field14[12];
    unsigned char field20[12];
    int field2C;
    int field30;
    int field34;
    unsigned int field38;
    unsigned char field3C[12];
    bool m_48;
    AsciiString field4C;
    unsigned char field50[12];
    unsigned char field5C[20];
    bool field70;
    bool field71;
    unsigned char pad72[2];
    unsigned char field74[12];
    unsigned char field80[0xB4];
    unsigned int field134;
    const Image *field138;
    unsigned int field13C;
};

#endif
