// Target facts (code addresses are RVAs, table addresses are VAs):
// Constructors 0x004E30D5 and 0x004E2F9F store 0x00C61F28 at +0; destructor 0x004E3184 stores that table at 0x004E3195, destroys members, then restores Snapshot's 0x00BBB554 at 0x004E323D. Snapshot's own destructor 0x0049B47C stores 0x00BBB554. The final destructor store belongs to the base, not SpawnArmy's live interface.
// Table 0x00C61F28 contains exactly four code pointers: deleting destructor 0x004E3797, loadPostProcess 0x000B3FD0, GetSnapshotName 0x004E30C6 (returns "SpawnArmy" at 0x00C04BC0), and xfer 0x004E3991. The next word at 0x00C61F38 is string data. Snapshot's 0x00BBB554 contains its deleting destructor and three purecall slots. There is one primary vptr and no secondary table or virtual base in either constructor.
// The constructors and copy 0x004E2F9F prove four-byte strings at +04,+08,+0C,+10,+14,+18,+1C,+28,+2C,+30,+34,+50 (StringBase<char> copy 0x000365F0); vector<AsciiString> at +38 is copied by 0x000BC07E and destroyed by 0x0002CC70. The copy reads/writes float words +20,+24,+44, int words +48,+4C and byte flags +54,+55. Four-byte alignment rounds the final byte to sizeof 0x58; parser 0x004E324D constructs that stack object, and node allocator 0x00500BA6 allocates 0x6C bytes for a 0x10-byte tree prefix, one pointer and this 0x58-byte record.
// Retail FieldParse table 0x00C616C0..0x00C617E0 confirms the string offsets, Position at +20 (parseCoord2D 0x0002F558), SpawnForTemplates at +38 (parseAsciiStringVector 0x0002F196), MoveSpeed at +44 (parseReal 0x0002EFC0), BuildTime at +48 (parseInt 0x0002EF56), IsCity at +54 and SpawnAtActStart at +55 (parseBool 0x0002E850). Neutral offset names retain the two separately copied position words.
// The ledger declares constructors 0x004E30D5/0x004E2F9F, destructor 0x004E3184, lookup helpers 0x00319CED/0x004E1755/0x004E23C1/0x004E23E2 and image/text helpers 0x004E240C/0x004E24DC/0x004E25AF/0x004E265F. They remain out of line; wrapper constructor 0x00500770 calls copy constructor 0x004E2F9F. The parser at 0x004E324D passes this class's static field table 0x00C616C0.
#pragma once

#ifndef BFME2_SPAWNARMY_H
#define BFME2_SPAWNARMY_H

#if defined(BFME_SNAPSHOT_CAPITALIZED_SLOTS) || defined(BFME_SNAPSHOT_NONCONST_NAME_SLOT) || defined(BFME_SNAPSHOT_REFERENCE_XFER) || defined(BFME_SNAPSHOT_CONSTRUCTOR_ONLY)
#error SpawnArmy requires the complete native Snapshot profile
#endif
#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"
#include <vector>

struct FieldParse;
class Image;

class SpawnArmy : public Snapshot
{
public:
    SpawnArmy(int index);
    SpawnArmy(const SpawnArmy &other);
    virtual ~SpawnArmy();
    virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *xfer);

    bool rva00319CED();
    int rva004E1755();
    void *rva004E23C1();
    void *rva004E23E2();
    const Image *GetButtonImage(int playerID);
    const Image *GetPortraitImage(int playerID);
    UnicodeString rva004E25AF(int playerID);
    UnicodeString GetButtonHelp(int playerID);
    static const FieldParse m_fieldParseTable[];

    AsciiString m_04;
    AsciiString m_08;
    AsciiString m_0c;
    AsciiString m_10;
    AsciiString m_14;
    AsciiString m_18;
    AsciiString m_1c;
    float m_20;
    float m_24;
    AsciiString m_28;
    AsciiString m_2c;
    AsciiString m_30;
    AsciiString m_34;
    _STL::vector<AsciiString> m_vec38;
    float m_44;
    int m_48;
    int m_4c;
    AsciiString m_50;
    bool m_54;
    bool m_55;
};

#endif
