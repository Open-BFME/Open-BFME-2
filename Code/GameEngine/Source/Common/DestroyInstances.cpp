// cl: /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7
// stlport46
// stlport
// STLport single-object _Destroy instances: nine-byte free functions
//
//     mov ecx,[esp+4] / jmp ~T
//
// _STL::_Destroy(T *) runs T's non-virtual destructor on its argument; the
// destructor call becomes a tail jump. Each instance tail-jumps to a matched
// ledger destructor, so the element type is that destructor's owner (structural inference from the shape and the jump target;
// the class key follows the owner's every existing declaration, or the
// declaration in the unit that compiles its destructor where views differ). The
// emitting units are not recovered, so the instances are instantiated here.
#include <vector>

class Rva000C2980
{
public:
	~Rva000C2980();
};
class Rva00216108
{
public:
	~Rva00216108();
};
class Rva0022304A
{
public:
	~Rva0022304A();
};
class Rva0022CFE6
{
public:
	~Rva0022CFE6();
};
class Rva00329D0E
{
public:
	~Rva00329D0E();
};
struct Rva00382B3F
{
public:
	~Rva00382B3F();
};
class Rva004104C9
{
public:
	~Rva004104C9();
};
class Rva00410688
{
public:
	~Rva00410688();
};
class Rva00466E23
{
public:
	~Rva00466E23();
};
class Rva004D960C
{
public:
	~Rva004D960C();
};
class Rva004E5086
{
public:
	~Rva004E5086();
};
class Rva004FF2F4
{
public:
	~Rva004FF2F4();
};
struct Rva004FABE2
{
public:
	~Rva004FABE2();
};
class Rva005011B4
{
public:
	~Rva005011B4();
};
struct Rva005F8447
{
public:
	~Rva005F8447();
};
struct Rva00600BBE
{
public:
	~Rva00600BBE();
};
class Rva00603C57
{
public:
	~Rva00603C57();
};

class LocomotorStore
{
public:
	~LocomotorStore();
};
class Rva00229487
{
public:
	~Rva00229487();
};
struct VersionBlockEntry
{
public:
	~VersionBlockEntry();
};
class Rva002B923F
{
public:
	~Rva002B923F();
};
class Rva00360F55
{
public:
	~Rva00360F55();
};
class BfmeNodeValueEBD
{
public:
	~BfmeNodeValueEBD();
};
class BuddyMessage
{
public:
	~BuddyMessage();
};
class Rva0041579E
{
public:
	~Rva0041579E();
};
struct Rva0073EEE0ListValue
{
public:
	~Rva0073EEE0ListValue();
};
struct Rva000543F5Record
{
public:
	~Rva000543F5Record();
};
struct Rva00111B25Record
{
public:
	~Rva00111B25Record();
};
struct BfmeStringRecord000B94D2
{
public:
	~BfmeStringRecord000B94D2();
};
struct BfmeStringTailRecord180
{
public:
	~BfmeStringTailRecord180();
};
class BfmePod248
{
public:
	~BfmePod248();
};
struct BfmeVectorRecord001B4A39
{
public:
	~BfmeVectorRecord001B4A39();
};
struct Rva0010F149Handle
{
public:
	~Rva0010F149Handle();
};
#include "ascii_string.h"
#include <utility>
typedef _STL::pair<AsciiString,AsciiString> ScriptStringKey;
typedef _STL::pair<const ScriptStringKey,AsciiString> ScriptStringValue;
template <> ScriptStringValue::~pair();
typedef ScriptStringValue Rva00204686;
class RvaSmartPtr12
{
public:
	~RvaSmartPtr12();
};
struct Rva0029E00D
{
public:
	~Rva0029E00D();
};
class Rva001EB63C
{
public:
	~Rva001EB63C();
};
class Rva00358B65
{
public:
	~Rva00358B65();
};
struct PeerResponse
{
public:
	~PeerResponse();
};
class Rva001EB940
{
public:
	~Rva001EB940();
};
struct Rva004F7DD4
{
public:
	~Rva004F7DD4();
};
class Rva005C8FBD
{
public:
	~Rva005C8FBD();
};
class BfmeVectorRecord002AF478
{
public:
	~BfmeVectorRecord002AF478();
};
struct Rva004F69C3
{
	~Rva004F69C3();
};
struct Rva0040AFF3
{
	~Rva0040AFF3();
};
struct LightSubPoint
{
	~LightSubPoint();
};
struct TreeHintOpaque0043671B
{
	~TreeHintOpaque0043671B();
};
struct Rva004F6986
{
	~Rva004F6986();
};
struct Rva004F691E
{
	~Rva004F691E();
};
struct Rva004FFE39
{
	~Rva004FFE39();
};
struct Rva004FFE89
{
	~Rva004FFE89();
};
class Rva0050174A
{
public:
	~Rva0050174A();
};
struct Rva005017AC
{
	~Rva005017AC();
};
class Rva00495C43PoolRecord
{
public:
	~Rva00495C43PoolRecord();
};
class ProductionPrerequisite
{
public:
	struct PrereqUnitRec
	{
		~PrereqUnitRec();
	};
};
template void _STL::_Destroy<Rva000C2980>(Rva000C2980 *);
template void _STL::_Destroy<Rva00216108>(Rva00216108 *);
template void _STL::_Destroy<Rva0022304A>(Rva0022304A *);
template void _STL::_Destroy<Rva0022CFE6>(Rva0022CFE6 *);
template void _STL::_Destroy<Rva00329D0E>(Rva00329D0E *);
template void _STL::_Destroy<Rva00382B3F>(Rva00382B3F *);
template void _STL::_Destroy<Rva004104C9>(Rva004104C9 *);
template void _STL::_Destroy<Rva00410688>(Rva00410688 *);
template void _STL::_Destroy<Rva00466E23>(Rva00466E23 *);
template void _STL::_Destroy<Rva004D960C>(Rva004D960C *);
template void _STL::_Destroy<Rva004E5086>(Rva004E5086 *);
template void _STL::_Destroy<Rva004FF2F4>(Rva004FF2F4 *);
template void _STL::_Destroy<Rva004FABE2>(Rva004FABE2 *);
template void _STL::_Destroy<Rva005011B4>(Rva005011B4 *);
template void _STL::_Destroy<Rva005F8447>(Rva005F8447 *);
template void _STL::_Destroy<Rva00600BBE>(Rva00600BBE *);
template void _STL::_Destroy<Rva00603C57>(Rva00603C57 *);
template void _STL::_Destroy<LocomotorStore>(LocomotorStore *);
template void _STL::_Destroy<Rva00229487>(Rva00229487 *);
template void _STL::_Destroy<VersionBlockEntry>(VersionBlockEntry *);
template void _STL::_Destroy<Rva002B923F>(Rva002B923F *);
template void _STL::_Destroy<Rva00360F55>(Rva00360F55 *);
template void _STL::_Destroy<BfmeNodeValueEBD>(BfmeNodeValueEBD *);
template void _STL::_Destroy<BuddyMessage>(BuddyMessage *);
template void _STL::_Destroy<Rva0041579E>(Rva0041579E *);
template void _STL::_Destroy<Rva0073EEE0ListValue>(Rva0073EEE0ListValue *);
template void _STL::_Destroy<Rva000543F5Record>(Rva000543F5Record *);
template void _STL::_Destroy<Rva00111B25Record>(Rva00111B25Record *);
template void _STL::_Destroy<BfmeStringRecord000B94D2>(BfmeStringRecord000B94D2 *);
template void _STL::_Destroy<BfmeStringTailRecord180>(BfmeStringTailRecord180 *);
template void _STL::_Destroy<BfmePod248>(BfmePod248 *);
template void _STL::_Destroy<BfmeVectorRecord001B4A39>(BfmeVectorRecord001B4A39 *);
template void _STL::_Destroy<Rva0010F149Handle>(Rva0010F149Handle *);
template void _STL::_Destroy<Rva00204686>(Rva00204686 *);
template void _STL::_Destroy<RvaSmartPtr12>(RvaSmartPtr12 *);
template void _STL::_Destroy<Rva0029E00D>(Rva0029E00D *);
template void _STL::_Destroy<Rva001EB63C>(Rva001EB63C *);
template void _STL::_Destroy<Rva00358B65>(Rva00358B65 *);
template void _STL::_Destroy<PeerResponse>(PeerResponse *);
template void _STL::_Destroy<Rva001EB940>(Rva001EB940 *);
template void _STL::_Destroy<Rva004F7DD4>(Rva004F7DD4 *);
template void _STL::_Destroy<Rva005C8FBD>(Rva005C8FBD *);
template void _STL::_Destroy<BfmeVectorRecord002AF478>(BfmeVectorRecord002AF478 *);

