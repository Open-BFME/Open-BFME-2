// ??0ScriptEngine@@QAE@XZ
// partial score=0.9865894 date=2026-10-10
// BANK ONLY: native208343..2086B7 and owned ScriptEngine destructor prove
// the target offsets,20-player arrays,599/202 templates and256 attack slots.
// BF1 575ba2b04 ScriptEngineRva00347E60 and ZH ScriptEngine.cpp guide purpose.
// Default map constructors below borrow only existing empty-header ABIs;
// their template payloads are not assertions of ScriptEngine map identities.
// SnapshotBlock/upgradePair array callback spellings and terminal global
// owners remain provisional and need independent owner/header reconciliation.
// In particular9FE15C is already owned by g_00DFE15C;9FE15D is unowned;
// st_CurrentFrame's ledger extent8 conflates scalar160 with unowned164.
// No Code admission/pin/alias/full EH verification was performed for this bank.
// cl: /O1 /G7 /arch:SSE /MD /EHs /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /Ireference/shims/moduledata
// stlport
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
class Rva002075F3Map:public MapHeaderA {public:__forceinline Rva002075F3Map(){}~Rva002075F3Map();};
class Rva00207630Map:public MapHeaderB {public:__forceinline Rva00207630Map(){}~Rva00207630Map();};
class Rva0020766DMap:public MapHeaderB {public:__forceinline Rva0020766DMap(){}~Rva0020766DMap();};
class Rva002076AAMap:public MapHeaderB {public:__forceinline Rva002076AAMap(){}~Rva002076AAMap();};
class Rva002076E7Map:public MapHeaderC {public:__forceinline Rva002076E7Map(){}~Rva002076E7Map();};
class Rva00207724Map:public MapHeaderB {public:__forceinline Rva00207724Map(){}~Rva00207724Map();};
class Rva00207761Map:public MapHeaderB {public:__forceinline Rva00207761Map(){}~Rva00207761Map();};
class Rva0020779EMap:public MapHeaderB {public:__forceinline Rva0020779EMap(){}~Rva0020779EMap();};
struct RvaPair00207E26 {AsciiString text;int scalar;~RvaPair00207E26();};
struct BfmeStringRecord00204A30 {int word0;AsciiString text0;int word1;AsciiString text1;int word2;~BfmeStringRecord00204A30();};
struct Rva00390729Element {int opaque[3];};
struct SnapshotBlock {char opaque[12];};
struct upgradePair {int opaque[5];};
namespace _STL {
template<>vector<RvaPair00207E26>::~vector();template<>vector<BfmeStringRecord00204A30>::~vector();template<>vector<Rva00390729Element>::~vector();
template<>_List_base<SnapshotBlock,allocator<SnapshotBlock> >::_List_base(const allocator<SnapshotBlock>&);
template<>_List_base<upgradePair,allocator<upgradePair> >::_List_base(const allocator<upgradePair>&);
}
class ScriptEngine:public SubsystemInterface,public Snapshot {public:ScriptEngine();virtual~ScriptEngine();virtual void init();virtual void reset();virtual void update();virtual void loadPostProcess();virtual const char*GetSnapshotName()const;virtual void xfer(Xfer*);
private:
_STL::vector<SequentialScript*> sequential;int unknown1C;Template action[599];ConditionTemplate condition[202];
Rva002075F3Map map190A0;Rva00207630Map map190AC;Rva0020766DMap map190B8;Rva002076AAMap map190C4;Rva002076E7Map map190D0;Rva00207724Map map190DC;Rva00207761Map map190E8;Rva0020779EMap map190F4;
Rva0034C5E0 attack[256];
int a100,a104,a108;AsciiString string1A10C;int a110,a114,a118,a11C;
_STL::vector<RvaPair00207E26> records;
bool a12C;int a130,a134,a138;bool a13C;float a140,a144,a148;int a14C,a150,a154,a158,a15C,a160;
MapHeaderC playerMaps[20];
_STL::list<int> list254;_STL::list<BfmePod8> list258,list25C;_STL::list<int> list260,list264;
_STL::list<SnapshotBlock> lists268[20],lists2B8[20],lists308[20],lists358[20];
_STL::vector<Rva00390729Element> vectors[20];
_STL::list<upgradePair> list498;_STL::vector<BfmeStringRecord00204A30> vector49C;
char breeze[0x1C];int difficulty;
_STL::vector<ObjectTypes*> allObjects;
bool a4D4,a4D5,a4D6,a4D7,a4D8,a4D9,a4DA;
double a4E0,a4E8,a4F0,a4F8;
};
extern "C" int st_CurrentFrame;
extern "C" int scriptLastFrame;
extern unsigned char scriptLogicContinuationLatch;
extern unsigned char scriptClientContinuationLatch;
ScriptEngine::ScriptEngine():unknown1C(0),a100(0),a104(0),a108(0),a110(0),a114(0),a118(0),a11C(0),a12C(true),a130(0),a134(0),a138(0),a13C(false),a140(0),a144(0),a148(0),a14C(0),a150(0),a154(0),a158(0),a15C(0),a160(0),a4D4(false),a4D5(true),a4D6(false),a4D7(false),a4D8(false),a4D9(true),a4DA(true),a4E0(0),a4E8(0),a4F0(0),a4F8(0){difficulty=1;st_CurrentFrame=scriptLastFrame=0;scriptLogicContinuationLatch=scriptClientContinuationLatch=true;}
