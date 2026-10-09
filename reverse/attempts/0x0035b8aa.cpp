// ??0Rva0035BB4B@@QAE@XZ
// partial score=0.98 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include <bitset>
#include <string.h>
#include "ascii_string.h"
class Rva001E3624 {public:Rva001E3624():next(0),flag(false),extra(-1){}virtual ~Rva001E3624();void*next;bool flag;int extra;};
class Rva002390CB {public:~Rva002390CB();char bytes[8];};
class Rva0024C7B3Member {public:Rva0024C7B3Member() throw();unsigned words[7];};
class Rva0042526Member {public:Rva0042526Member() throw();unsigned words[19];};
class Rva001EAE6FHelper {public:Rva001EAE6FHelper(){clear80();}Rva001EAE6FHelper*clear80();unsigned words[32];};
class BfmeSlotVecG:public _STL::_Vector_base<int,_STL::allocator<int> > {public:
 __forceinline BfmeSlotVecG() throw():_STL::_Vector_base<int,_STL::allocator<int> >(_STL::allocator<int>()){}
 void bfmeErase(void**,void**);
 void clear(){bfmeErase((void**)_M_start,(void**)_M_finish);}
};
enum ScienceType {SCIENCE_NONE=0};
struct RawString {RawString():data(0){}void*data;};
struct PairCapacity {PairCapacity():begin(0),size(32){}void*begin;unsigned size;};
struct ButtonActionDefaults {int command;void*next;unsigned options;__forceinline ButtonActionDefaults():command(0),next(0),options(0){}};
class Rva0035BB4B:public Rva001E3624 {public:
 Rva0035BB4B();virtual ~Rva0035BB4B();
 AsciiString name;ButtonActionDefaults action;void*thing,*upgrade;
 BfmeSlotVecG buildUpgrades;bool field34;
 _STL::vector<AsciiString>textLabel;int field44;AsciiString cursor;int radiusCursor;AsciiString invalidCursor,field54;
 _STL::vector<AsciiString>description,purchasedDescription;
 AsciiString purchased,conflicting,lacksPrereq;AsciiString unparsed;
 int weaponSlot,toggle1,toggle2,toggle3;
 _STL::bitset<128>flagsToggle;int maxShots;
 _STL::vector<ScienceType>science;int border;
 _STL::vector<AsciiString>imageNames;int flashCount;AsciiString audioPrefix;
 _STL::vector<Rva002390CB>audio0,audio1,audio2;
 _STL::vector<unsigned>buttonImages;int audioTail2,audioTail3;
 bool doubleClick,radial,inPalantir,production,production2,clickable,show,requiresContainer;
 int level;bool autoAbility;
 Rva0024C7B3Member affectsKindOf;bool affectsAllies;float presetRange,autoDelay;bool needDamagedTarget;
 Rva0042526Member commandTrigger;
 _STL::vector<AsciiString>field188;
 Rva0042526Member enableCondition,disableCondition;
 PairCapacity field22C;
 _STL::vector<unsigned>field234;
 AsciiString field240;int field244;AsciiString field248;
 Rva001EAE6FHelper field24C;
};
Rva0035BB4B::Rva0035BB4B():
 thing(0),upgrade(0),field34(false),field44(0),radiusCursor(0),
 weaponSlot(0),toggle1(5),toggle2(5),toggle3(5),maxShots(0x7fffffff),border(0),flashCount(-1),
 audioTail2(0),audioTail3(0),doubleClick(false),radial(false),inPalantir(false),production(false),production2(false),clickable(true),show(true),requiresContainer(false),level(0),autoAbility(false),affectsAllies(false),presetRange(0),autoDelay(0),needDamagedTarget(false),field244(0)
{
 memset(&affectsKindOf,0,28);
 science.clear();memset(&flagsToggle,0,16);
 memset(&commandTrigger,0,76);memset(&enableCondition,0,76);memset(&disableCondition,0,76);
 ((StringBase<char>*)&unparsed)->clear();
 buildUpgrades.clear();field188.clear();
}
