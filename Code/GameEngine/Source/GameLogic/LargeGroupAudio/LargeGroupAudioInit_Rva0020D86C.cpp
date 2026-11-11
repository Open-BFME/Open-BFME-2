// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Split from LargeGroupAudioInit.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
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

#include "../../../Include/Common/INI/INI.h"

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

#include "../../../Include/GameLogic/Rva003ED658.h"

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
        ((Rva003ED94FDtor *)this)->Rva003ED94FDtor::~Rva003ED94FDtor();
    }
};

#include "../../../Include/GameLogic/Rva0020DXXXElem.h"

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


#include "../../../Include/Common/SubsystemInterfaceList.h"

extern SubsystemInterfaceList *TheSubsystemList;


#include "../../../Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;


// Native 0x0020D86C..0x0020D8F1: combine the first pointer range's
// returned key maps, then copy the 12-byte aggregate into the hidden result.
// Existing address-derived types preserve the provider's unresolved identity.
Rva003ED658 LargeGroupAudio::rva0020D86C()
{
    Rva003EDD68KeyMap list;
    for (void **it = m_begin10, **end = m_end14; it != end; ++it)
    {
        ((Rva003ED9B1 *)&list)->rva003ED9B1(
            (const Rva003ED9B1 &)((Rva0020DXXXElem *)*it)->rva003EDD68());
    }
    return *(const Rva003ED658 *)&list;
}
