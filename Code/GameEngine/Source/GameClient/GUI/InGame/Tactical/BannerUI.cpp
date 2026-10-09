// cl: /G7 /arch:SSE /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// BannerUI::ParseBannerTypeInfo, retail 0x00217194 (94B), from the WorldBuilder
// lead (BannerUI.cpp): an INI block parser that takes the banner type name
// token, finds or creates its info in the banner UI singleton's type table
// (g_00DFE32C +0x0C, 0x00216F91) and parses the block into it with the
// banner-type field table at 0x00BE5A50 (INI::initFromINI).
//
// Target facts: the type table, its lookup and the info record keep
// address-derived names; the field table is referenced by address.

#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../../Common/GameLogicObjectLookupView.h"

struct FieldParse;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	void initFromINI(void *what, const FieldParse *parseTable);
};

class Rva00217194Types
{
public:
	void *rva00216F91(const AsciiString &name);
};

class Rva00217194BannerUI
{
public:
	Rva00217194Types *getTypes() { return &m_types; }

private:
	unsigned char m_pad00[0x0C];
	Rva00217194Types m_types;
};
extern Rva00217194BannerUI *g_00DFE32C;

extern const FieldParse g_00BE5A50[];


struct Rva0041534BIter {void *m_node;void *m_table;};
struct BannerTypeIterator
{
	BannerTypeIterator(void *node, void *table) : m_node(node), m_table(table) {}
	void *m_node;
	void *m_table;
};
class Rva00056F61 {
public:
 BannerTypeIterator find(const AsciiString &name) {return BannerTypeIterator(rva00056F61(&name),this);}
 __declspec(nothrow) Rva0041534BIter rva0041534B(const AsciiString *);
 __declspec(nothrow) void *rva00056F61(const AsciiString *);
 void *unused;void **begin,**end,**capacity;unsigned count;
};

// One banner on screen, the vector's 28-byte record (rowed push_back
// 0x00216BB9 and the slot-keyed find/erase in RemoveBanner): its slot, the
// army banner id it shows, and the banner type entry it was created from.
// CreateBanner builds it with +0x14 at -1 and the rest cleared (see
// clearBannerRecord). BfmePod28 is the shared neutral spelling of 28-byte
// records, and its default constructor is retail's 0x00583AE2
// (HordeMeleeSwarmXfer.cpp), so this view declares none: at /O1 an inline
// one here is emitted as a conflicting ??0BfmePod28@@QAE@XZ COMDAT.
struct BfmePod28
{
	unsigned int slot;			// +0x00
	int bannerID;				// +0x04
	const void *typeEntry;		// +0x08, the type table's key/info pair
	int unknown0C;
	int unknown10;
	int unknown14;
	bool unknown18;
};

namespace _STL {
template <class T> class allocator { public: allocator() {} };
template <class T, class A> class vector {
public:
	typedef T *iterator;
	iterator begin() { return _M_start; }
	iterator end() { return _M_finish; }
	void push_back(const T &value);	// 0x00216BB9
private:
	iterator _M_start;
	iterator _M_finish;
	iterator _M_end_of_storage;
};
// STLport 4.5.3 for_each (stl/_algo.h). Over the banners with the collector
// below it is retail 0x00215EF7 (43 bytes; the collector has a constructor,
// so it is returned through the hidden pointer).
template <class _InputIter, class _Function>
_Function for_each(_InputIter __first, _InputIter __last, _Function __f) {
	for ( ; __first != __last; ++__first)
		__f(*__first);
	return __f;
}
}

// The banner slot collector CreateBanner runs over the banners: slot i keeps
// the first banner holding it (rowed 0x00215E6F, still address-named), and
// firstFree is the inline scan for the first slot nobody holds (2 if none).
class Rva00215E6F
{
public:
	Rva00215E6F() { for (BfmePod28 **slot = m_slots; slot != m_slots + 2; ++slot) *slot = 0; }
	void rva00215E6F(unsigned int *banner);
	void operator()(BfmePod28 &banner) { rva00215E6F((unsigned int *)&banner); }
	unsigned int firstFree() const
	{
		for (unsigned int slot = 0; slot < 2; ++slot)
			if (!m_slots[slot])
				return slot;
		return 2;
	}
	BfmePod28 *m_slots[2];
};

class BannerUI
{
public:
	static void ParseBannerTypeInfo(INI *ini);
 void init();
 const AsciiString &GetBannerIconImageName(const AsciiString &key);
 int CreateBanner(int bannerID);
 void OnAptMovieInitialized(const char *path);
 void OnBannerButton(int slot);
 void OnBttnBanner(const char *path);
private:
 unsigned char m_pad00[0x0C];
 Rva00056F61 m_types;
 bool m_aptMovieInitialized;	// +0x20, WB's assert names it
 unsigned char m_pad21[3];
 int m_windowIndex;
 _STL::vector<BfmePod28, _STL::allocator<BfmePod28> > m_banners;	// +0x28
 unsigned char m_pad34[4];
 int m_38;	// +0x38
 float m_bannerXOffsets[2];	// +0x3C, SetBannerSlotXOffset's per-slot offsets
};

