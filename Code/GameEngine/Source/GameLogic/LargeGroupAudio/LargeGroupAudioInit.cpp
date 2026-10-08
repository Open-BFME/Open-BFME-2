// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /EHsc
// Retail 0x0020DA21..0x0020DA49: LargeGroupAudio's INI load helper.
// The constructor at 0x0020DD59 installs primary table 0x00BE40A0;
// its init slot is 0x0020DA49. Both init and slot 4 (0x0020DB09) pass
// this in ECX to this helper, and slot 4 tests its byte return in AL.
// The old free void __stdcall claim had the wrong receiver and result ABI.
// Helper spelling and the remaining field names are address-derived.

#include "ascii_string.h"

class Xfer;
enum INILoadType
{
    INI_LOAD_INVALID = 0,
    INI_LOAD_OVERWRITE = 1,
    INI_LOAD_CREATE_OVERRIDES = 2
};

class INI
{
public:
    INI();
    ~INI();
    unsigned char loadFile(AsciiString filename, INILoadType loadType, Xfer *xfer);
    char m_pad00[8];
    INILoadType m_word08;
    // The rowed constructor and callers establish the 0x87C-byte extent.
    char m_pad0C[0x870];
};

class LargeGroupAudio
{
public:
    virtual void init();
    unsigned char rva0020DA21(INI *ini);
private:
    // Partial view: the constructor establishes a primary vptr at +0,
    // Snapshot at +0xC and three 12-byte containers at +0x10/+0x1C/+0x28.
    char m_pad04[0x34];
    bool m_flag38;
    bool m_flag39;
    bool m_flag3A;
    char m_pad3B;
    int m_word3C;
};

unsigned char LargeGroupAudio::rva0020DA21(INI *ini)
{
    return ini->loadFile("Data\\INI\\LargeGroupAudio.ini", ini->m_word08, 0);
}

class SubsystemInterfaceList
{
public:
    // Target 0x001B5018 takes one pointer in a stack argument, this in ECX,
    // and returns with RET 4. Its source name remains unresolved.
    void rva001B5018(void *subsystem);
};

extern SubsystemInterfaceList *TheSubsystemList;

// Retail init slot: 0x0020DA49..0x0020DAA5, 92 bytes. Local INI lifetime,
// helper call, flag +0x38 and subsystem-list receiver are target evidence.
void LargeGroupAudio::init()
{
    INI ini;
    rva0020DA21(&ini);
    m_flag38 = true;
    TheSubsystemList->rva001B5018(this);
}
