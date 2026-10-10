// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
// Native2B93B3..2B9641 and21042D..2104B0. WB D7C070 identifies
// LivingWorldLogic; both native vtable name slots independently identify
// LivingWorldLogic and LivingWorldRegionManager. Preserve the existing
// neutral deleting-destructor owners Rva002B964F/Rva00210B38.
// Native EH maps establish seven16B non-polymorphic bases, three4B
// observer bases, and four tail cleanup owners. Observer slot labels and
// static observer storage names are descriptive, not recovered spellings.
// Scalar offsets and container-header boundaries are native facts; opaque
// BfmeE16 vector declarations carry existing header ABI, not element identity.
#include "ascii_string.h"
typedef bool Bool;
#include "subsystem_interface.h"
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#include "Common/Snapshot.h"
#include <map>
#include <list>
#include "unicode_string.h"
struct BfmeE16 {float x,y,z,w;};
class Rva00330757Member {public:Rva00330757Member() throw();~Rva00330757Member() throw();char storage[16];};
class Rva002B2294DwordImmSetter{public:void apply();};class Rva0002B221ADwordImmSetter{public:void apply();};class Rva002B228DDwordImmSetter{public:void apply();};
class LivingWorldBuildingObserver {public:~LivingWorldBuildingObserver(){((Rva002B2294DwordImmSetter*)this)->apply();}virtual void slot0(void*);virtual void slot1(void*);virtual void slot2(void*);virtual void slot3(void*,void*);};
class LivingWorldRegionObserver {public:~LivingWorldRegionObserver(){((Rva0002B221ADwordImmSetter*)this)->apply();}virtual void slot0(void*,int,int);virtual void slot1(void*,int,int);virtual void slot2(void*,void*);virtual void slot3(void*,void*);};
class LivingWorldPlayerObserver {public:~LivingWorldPlayerObserver(){((Rva002B228DDwordImmSetter*)this)->apply();}virtual void slot0(void*);virtual void slot1(void*);virtual void slot2(void*,void*,void*);virtual void slot3(void*);};
struct BfmeStringRecord002B4DC1{UnicodeString text;int a,b;BfmeStringRecord002B4DC1():a(0),b(3){}~BfmeStringRecord002B4DC1(){}};
namespace _STL{template<>list<BfmeStringRecord002B4DC1>::list(unsigned);template<>map<int,void*>::map();template<>_List_base<BfmeStringRecord002B4DC1,allocator<BfmeStringRecord002B4DC1> >::~_List_base();}
class Rva004EDFFFDwordImmSetter{public:void apply();};
class CtorRegionTurnObserver {public:~CtorRegionTurnObserver(){((Rva004EDFFFDwordImmSetter*)this)->apply();}virtual void first(int,int);virtual void second(int,int);};
class Rva002B964F;
class Rva00210B38:public Snapshot,public CtorRegionTurnObserver {
public:Rva00210B38(Rva002B964F*);virtual~Rva00210B38();virtual void loadPostProcess();virtual const char*GetSnapshotName();virtual void xfer(Xfer*);
void*inner;int word0C,word10;_STL::vector<BfmeE16>vec14,vec20;int word2C,word30;_STL::vector<BfmeE16>vec34;
};

class Rva002130CF {public:void rva002130CF(struct Rva002130CFOwner*);};class LivingWorldManager;extern LivingWorldManager*TheLivingWorldManager;
class Rva005A0B4CList {public:void append(struct Rva002BA8F1Listener*);};class Rva002B7250;extern Rva002B7250 g_00E04424,g_00E02E88;
template<int Tag>class CtorObservableView:public Rva00330757Member {};
struct TargetRef00217D4C;struct Rva005F8F96{Rva005F8F96():m_00(0){}~Rva005F8F96();TargetRef00217D4C*m_00;};
class Rva002B9099{public:void clear();void*pointer;};struct CtorOwnedChild:public Rva002B9099{CtorOwnedChild(){pointer=0;}~CtorOwnedChild(){clear();}};
struct Rva002B7000Element{};
namespace _STL{template<>vector<Rva002B7000Element>::~vector();}
class Rva002B964F:public SubsystemInterface,public Snapshot,public CtorObservableView<0>,public CtorObservableView<1>,public CtorObservableView<2>,public CtorObservableView<3>,public CtorObservableView<4>,public CtorObservableView<5>,public CtorObservableView<6>,public LivingWorldBuildingObserver,public LivingWorldRegionObserver,public LivingWorldPlayerObserver {
public:
 Rva002B964F();virtual ~Rva002B964F();
 virtual void init();virtual void reset();virtual void update();
 virtual void loadPostProcess();virtual const char*GetSnapshotName();virtual void xfer(Xfer*);
 virtual void slot1(void*);virtual void slot0(void*,int,int);virtual void slot0(void*);virtual void slot2(void*,void*,void*);

 _STL::vector<BfmeE16> players;
 void*localPlayer;int word9C,wordA0,wordA4,wordA8,wordAC;Rva00210B38*regions;
 bool flagB4,flagB5,flagB6;int wordB8;
 _STL::vector<BfmeE16> vecBC;bool flagC8,flagC9;
 _STL::vector<BfmeE16> vecCC,vecD8;
 int wordE4;bool flagE8,flagE9;int wordEC;
 _STL::list<BfmeStringRecord002B4DC1> records;
 int wordF4,wordF8,wordFC,word100,word104;bool flag108,flag109,flag10A,flag10B;
 _STL::vector<BfmeE16> vec10C,vec118,vec124;
 _STL::map<int,void*>map130,map13C;
 _STL::vector<BfmeE16>vec148;_STL::vector<Rva002B7000Element>vec154;
 Rva005F8F96 word160;int word164;bool flag168,flag169;int word16C,word170;bool flag174,flag175,flag176,flag177;CtorOwnedChild word178;
};
Rva002B964F::Rva002B964F():localPlayer(0),word9C(0),wordA0(0),wordA4(0),wordA8(0),wordAC(-1),flagB4(false),flagB5(true),flagB6(false),wordB8(0),flagC8(false),flagC9(false),wordE4(0),flagE8(false),flagE9(false),wordEC(1),records(0),word100(0),word104(0),flag108(false),flag109(false),flag10A(false),flag10B(true),word164(0),flag168(false),flag169(false),word16C(0),word170(0),flag174(false),flag175(false),flag176(false),flag177(false)
{
 regions=new Rva00210B38(this);
 wordF8=-1;wordF4=0;wordFC=0;
 ((Rva002130CF*)TheLivingWorldManager)->rva002130CF((Rva002130CFOwner*)this);
 ((Rva005A0B4CList*)&g_00E04424)->append((Rva002BA8F1Listener*)(LivingWorldBuildingObserver*)this);
 ((Rva005A0B4CList*)&g_00E02E88)->append((Rva002BA8F1Listener*)(LivingWorldRegionObserver*)this);
}

Rva00210B38::Rva00210B38(Rva002B964F*logic):inner(0),word0C(0),word10(0),word2C(0),word30(0){
 ((Rva005A0B4CList*)((char*)logic+0x1C))->append((Rva002BA8F1Listener*)(CtorRegionTurnObserver*)this);
}