void BannerUI::ParseBannerTypeInfo(INI *ini)
{
	void *info;
	{
		AsciiString name(ini->getNextToken());
		info = g_00DFE32C->getTypes()->rva00216F91(name);
	}
	ini->initFromINI(info, g_00BE5A50);
}

// WB B6E990 names GetBannerIconImageName. Native216F3B..216F91 RET4
// looks up the type table at+C, retries BannerMen, then returns string+10
// in the node or TheEmptyString. The reference interface is inferred from
// that stable returned string and pointer-equivalent native argument ABI.
const AsciiString &BannerUI::GetBannerIconImageName(const AsciiString &key) {
 Rva0041534BIter it=m_types.rva0041534B(&key);
 void *node=it.m_node;
 if(!node) {
  {
   AsciiString fallback("BannerMen");
   node=m_types.rva00056F61(&fallback);
   // Retail retains this owner update in the exposed iterator slot before
   // releasing the temporary fallback key; its node result stays separate.
   it.m_table=&m_types;
  }
  if(!node)return AsciiString::TheEmptyString;
 }
 return *(const AsciiString*)((char*)node+0x10);
}

// Native216F91..217031 constructs a12-byte three-string default value and
// a16-byte key/value record. Existing21613D copy and2160C4/216108 cleanup
// prove those layouts independently; application field names remain unknown.
class Rva002160C4 {public:~Rva002160C4();};
class Rva00216108 {public:~Rva00216108();};
class Gen_003A8BE0 {
 unsigned int m_words[3];
public:
 __forceinline Gen_003A8BE0(){m_words[0]=0;m_words[1]=0;m_words[2]=0;}
 Gen_003A8BE0(const Gen_003A8BE0 &);
 __forceinline ~Gen_003A8BE0(){((Rva002160C4*)this)->~Rva002160C4();}
};
namespace _STL {
template<class A,class B>struct pair;
template<>struct pair<const AsciiString,Gen_003A8BE0> {
 pair(const AsciiString &,const Gen_003A8BE0 &);
 __forceinline ~pair(){((Rva00216108*)this)->~Rva00216108();}
 union {unsigned int m_alignment;unsigned char m_native[16];};
};
}
typedef _STL::pair<const AsciiString,Gen_003A8BE0> BannerTypePair;
class Rva000427195 {public:BannerTypePair *rva00216D5C(const BannerTypePair &);};
void *Rva00217194Types::rva00216F91(const AsciiString &name) {
 void *node;
 {Rva0041534BIter it=((Rva00056F61 *)this)->rva0041534B(&name);node=it.m_node;}
 return !node ? (char*)((Rva000427195*)this)->rva00216D5C(
  BannerTypePair(name,Gen_003A8BE0()))+4 : (char*)node+8;
}

// BFME1 BannerUI::init at donor ba7ddda is the semantic lead. BFME2 WB
// B6D600 and native216035..216094 prove the guard, slot20, two by-value
// strings, two zero arguments, and returned window index at+24. BFME1's
// third argument and separate callback registration are absent in BFME2.
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class BannerWindowLoader {
public:
 virtual void unusedSlot0()=0;
 virtual void unusedSlot1()=0;
 virtual void unusedSlot2()=0;
 virtual void unusedSlot3()=0;
 virtual void unusedSlot4()=0;
 virtual void unusedSlot5()=0;
 virtual void unusedSlot6()=0;
 virtual void unusedSlot7()=0;
 virtual void unusedSlot8()=0;
 virtual void unusedSlot9()=0;
 virtual void unusedSlot10()=0;
 virtual void unusedSlot11()=0;
 virtual void unusedSlot12()=0;
 virtual void unusedSlot13()=0;
 virtual void unusedSlot14()=0;
 virtual void unusedSlot15()=0;
 virtual void unusedSlot16()=0;
 virtual void unusedSlot17()=0;
 virtual void unusedSlot18()=0;
 virtual void unusedSlot19()=0;
 virtual int loadWindow(AsciiString directory,AsciiString movie,int arg1,int arg2)=0;
};
void BannerUI::init() {
 if(g_00DFE32C)
  m_windowIndex=((BannerWindowLoader*)g_bfmeAptWindowManager)->loadWindow("Apt\\","BannerUI.apt",0,0);
}

