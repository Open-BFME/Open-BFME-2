// cl: /O1 /Oy- /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Target evidence: WB DA2310 names appendDisplayCommandPointBonus in
// LivingWorldBuildingTemplate.cpp; retail 2DFD9F..2DFE36 is 151 bytes.
// Kind +2C == 3 selects IncreaseCommandPoints. Its nugget contributes +0C
// to CONTROLBAR:LW_FarmCPBonus; GameText slot 15 returns the wide string.
// The complete 76-byte helper at 2DFBA0..2DFBEC searches pointers +30/+34,
// compares each slot-2 returned name and releases the temporary. findNugget
// is a descriptive selector; the original helper and nugget class names
// remain unknown. The const interface is a local read-only view.
// The canonical string compare's nonthrowing contract and slot-2 getter
// reproduce the helper's lack of EH; the formatter retains both EH states.
// No corresponding clean BF1 ba7ddda or ZH building-template donor found.
// Identity and accessed offsets come from target debug and native evidence.
// stlport
#include <algorithm>
#include "ascii_string.h"
#include "unicode_string.h"
class BuildingNuggetView
{
public:
    virtual void slot0();
    virtual void slot1();
    virtual AsciiString getName() const throw();
    char unknown04[8];
    int commandPoints;
};
class LivingWorldBuildingTemplate
{
public:
    BuildingNuggetView *findNugget(const AsciiString &) const;
    void appendDisplayCommandPointBonus(UnicodeString &) const;
    char unknown00[0x2C];
    int kind;
    BuildingNuggetView **begin, **end;
};
BuildingNuggetView *LivingWorldBuildingTemplate::findNugget(const AsciiString &name) const
{
    BuildingNuggetView **i = begin, **last = end;
    while (i != last)
    {
        bool matches = ((*i)->getName() == name);
        if (matches)
            return *i;
        ++i;
    }
    return 0;
}

class GameTextInterface
{
public:
#define GT_SLOT(n) virtual void slot##n();
GT_SLOT(0) GT_SLOT(1) GT_SLOT(2) GT_SLOT(3) GT_SLOT(4) GT_SLOT(5) GT_SLOT(6) GT_SLOT(7) GT_SLOT(8) GT_SLOT(9) GT_SLOT(10) GT_SLOT(11) GT_SLOT(12) GT_SLOT(13) GT_SLOT(14)
#undef GT_SLOT
    virtual UnicodeString fetch(const char *, bool *);
};
extern GameTextInterface *TheGameText;
void LivingWorldBuildingTemplate::appendDisplayCommandPointBonus(UnicodeString &description) const
{
    if (kind != 3)
        return;
    BuildingNuggetView *nugget = findNugget(AsciiString("IncreaseCommandPoints"));
    if (nugget)
    {
        UnicodeString text = TheGameText->fetch("CONTROLBAR:LW_FarmCPBonus", 0);
        text.format(&text, nugget->commandPoints);
        description += text;
    }
}

// Native 0x002DFA43..0x002DFA7A RET4, called by OwnershipSet's building loop
// and the existing template-store export helpers. The original predicate name
// is unknown; retain the existing admitted Rva0059E647Entry::Check spelling.
// Empty key ranges at +3C/+40 accept every key; otherwise search four-byte keys.
struct Rva0059E647Entry
{
    unsigned char unknown00[0x3c];
    int *begin;
    int *end;
    bool Check(int key);
};
bool Rva0059E647Entry::Check(int key)
{
    // Retail observes the range again after the empty-range branch.
    if (*(int *volatile *)&begin == *(int *volatile *)&end)
        return true;
    int value = key;
    // Preserve retail's independent load and store of the outgoing search key.
    *(volatile int *)&key = value;
    int *last = end;
    return _STL::find(begin, last, key) != last;
}


#include <hash_map>
class GameWindow;
class WindowVideo;
// Declaration view of the existing native provider's empty hash functor.
// No WindowVideoManager object is sized or accessed in this unit.
class WindowVideoManager {
public: struct hashConstGameWindowPtr {
 unsigned int operator()(const GameWindow *) const;
};
};
typedef _STL::pair<const GameWindow *const,WindowVideo *> NativeBeginPair;
typedef _STL::hashtable<NativeBeginPair,const GameWindow *,
 WindowVideoManager::hashConstGameWindowPtr,_STL::_Select1st<NativeBeginPair>,
 _STL::equal_to<const GameWindow *>,_STL::allocator<NativeBeginPair> > NativeBeginTable;
namespace _STL { template<> NativeBeginTable::iterator NativeBeginTable::begin(); }
class LivingWorldBuildingTemplateStore {
public: const LivingWorldBuildingTemplate *getEmergencyBackupTemplateForBadLoads();
private: char unknown00[0x10]; char tablePrefix[0x14];
};
// The 68-byte native begin provider reads only the shared bucket/node prefix,
// never its key or mapped payload. This call does not identify the store's
// original specialization. Native node+8 is the embedded fallback template.
const LivingWorldBuildingTemplate *LivingWorldBuildingTemplateStore::getEmergencyBackupTemplateForBadLoads() {
 NativeBeginTable::iterator first=reinterpret_cast<NativeBeginTable*>(tablePrefix)->begin();
 return reinterpret_cast<const LivingWorldBuildingTemplate*>((char*)first._M_cur+8);
}
