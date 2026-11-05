// cl: /O1 /Oy /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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
    UnicodeString rva002DFE36();
    char unknown00[0x24];
    AsciiString descriptionLabel;
    char unknown28[4];
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

#include "../../../../Include/GameClient/GameText.h"
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

#include <hash_map>
class GameWindow;
class WindowVideo;
// Declaration view of the existing native provider's empty hash functor.
// No WindowVideoManager object is sized or accessed in this unit.
#include "../../../../Include/GameClient/WindowVideoManagerClass.h"
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

// Native2DFE36..2DFE9E complete104B: translated description + command-point bonus.
UnicodeString LivingWorldBuildingTemplate::rva002DFE36()
{
    UnicodeString description=TheGameText->fetch(descriptionLabel,0);
    appendDisplayCommandPointBonus(description);
    return UnicodeString(description);
}