// BannerUI::CreateBanner, retail 0x00216DBC (383 bytes; WB 0x00B6E140 at
// BannerUI.cpp:425..452, wb-name-unverified; WB's own assert text names the
// type table m_bannerTypeInfoMap). The banner takes the first of
// the two slots no current banner holds (else -1); its type is the army
// banner name GameLogic reports for the id (BannerMen when that is empty),
// looked up in the type table at +0x0C (unknown type: -1). The movie's
// AddBanner gets the slot, the type name and the type's first string, the
// banner is appended, and the slot's timer text APT:BannerTimer%d is
// cleared. Returns the slot.
extern GameLogic *TheGameLogic;

class Rva00222A8BTarget;
int __cdecl Rva00216496Invoke(Rva00222A8BTarget *target, void *owner, const char *name, const unsigned int &a, const AsciiString &b, const AsciiString &c);

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &key, const UnicodeString &text, bool usePlaceholder);
};

template Rva00215E6F _STL::for_each<BfmePod28 *, Rva00215E6F>(BfmePod28 *, BfmePod28 *, Rva00215E6F);

// WB's record constructor clears every field before CreateBanner assigns
// the ones it sets; retail keeps the stores that survive, in that order.
static inline void clearBannerRecord(BfmePod28 &banner)
{
	banner.bannerID = 0;
	banner.typeEntry = 0;
	banner.unknown0C = 0;
	banner.unknown10 = 0;
	banner.unknown14 = 0;
	banner.unknown18 = false;
}

int BannerUI::CreateBanner(int bannerID)
{
	BfmePod28 banner;
	clearBannerRecord(banner);
	banner.bannerID = bannerID;
	banner.unknown0C = 0;
	banner.unknown10 = 0;
	banner.unknown14 = -1;

	Rva00215E6F used;
	used = _STL::for_each(m_banners.begin(), m_banners.end(), used);
	unsigned int slot = used.firstFree();
	banner.slot = slot;
	if (banner.slot < 0 || banner.slot >= 2)
		return -1;

	AsciiString typeName(*TheGameLogic->rva0023D06A(bannerID));
	if (typeName.isEmpty())
		typeName = "BannerMen";
	// Retail keeps the iterator's table store (+0x0C into [ebp-0x20]) only
	// when the iterator is assigned from find after being declared.
	BannerTypeIterator it(0, 0);
	it = m_types.find(typeName);
	if (!it.m_node)
		return -1;

	const AsciiString *typeEntry = (const AsciiString *)((char *)it.m_node + 8);
	banner.typeEntry = typeEntry;
	Rva00216496Invoke((Rva00222A8BTarget *)g_bfmeAptWindowManager, (void *)m_windowIndex, "AddBanner", banner.slot, typeEntry[0], typeEntry[1]);
	m_banners.push_back(banner);

	AsciiString timerName;
	timerName.format("APT:BannerTimer%d", slot);
	g_bfmeAptWindowManager->bfmeSetText(timerName, UnicodeString(L""), false);
	return slot;
}

// BannerUI::OnAptMovieInitialized, retail 0x00217071 (291 bytes; WB
// 0x00B6DC60 at BannerUI.cpp:348..368, wb-name-unverified). Once, after the
// movie loads and while the game logic exists: when the living world logic
// is active and not selection-locked, the current battle's banner ids for the
// local player's army (LivingWorldBattle 0x003F5BDB into an id vector) each
// get CreateBanner. Every slot whose X offset is set is pushed to the movie
// (SetBannerXOffset), +0x38 is reset and the movie is marked initialized.
// The constructor 0x00217211 binds it as the Apt command
// "AptBannerUI::OnInitialized", so it takes the command path.
// The id vector is spelled as the vector<ScienceType> the rowed battle method
// takes; its base ctor is the folded _Vector_base pin 0x00211E58 and its
// storage goes back through the game free 0x00030830, as STLport's
// _Vector_base dtor does under the BFME allocator.
enum ScienceType {};
extern "C" void __cdecl free(void *memory);	// 0x00030830, the game free
namespace _STL {
template <class T, class A> class _Vector_base {
public:
	_Vector_base(const A &a);	// 0x00211E58
	~_Vector_base() { if (_M_start) free(_M_start); }
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
template <> class vector<ScienceType, allocator<ScienceType> > : public _Vector_base<ScienceType, allocator<ScienceType> > {
public:
	typedef ScienceType *iterator;
	__forceinline vector() : _Vector_base<ScienceType, allocator<ScienceType> >(allocator<ScienceType>()) {}
	iterator begin() { return _M_start; }
	iterator end() { return _M_finish; }
};
}

class Rva002E2903Player;
class LivingWorldBattle
{
public:
	void rva003F5BDB(void *army, _STL::vector<ScienceType, _STL::allocator<ScienceType> > *armyIDs);	// 0x003F5BDB
};
class Rva0020E6B7RegionManager
{
public:
	LivingWorldBattle *rva0020E6B7();	// 0x0020E6B7, the current battle
};
class BfmeSelectionState
{
public:
	bool isSelectionLocked() const;	// 0x0004253A
};
class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *out);	// 0x002B51F8
};
class LivingWorldLogic
{
public:
	Rva0020E6B7RegionManager *getRegionManager() const { return m_regionManager; }
	bool isActive() const { return m_active; }
private:
	unsigned char m_pad00[0xB0];
	Rva0020E6B7RegionManager *m_regionManager;	// +0xB0
	bool m_active;	// +0xB4
};
extern LivingWorldLogic *TheLivingWorldLogic;

