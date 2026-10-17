// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
// stlport
// ??1Rva00386374@@UAE@XZ 0x00386374 344B
// Evidence: leaf dtor with pin; vtable 0x00C19500 then 0x00C19230; TheGameInfo vs TheGameSpyGame clear then GameSpyInfo::reset 0x385D25 then 20 member dtors descending from +0x162C to +0xC; caller deleting dtor 0x38745D; donor PeerDefs GameSpyInfo reset plus Rva0046A93E member shapes.
#include "ascii_string.h"
#include <map>

// Declaration-only: the rowed set<AsciiString> tree members are bound,
// this TU emits no per-flag copy of them or of their allocator leaves.
namespace _STL {
typedef _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> > Lk6AsciiSetTree;
template <> Lk6AsciiSetTree::~_Rb_tree();
}

class GameInfo;
extern GameInfo *TheGameInfo;
class GameSpyStagingRoom;
extern GameSpyStagingRoom *TheGameSpyGame;

struct GameSpyInfo
{
	virtual void reset();
};

class PlayerInfo
{
public:
	~PlayerInfo();
private:
	char m_data[0x30];
};
struct AsciiComparator
{
	bool operator()(AsciiString s1, AsciiString s2) const;
};
typedef _STL::pair<const AsciiString, PlayerInfo> PlayerInfoMapValue;
typedef _STL::_Rb_tree<AsciiString, PlayerInfoMapValue, _STL::_Select1st<PlayerInfoMapValue>, AsciiComparator, _STL::allocator<PlayerInfoMapValue> > PlayerInfoMapTree;
typedef _STL::map<AsciiString, PlayerInfo, AsciiComparator> PlayerInfoMap;
typedef _STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>, _STL::less<AsciiString>, _STL::allocator<AsciiString> > FactionSetTree;

struct Rva00072FE6
{
	~Rva00072FE6();
};
struct Rva003820D1
{
	~Rva003820D1();
};
struct Rva00383A28
{
	~Rva00383A28();
};
struct Rva00383AFF
{
	~Rva00383AFF();
};
struct Rva0038404A
{
	~Rva0038404A();
};
struct Rva003820A4
{
	~Rva003820A4();
};
struct BfmeSubEBD
{
	~BfmeSubEBD();
};

// Lifetime-only view of the group-room map at owner+0x18. Native constructor
// 0x00385FE1 and destructor 0x00386374 bind their state-4 unwind actions to
// 0x003853BC, which destroys the inner tree through 0x00384DEB on the same
// receiver. The tree's storage remains opaque; the existing owner padding
// preserves the following member at +0x24. This is not an original type name.
struct BfmeGroupRoomMapEBD
{
	~BfmeGroupRoomMapEBD() {}
	BfmeSubEBD m_tree;
};

struct Gen_uw_00385371
{
	~Gen_uw_00385371();
};
class GameSpyStagingRoom
{
public:
	virtual ~GameSpyStagingRoom();
};

extern "C" const void *const __identifier("??_7Rva00381D78@@6B@")[];

struct Rva00386374Base
{
	virtual ~Rva00386374Base() { *(const void **)this = __identifier("??_7Rva00381D78@@6B@"); }
};

class Rva00386374 : public Rva00386374Base
{
public:
	virtual ~Rva00386374();
private:
	char m_pad04[8];
	AsciiString m_0C;
	AsciiString m_10;
	AsciiString m_14;
	BfmeGroupRoomMapEBD m_18;
	char m_pad19[0x24 - 0x19];
	Rva003820A4 m_24;
	char m_pad25[0x34 - 0x25];
	Rva0038404A m_34;
	char m_pad35[0x40 - 0x35];
	Rva0038404A m_40;
	char m_pad41[0x4C - 0x41];
	PlayerInfoMap m_4C;
	Rva00383AFF m_58;
	char m_pad59[0x60 - 0x59];
	AsciiString m_60;
	char m_pad64[0x70 - 0x64];
	AsciiString m_70;
	char m_pad74[0x78 - 0x74];
	AsciiString m_78;
	AsciiString m_7C;
	AsciiString m_80;
	Gen_uw_00385371 m_84;
	char m_pad85[0x5E4 - 0x85];
	GameSpyStagingRoom m_5E4;
	char m_pad5E8[0x1608 - 0x5E8];
	FactionSetTree m_1608;
	Rva00383A28 m_1614;
	char m_pad1615[0x1620 - 0x1615];
	Rva003820D1 m_1620;
	char m_pad1621[0x162C - 0x1621];
	Rva00072FE6 m_162C;
};

// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<AsciiString,pair<AsciiString const ,PlayerInfo>,_Select1st<pair<AsciiString const ,PlayerInfo> >,AsciiComparator,allocator<pair<AsciiString const ,PlayerInfo> > >::~_Rb_tree(); }
namespace _STL { template <> pair<AsciiString const ,PlayerInfo>::~pair(); }
// bfme link decl-only end
Rva00386374::~Rva00386374()
{
	if (TheGameInfo == (GameInfo *)TheGameSpyGame)
		TheGameInfo = 0;
	TheGameSpyGame = 0;
	((GameSpyInfo *)this)->GameSpyInfo::reset();
}
