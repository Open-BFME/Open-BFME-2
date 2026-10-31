// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva0035BB4B@@QAE@XZ @0x0035B8AA 673B
// Constructor of the large Common record whose virtual dtor 0x0035BB4B lives in
// Rva0035BB4BDtor.cpp (vptr 0x00816204, base Overridable). Member names follow
// the Zero Hour CommandButton field order as a structural inference only; the
// class identity stays address-named.
// Target evidence: WB twin 0xEFE320 (offsets +4) stores the three words after
// the name as plain zeros, then constructs the +0x20 member through a
// one-pointer ctor with 0, then a plain zero at +0x24; modelling +0x20 as
// Zero Hour's OVERRIDE<ThingTemplate> (body-assigning ctor) gives retail's store
// schedule around the first vector-base ctor (bank 0.9945 -> exact).
#include <vector>
// vector<unsigned int>'s allocator constructor inlines at every use here;
// imported force-inline so this unit emits no COMDAT copy of it (its copy
// differs from retail's kept /Od body at 0x00025100). The vector base
// constructor stays a declared nothrow call to its kept copy (0x00211E58).
namespace _STL {
template <> _Vector_base<unsigned int,allocator<unsigned int> >::_Vector_base(const allocator<unsigned int> &) throw();
template <> __declspec(dllimport) __forceinline
vector<unsigned int, allocator<unsigned int> >::vector(const allocator<unsigned int> &__a)
	: _Vector_base<unsigned int, allocator<unsigned int> >(__a) {}
}
#include <bitset>
#include <string.h>
#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> void _Destroy<AsciiString *>(AsciiString *, AsciiString *); }
namespace _STL { template <> void _Destroy<AsciiString>(AsciiString *); }
namespace _STL { template <> vector<AsciiString, allocator<AsciiString> >::~vector(); }
namespace _STL { template <> AsciiString * vector<AsciiString, allocator<AsciiString> >::erase(AsciiString *, AsciiString *); }
// bfme link decl-only end
#include "../../Include/Common/Overridable.h"
class Rva002390CB {public:~Rva002390CB();char bytes[8];};
// Bind to the kept copies (rows: vector<Rva002390CB> dtor 0x0035B825, range
// erase 0x00532803, vector<void *> range erase 0x0031BD55) instead of
// emitting this unit's differing ones.
namespace _STL { template <> vector<Rva002390CB, allocator<Rva002390CB> >::~vector(); }
namespace _STL { template <> void **vector<void *, allocator<void *> >::erase(void **, void **); }
class Rva0024C7B3Member {public:Rva0024C7B3Member() throw();unsigned words[7];};
class Rva0042526Member {public:Rva0042526Member() throw();unsigned words[19];};
class Rva001EAE6FHelper {public:Rva001EAE6FHelper(){clear80();}Rva001EAE6FHelper*clear80();unsigned words[32];};
class BfmeSlotVecG:public _STL::_Vector_base<int,_STL::allocator<int> > {public:
 __forceinline BfmeSlotVecG() throw():_STL::_Vector_base<int,_STL::allocator<int> >(_STL::allocator<int>()){}
 __forceinline void bfmeErase(void**first,void**last){((_STL::vector<void*>*)this)->erase(first,last);}
 void clear(){bfmeErase((void**)_M_start,(void**)_M_finish);}
};
enum ScienceType {SCIENCE_NONE=0};
namespace _STL { template <> ScienceType *vector<ScienceType, allocator<ScienceType> >::erase(ScienceType *, ScienceType *); }
struct RawString {RawString():data(0){}void*data;};
struct PairCapacity {PairCapacity():begin(0),size(32){}void*begin;unsigned size;};

// Zero Hour Override.h spelling: WB twin 0xEFE320 constructs the +0x20 member
// through an out-of-line one-pointer ctor called with 0 (WB 0xF00CF0, body
// m_overridable = arg), which retail inlines.
class ThingTemplate;
template <class T> class OVERRIDE {public: OVERRIDE(const T *overridable = 0); const T *m_overridable;};
template <class T> OVERRIDE<T>::OVERRIDE(const T *overridable){ m_overridable = overridable; }

class Rva0035BB4B:public Overridable {public:
 Rva0035BB4B();virtual ~Rva0035BB4B();
 AsciiString name;int command;void*next;unsigned options;OVERRIDE<ThingTemplate> thing;void*upgrade;
 BfmeSlotVecG buildUpgrades;bool field34;
 _STL::vector<AsciiString>textLabel;int field44;AsciiString cursor;int radiusCursor;AsciiString invalidCursor,field54;
 _STL::vector<AsciiString>description,purchasedDescription;
 AsciiString purchased,conflicting,lacksPrereq;AsciiString unparsed;
 int weaponSlot,toggle1,toggle2,toggle3;
 _STL::bitset<128>flagsToggle;int maxShots;
 _STL::vector<ScienceType>science;int border;
 _STL::vector<AsciiString>imageNames;int flashCount;RawString audioPrefix;
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
 command(0),next(0),options(0),upgrade(0),field34(false),field44(0),radiusCursor(0),
 weaponSlot(0),toggle1(5),toggle2(5),toggle3(5),maxShots(0x7fffffff),border(0),flashCount(-1),
 audioTail2(0),audioTail3(0),doubleClick(false),radial(false),inPalantir(false),production(false),production2(false),clickable(true),show(true),requiresContainer(false),level(0),autoAbility(false),affectsAllies(false),presetRange(0),autoDelay(0),needDamagedTarget(false),field244(0)
{
 memset(&affectsKindOf,0,28);
 science.clear();memset(&flagsToggle,0,16);
 memset(&commandTrigger,0,76);memset(&enableCondition,0,76);memset(&disableCondition,0,76);
 ((StringBase<char>*)&unparsed)->clear();
 buildUpgrades.clear();field188.clear();
}