class Player
{
public:
	int getArmyID() const { return m_armyID; }
private:
	unsigned char m_pad000[0x3AC];
	int m_armyID;	// +0x3AC
};
class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }
private:
	unsigned char m_pad00[0x10];
	Player *m_local;	// +0x10
};
extern PlayerList *ThePlayerList;

int __cdecl Rva0021642FInvoke(Rva00222A8BTarget *target, void *owner, const char *name, const float &value);

void BannerUI::OnAptMovieInitialized(const char *path)
{
	if (m_aptMovieInitialized)
		return;
	if (TheGameLogic == 0)
		return;

	LivingWorldLogic *logic = TheLivingWorldLogic;
	if (logic && logic->isActive() && !((BfmeSelectionState *)logic)->isSelectionLocked())
	{
		LivingWorldBattle *battle = logic->getRegionManager()->rva0020E6B7();
		if (battle)
		{
			Player *player = ThePlayerList->getLocalPlayer();
			Rva002E2903Player *army = player ? ((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(player->getArmyID(), 0) : 0;
			if (army)
			{
				_STL::vector<ScienceType, _STL::allocator<ScienceType> > armyIDs;
				battle->rva003F5BDB(army, &armyIDs);
				for (_STL::vector<ScienceType, _STL::allocator<ScienceType> >::iterator it = armyIDs.begin(); it != armyIDs.end(); ++it)
					CreateBanner(*it);
			}
		}
	}

	for (unsigned int slot = 0; slot < 2; ++slot)
		if (m_bannerXOffsets[slot] != 0.0f)
			Rva0021642FInvoke((Rva00222A8BTarget *)g_bfmeAptWindowManager, (void *)m_windowIndex, "SetBannerXOffset", m_bannerXOffsets[slot]);

	m_38 = -1;
	m_aptMovieInitialized = true;
}

// BannerUI::OnBannerButton, retail 0x002166BB (122 bytes; WB 0x00B6EBD0,
// wb-name-unverified), and the Apt command the constructor binds as
// "AptBannerUI::OnBttnBanner", retail 0x00216735 (26 bytes), which passes it
// atoi of the command path. Entry 0x002166BB is proven by that command's
// call and 0x00216735 by the constructor's DIR32; both end at their RET 4.
// The banner in the pressed slot (the rowed slot lookup 0x00216245, still
// spelled on an address-named owner) is acted on once: in state 0 the
// message 0x45E carries its banner id; in state 2 the script engine gets the
// banner's army name (GameLogic 0x0023D05F, script call 0x00357DAC), message
// 0x45F carries the id and the banner is marked handled (+0x18).
class Rva00216245
{
public:
	BfmePod28 *rva00216245(int slot);	// 0x00216245
};

class GameMessage
{
public:
	void appendIntegerArgument(int arg);	// 0x0030F936
};

#define V(n) virtual void vslot##n() = 0;
class MessageStream
{
public:
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17)
	virtual GameMessage *appendMessage(int type) = 0;	// slot 18, 0x0030F6D4
};
#undef V
extern MessageStream *TheMessageStream;

class ScriptEngine
{
public:
	void rva00357DAC(const AsciiString &name);	// 0x00357DAC
};
extern ScriptEngine *TheScriptEngine;

// msvcr71's atoi, called through its import as <stdlib.h> declares it under /MD.
extern "C" __declspec(dllimport) int __cdecl atoi(const char *text);

void BannerUI::OnBannerButton(int slot)
{
	BfmePod28 *banner = ((Rva00216245 *)this)->rva00216245(slot);
	if (banner && !banner->unknown18)
	{
		if (banner->unknown0C == 0)
		{
			GameMessage *msg = TheMessageStream->appendMessage(0x45E);
			msg->appendIntegerArgument(banner->bannerID);
		}
		else if (banner->unknown0C == 2)
		{
			TheScriptEngine->rva00357DAC(*TheGameLogic->rva0023D05F(banner->bannerID));
			GameMessage *msg = TheMessageStream->appendMessage(0x45F);
			msg->appendIntegerArgument(banner->bannerID);
			banner->unknown18 = true;
		}
	}
}

void BannerUI::OnBttnBanner(const char *path)
{
	OnBannerButton(atoi(path));
}
