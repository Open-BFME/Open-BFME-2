// cl: /O1 /G7 /arch:SSE /MD /EHs /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /Ireference/shims/moduledata
// stlport
//
// ??0ScriptEngine@@QAE@XZ, retail 0x00208343..0x002086B7 (884 B): the
// ScriptEngine constructor. Native body plus the owned ScriptEngine destructor
// prove the member offsets, the 20-player arrays, the 599/202 templates and
// the 256 attack slots; ZH ScriptEngine.cpp and BFME1 ScriptEngineRva00347E60
// guide the shape: ZH's initializer list literally, then the body in BFME1's
// order (setGlobalDifficulty(1), the two continuation latches, the frames).
// The frame and latch globals are file statics as in ZH ScriptEngine.cpp
// (st_CurrentFrame / st_LastCurrentFrame / st_CanAppCont): retail schedules
// their stores after the pops, which only non-aliased TU statics allow.
// Built without /Oa, which moves pop edi. The default map/list constructors
// below borrow existing empty-header ABIs; their template payloads are not
// claims about ScriptEngine's map identities and need reconciling with the
// owner headers. Which latch is 0x9FE15C and which 0x9FE15D is not proven.
#include <map>
#include <list>
#include <vector>
#include <new>
#include "ascii_string.h"
typedef bool Bool;
#include "subsystem_interface.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
class SequentialScript;class ObjectTypes;
class Rva003B39C7 {public:Rva003B39C7();~Rva003B39C7();int words[32];};
class Template:public Rva003B39C7 {public:Template(){}~Template(){}};
class ConditionTemplate:public Rva003B39C7 {public:ConditionTemplate(){}~ConditionTemplate(){}};
class Rva0034C5E0 {public:Rva0034C5E0();virtual~Rva0034C5E0();char opaque[12];};
enum NameKeyType { NativeNameKeyUnknown=0 };
class ModuleFactory {public:class ModuleTemplate {int opaque[3];};};
struct BfmePod8 {int words[2];};
typedef _STL::map<NameKeyType,ModuleFactory::ModuleTemplate> MapHeaderA;
typedef _STL::map<int,BfmePod8> MapHeaderB;
typedef _STL::map<int,void*> MapHeaderC;
namespace _STL {template<>MapHeaderA::map();template<>MapHeaderB::map();template<>MapHeaderC::map();}
class Rva002075F3:public MapHeaderA {public:__forceinline Rva002075F3(){}~Rva002075F3();};
class Rva00207630:public MapHeaderB {public:__forceinline Rva00207630(){}~Rva00207630();};
class Rva0020766D:public MapHeaderB {public:__forceinline Rva0020766D(){}~Rva0020766D();};
class Rva002076AA:public MapHeaderB {public:__forceinline Rva002076AA(){}~Rva002076AA();};
class Rva002076E7Map:public MapHeaderC {public:__forceinline Rva002076E7Map(){}~Rva002076E7Map();};
// playerMaps[20] element: retail's eh vector constructor call (0x002084A1)
// passes the shared 25-byte empty-tree constructor 0x0033C432 and the 5-byte
// destructor 0x00205AF8 (rowed ??1Rva00205AF8, a jump to the tree destructor
// ??1Rva00204136 at 0x002055E4), so the element is not map<int,void*>, whose
// destructor is 0x00286921. Key and payload are unresolved: the tree type
// below only spells the ICF-shared tree constructor (0x001F068F), as
// ThingTemplate's map views do.
typedef _STL::pair<const int,void*> PlayerMapValue;
typedef _STL::_Rb_tree<int,PlayerMapValue,_STL::_Select1st<PlayerMapValue>,_STL::less<int>,_STL::allocator<PlayerMapValue> > PlayerMapTree;
struct Rva00205AF8 {PlayerMapTree tree;Rva00205AF8():tree(_STL::less<int>(),PlayerMapTree::allocator_type()){}~Rva00205AF8();};
class Rva00207724:public MapHeaderB {public:__forceinline Rva00207724(){}~Rva00207724();};
class Rva00207761:public MapHeaderB {public:__forceinline Rva00207761(){}~Rva00207761();};
class Rva0020779EMap:public MapHeaderB {public:__forceinline Rva0020779EMap(){}~Rva0020779EMap();};
struct RvaPair00207E26
{
public:
	~RvaPair00207E26();
	AsciiString text; // +0x00
	int scalar; // +0x04
};
#include "../../../Include/Common/BfmeStringRecord00204A30.h"
struct Rva00390729Element {int opaque[3];};
struct SnapshotBlock {char opaque[12];};
struct upgradePair {int opaque[5];};
namespace _STL {
template<>vector<RvaPair00207E26>::~vector();template<>vector<BfmeStringRecord00204A30>::~vector();template<>vector<Rva00390729Element>::~vector();
template<>_List_base<upgradePair,allocator<upgradePair> >::_List_base(const allocator<upgradePair>&);
template<>void _List_base<upgradePair,allocator<upgradePair> >::clear();
}
class ScriptEngine:public SubsystemInterface,public Snapshot {public:ScriptEngine();virtual~ScriptEngine();virtual void init();virtual void reset();virtual void update();virtual void loadPostProcess() = 0;virtual const char*GetSnapshotName()const = 0;virtual void xfer(Xfer*) = 0;
private:
_STL::vector<SequentialScript*> sequential;int unknown1C;Template action[599];ConditionTemplate condition[202];
Rva002075F3 map190A0;Rva00207630 map190AC;Rva0020766D map190B8;Rva002076AA map190C4;Rva002076E7Map map190D0;Rva00207724 map190DC;Rva00207761 map190E8;Rva0020779EMap map190F4;
Rva0034C5E0 attack[256];
int a100,a104,a108;AsciiString string1A10C;int a110,a114,a118,a11C;
_STL::vector<RvaPair00207E26> records;
bool a12C;int a130,a134,a138;bool a13C;float a140,a144,a148;int a14C,a150,a154,a158,a15C,a160;
Rva00205AF8 playerMaps[20];
_STL::list<int> list254;_STL::list<BfmePod8> list258,list25C;_STL::list<int> list260,list264;
_STL::list<SnapshotBlock> lists268[20],lists2B8[20],lists308[20],lists358[20];
_STL::vector<Rva00390729Element> vectors[20];
_STL::list<upgradePair> list498;_STL::vector<BfmeStringRecord00204A30> vector49C;
char breeze[0x1C];int difficulty;
_STL::vector<ObjectTypes*> allObjects;
bool a4D4,a4D5,a4D6,a4D7,a4D8,a4D9,a4DA;
double a4E0,a4E8,a4F0,a4F8;
public: void setGlobalDifficulty(int d){difficulty=d;}
};
static int st_CurrentFrame;
static int scriptLastFrame;
static unsigned char scriptLogicContinuationLatch;
static unsigned char scriptClientContinuationLatch;
ScriptEngine::ScriptEngine():unknown1C(0),a100(0),a104(0),a108(0),a110(0),a114(0),a118(0),a11C(0),a12C(true),a130(0),a134(0),a138(0),a13C(false),a140(0),a144(0),a148(0),a14C(0),a150(0),a154(0),a158(0),a15C(0),a160(0),a4D4(false),a4D5(true),a4D6(false),a4D7(false),a4D8(false),a4D9(true),a4DA(true),a4E0(0),a4E8(0),a4F0(0),a4F8(0){setGlobalDifficulty(1);scriptClientContinuationLatch=true;scriptLogicContinuationLatch=true;scriptLastFrame=st_CurrentFrame=0;}
