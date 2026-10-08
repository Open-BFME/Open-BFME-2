// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /EHsc
// Retail 0x0020DA21..0x0020DA49: LargeGroupAudio's INI load helper.
// The constructor at 0x0020DD59 installs primary table 0x00BE40A0;
// its init slot is 0x0020DA49. Both init and slot 4 (0x0020DB09) pass
// this in ECX to this helper, and slot 4 tests its byte return in AL.
// The old free void __stdcall claim had the wrong receiver and result ABI.
// Helper spelling and the remaining field names are address-derived.

#include "ascii_string.h"
#include "unicode_string.h"

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

class Rva003ED94FDtor
{
public:
    ~Rva003ED94FDtor();
    // Match the existing eight-byte cleanup-owner view, rather than emitting
    // a scalar deleting destructor for an empty class.
    void *m_header;
    int m_flag;
};

class Rva003ED9B1
{
public:
    void rva003ED9B1(const Rva003ED9B1 &other);
};

// The base is a zero-offset call view of the same key-map storage.
class Rva003ED658 : public Rva003ED9B1
{
public:
    Rva003ED658(const Rva003ED658 &other);
    // The native returned aggregate is destroyed through this existing
    // tree-cleanup owner; no second destructor pin is introduced.
    __forceinline ~Rva003ED658()
    {
        ((Rva003ED94FDtor *)this)->~Rva003ED94FDtor();
    }
    char m_storage[12];
};

class ObjectCreationList
{
public:
    ObjectCreationList();
    char m_storage[12];
};

// Initialization-only view used by the exact rva003EDD68 provider. Its
// constructor is folded; the target's cleanup uses the key-map owner.
class Rva003EDD68KeyMap : public ObjectCreationList
{
public:
    __forceinline ~Rva003EDD68KeyMap()
    {
        ((Rva003ED94FDtor *)this)->~Rva003ED94FDtor();
    }
};

class Rva0020DXXXElem
{
public:
    Rva003ED658 rva003EDD68();
};

class LargeGroupAudio
{
public:
    virtual void init();
    unsigned char rva0020DA21(INI *ini);
    // Primary virtual slot 4; original source name and argument role unknown.
    virtual bool rva0020DB09(int reason);
    Rva003ED658 rva0020D86C();
private:
    // Partial view: the constructor establishes a primary vptr at +0,
    // Snapshot at +0xC and three 12-byte containers at +0x10/+0x1C/+0x28.
    char m_pad04[0x0C];
    void **m_begin10;
    void **m_end14;
    char m_pad18[0x20];
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

class InGameUI
{
public:
#define SLOT(N) virtual void vslot##N();
    SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
    SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
#undef SLOT
    // The already-rowed gated UnicodeString formatter occupies slot 16.
    virtual void __cdecl rva0029E846(UnicodeString format, ...);
};
extern InGameUI *TheInGameUI;

// Native 0x0020DB09..0x0020DB91, RET 4. The argument is unused.
// Target sets INI word +8 to 5 and latches +0x39/+0x3A after a successful
// reload; the notification and both latches are target facts.
bool LargeGroupAudio::rva0020DB09(int reason)
{
    INI ini;
    ini.m_word08 = static_cast<INILoadType>(5);
    if (rva0020DA21(&ini))
    {
        m_flag39 = true;
        TheInGameUI->rva0029E846(UnicodeString(L"RIF: LGAS reloaded. Changes take effect immediately."));
        m_flag3A = true;
    }
    return m_flag39;
}

// Native 0x0020D86C..0x0020D8F1: combine the first pointer range's
// returned key maps, then copy the 12-byte aggregate into the hidden result.
// Existing address-derived types preserve the provider's unresolved identity.
Rva003ED658 LargeGroupAudio::rva0020D86C()
{
    Rva003EDD68KeyMap list;
    for (void **it = m_begin10, **end = m_end14; it != end; ++it)
    {
        ((Rva003ED9B1 *)&list)->rva003ED9B1(((Rva0020DXXXElem *)*it)->rva003EDD68());
    }
    return *(const Rva003ED658 *)&list;
}