// 0x00288FE5 -> ??1?$pair@$$CBHV?$list@UBfmePod264@@...@@ 0x00288B89 and
// 0x002A1D94 -> ??1?$pair@VAsciiString@@VAudioEventRTS@@ 0x002A12E1 (ICF-shared
// with another AsciiString-keyed pair). Each pair destructor is the rowed
// body, declared here so the instance tail-jumps to it.
#include <list>
struct BfmePod264 { BfmePod264(const BfmePod264 &); virtual ~BfmePod264(); int a[65]; };
typedef _STL::pair<const int, _STL::list<BfmePod264> > Rva00288B89Pair;
template <> Rva00288B89Pair::~pair();
// The pair's +4 teardown is retail's call to 0x004EC395, the ICF-folded
// _List_base<int> destructor row; no AudioEventRTS destructor is rowed.
class AudioEventRTS
{
public:
	_STL::_List_base<int, _STL::allocator<int> > m_list;
};
typedef _STL::pair<AsciiString, AudioEventRTS> Rva002A12E1Pair;
template <> Rva002A12E1Pair::~pair();
template void _STL::_Destroy<Rva00288B89Pair>(Rva00288B89Pair *);
template void _STL::_Destroy<Rva002A12E1Pair>(Rva002A12E1Pair *);

template void _STL::_Destroy<Rva004F69C3>(Rva004F69C3 *);				// 0x0040D47E
template void _STL::_Destroy<Rva00495C43PoolRecord>(Rva00495C43PoolRecord *);	// 0x00495DF8
template void _STL::_Destroy<ProductionPrerequisite::PrereqUnitRec>(ProductionPrerequisite::PrereqUnitRec *);	// 0x0045710A
template void _STL::_Destroy<Rva004F6986>(Rva004F6986 *);				// 0x004F73E1
template void _STL::_Destroy<Rva004F691E>(Rva004F691E *);				// 0x004F73EA
template void _STL::_Destroy<Rva004FFE39>(Rva004FFE39 *);				// 0x0050051D
template void _STL::_Destroy<Rva004FFE89>(Rva004FFE89 *);				// 0x00500526
template void _STL::_Destroy<Rva0050174A>(Rva0050174A *);				// 0x00502070
template void _STL::_Destroy<Rva005017AC>(Rva005017AC *);				// 0x00502079
template void _STL::_Destroy<Rva0040AFF3>(Rva0040AFF3 *);				// 0x0040B3D5
template void _STL::_Destroy<LightSubPoint>(LightSubPoint *);				// 0x00424DCC
template void _STL::_Destroy<TreeHintOpaque0043671B>(TreeHintOpaque0043671B *);	// 0x00434A26
