// cl: /O1 /G7 /arch:SSE /GX- /MD /DNDEBUG /Ireference/shims/bfme2_ascii /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// Split from GapBodiesSeat1A.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// Small GameEngine bodies from .text gaps no ledger row covered (each begins
// after its neighbour's padding or return and ends in its own ret). Retail
// bytes establish every shape below; the owning classes are not recovered, so
// each keeps an address-derived name and a view of only the members it
// touches. Callees are the ledger's existing rows under their current
// spellings.
#include "GameLogicObjectLookupView.h"
#include "ascii_string.h"
#include "unicode_string.h"
#include "RTS/XYDistanceCallView.h"

extern GameLogic *TheGameLogic;

class GlobalData;
extern GlobalData *TheWritableGlobalData;

// --- 0x00203582 (19B): adds the argument to the float at +0x48.
// --- 0x00203671 (23B): stores a non-negative argument into
// TheWritableGlobalData's word at +0xAC8; the receiver is unused.
// --- 0x00203E65 (17B): 1 when TheGameLogic->rva001DCD1C() is false, else 0
// (sibling of the rowed 0x00203688/0x00203693 wrappers).
// --- 0x00205A1B (16B): returns by value a pair {0, &this[+0x0C]}.
// --- 0x00210EAC (19B): returns a zero float pair by value; both word
// arguments and the receiver are unused.
// --- 0x00215E5F (16B): 1 when the argument's first word equals this one's.
// --- 0x00215E87 (18B): the index of the first null of two slots, else 2.
// --- 0x0021982A (16B): the halfword at +4 of the node the first word points
// at, or 0 without a node.
// --- 0x002224DE (32B): false past the fourteenth 0x28-byte record at +0xF0,
// else the inverse of that record's second flag bit.
// --- 0x002226A2 (28B): constructor from a flag and an eight-byte pair.
struct Rva002226A2Pair
{
	int m_00;
	int m_04;
};

// --- 0x00225A81 (18B): copies an eight-byte pair to +0x38.
// --- 0x0022CF6E, 0x0022CF9F (18B each): the rowed timing hooks applied to
// the argument twice, as the rowed 0x0022D189 setter calls the first.
int Rva0022CB5CHook(int a, int b);
int Rva0022CC0EHook(int a, int b);

// --- 0x0022D979 (20B): sets the timing value from the pointed word through
// the rowed 0x0022D189 setter and returns this.
// --- 0x0023262C (23B): whether the halfword at +6 of the indexed 8-byte
// record at +0x18 shares a bit with the mask.
// --- 0x0023426A (30B): constructor from an eight-byte pair and a halfword;
// 0x002342C5 (16B): copies the first halfword out and returns 1.
// --- 0x00239B11 (24B): one node from the freelist pool at VA 0x00DBA5E0
// (rowed pop), none for a count above one; the second word is unused.
#include "../../Include/Common/FreelistPool.h"
extern FreelistPool g_freelistPool00DBA5E0;

// --- 0x0023DB48 (16B): latches +0x38 into an unset +0x40 and returns it.
// --- 0x0023E887 (28B): constructor copying a word and building the string
// at +4 from the source's text.
// --- 0x00254628 (34B) and 0x002546EB (34B): module-data field parsers,
// each the rowed base table 0x004CE29D at offset 8 then its own table (VA
// 0x00BF247C, VA 0x00BF2534); 0x0025464A (52B) and 0x0025470D (52B): their
// INI factories over 0x11C-byte data built by the rowed constructors
// 0x0025460F and 0x002546D2 (the latter folds with RadarUpgradeModuleData's).
class INI;
#include "../../Include/Common/INI/FieldParse.h"
class ModuleData;

#include "../../Include/Common/INI/INI.h"

int Rva004CE29DGet(void);
extern const FieldParse s_Rva00254628FieldParse[];			// VA 0x00BF247C
extern const FieldParse s_Rva002546EBFieldParse[];			// VA 0x00BF2534
const FieldParse s_Rva00254628FieldParse[] = {
    { "DelayTime", INI::parseDurationUnsignedInt, 0, 0x118 },
    { 0, 0, 0, 0 }
};
const FieldParse s_Rva002546EBFieldParse[] = {
    { "KillLocomotorUpgrade", INI::parseBool, 0, 0x118 },
    { 0, 0, 0, 0 }
};


class Rva0025460F
{
public:
	Rva0025460F();
private:
	char m_pad[0x11C];
};

class RadarUpgradeModuleData
{
public:
	RadarUpgradeModuleData();
private:
	unsigned char m_pad[0x11C];
};

class Rva00254628ModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &p);
};

void Rva00254628ModuleData::buildFieldParse(MultiIniFieldParse &multiIniFieldParse)
{
	multiIniFieldParse.add((const FieldParse *)Rva004CE29DGet(), 8);
	multiIniFieldParse.add(s_Rva00254628FieldParse, 0);
}

// ModuleFactory::init registers 0x0025464A (DelayedUpgrade) and 0x0025470D
// (LocomotorSetUpgrade) as data factories; they keep the address-derived
// names of their symbols.csv pins like their unowned peers.
ModuleData *ModuleFactoryDataAt0025464A(INI *ini)
{
	Rva0025460F *data = new Rva0025460F;
	if (ini)
		ini->initFromINIMultiProc(data, Rva00254628ModuleData::buildFieldParse);
	return (ModuleData *)data;
}

class Rva002546EBModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &p);
};

void Rva002546EBModuleData::buildFieldParse(MultiIniFieldParse &multiIniFieldParse)
{
	multiIniFieldParse.add((const FieldParse *)Rva004CE29DGet(), 8);
	multiIniFieldParse.add(s_Rva002546EBFieldParse, 0);
}

ModuleData *ModuleFactoryDataAt0025470D(INI *ini)
{
	RadarUpgradeModuleData *data = new RadarUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, Rva002546EBModuleData::buildFieldParse);
	return (ModuleData *)data;
}

// --- 0x0025F342 (67B): swaps a marker into the +0x80 list in place of the
// one with the same name, returning the unlinked one (or null); 0x0025F3AE
// (69B): unlinks and deletes the marker with the argument's name.
class CameraMarker
{
public:
	~CameraMarker();										// 0x0029D7C2
	CameraMarker *m_next;
	AsciiString m_name;
};

// --- 0x002602C1 (25B): constructor from a unicode string and a word.
// --- 0x00260DCF (13B): bit 3 of the byte at +0x438.
// --- 0x00260DDC (17B) and 0x0026223A (17B): the +4 word of the record at
// +0x04 / +0x50, or 999999 without one.
// --- 0x00262263 (14B): byte +8 set and byte +0x0A clear.
// --- 0x00260E0D (17B): 1 when the object is not on an airborne locomotor.
enum ObjectStatusTypes { OBJECT_STATUS_4 = 4 };
enum ObjectScriptStatusBit { OBJECT_SCRIPT_STATUS_0 };
struct Coord3D;

class Object
{
public:
	bool isUsingAirborneLocomotor() const;					// 0x0028B81E
	int rva0028B511() const;								// 0x0028B511
	bool isMassSelectable() const;								// 0x00292FAC
	bool testStatus(ObjectStatusTypes status) const;		// 0x0004E536
	void rva0028D611(Object *other, int a, int b);
	float GetRelativeAngle(const Coord3D *pos) const;		// 0x000B4542
	float rva0028F8A3(const Object *other) const;
	void setScriptStatus(ObjectScriptStatusBit bit, bool set);	// 0x00292969
	void rva002934D9(ObjectScriptStatusBit bit);
	void rva00294C1A(Object *other, bool flag, float scale);	// 0x00294C1A
	int m_pad00[0x74 / 4];
	int m_74;												// +0x74
	char m_pad78[0x244 - 0x78];
	void **m_modules;										// +0x244, null-terminated
	char m_pad248[0x484 - 0x248];
	int m_484;												// +0x484
};

// --- 0x00260F3B (21B): the argument's +0x304 word equals this +8 word.
// --- 0x00261750 (30B): allow() of the thing-template partition filter
// (vftable 0x00C1FDEC; Zero Hour's PartitionFilterThing): whether the +8
// template's rowed isEquivalentTo the object's +4 template agrees with the
// +0x0C flag; 0x0026176E (34B): the same over the rowed 0x00376A62 test of
// that template's +0x64 name.
#include "../../Include/Common/ThingTemplate.h"

class ObjectTypes
{
public:
	bool isInSet(const AsciiString &name) const;			// 0x00376A62
};

// --- 0x002619AE (19B): the argument's rowed BitFlags<69>::test of this
// +0x108.
template <int N> class BitFlags
{
public:
	bool test(const void *other) const;
};

// --- 0x002628E0 (25B): the +0x224 owner's rowed removeFromMatching of the
// argument's +0x74 word and the second argument.
class Rva00331CBAVectorOwner
{
public:
	void removeFromMatching(int entry, int key);			// 0x00331CBA
};

// --- 0x00262B7D (44B): TheAI's pathfinder (+0x10) validates a position for
// the +8 object with its rowed 0x0028B511 answer and this +0x1DC word.
struct Coord3D;
#include "../../Include/GameLogic/AIPathfind.h"

class AI;
extern AI *TheAI;

// --- 0x002636E6 (16B): the rowed squared distance to the argument's +0x38
// point.
// --- 0x002638CC, 0x002638E4 (14B each): Locomotor flag setters for flags 6
// and 3 through the rowed private setFlag.
#include "../../Include/GameLogic/LocomotorClass.h"




// --- 0x00265681 (16B): returns by value the word the +4 handle's pointer
// addresses.
// --- 0x0026891F (27B): constructor storing two words, then the rowed
// 0x002654D6 reset.
class Rva002654D6
{
public:
	Rva002654D6(int a, int b);
	void rva002654D6();										// 0x002654D6
private:
	int m_00;
	int m_04;
};



// --- 0x0026FCF9 (14B): the indexed word of the array at +0x148.
// --- 0x0027175F (26B): 1 when the +0xFC object answers the rowed
// 0x00292FAC test.
// --- 0x0027229B (15B): bit 20 of +0x98 clear.
struct GapVoidVector
{
	void **m_start;
	void **m_finish;
	void **m_end;
};

static __forceinline int GapVoidVectorCount(const GapVoidVector *gapVoidVector) { return gapVoidVector->m_finish - gapVoidVector->m_start; }

// Dummy virtual slots for call views; only the slot index matters.
#define GAP_V1(n) virtual void v##n();
#define GAP_V10(n) GAP_V1(n##0) GAP_V1(n##1) GAP_V1(n##2) GAP_V1(n##3) GAP_V1(n##4) GAP_V1(n##5) GAP_V1(n##6) GAP_V1(n##7) GAP_V1(n##8) GAP_V1(n##9)

// --- 0x00272366 (45B): the +0x14C holder's object's slot-42 answer, when
// there is one, handles the three arguments in its slot 0; else false.
class Rva00272366Handler
{
public:
	virtual bool handle(int a, int b, int c);
};

class Rva00272366Target
{
public:
	GAP_V10(0) GAP_V10(1) GAP_V10(2) GAP_V10(3)
	GAP_V1(40) GAP_V1(41)
	virtual Rva00272366Handler *getHandler();				// slot 42
	GAP_V1(43) GAP_V1(44) GAP_V1(45) GAP_V1(46) GAP_V1(47) GAP_V1(48) GAP_V1(49)
	GAP_V1(50) GAP_V1(51) GAP_V1(52) GAP_V1(53)
	virtual void slot54(int a, int b);						// slot 54
};

// --- 0x002785D6 (37B): changes the +0x447 flag, then on set the rowed
// 0x002783F6(0), on clear the rowed 0x002743D7; 0x0027862C (24B): changes the
// +0x449 flag, then the rowed 0x002784EB.
class Rva002783F6Host
{
public:
	void rva002783F6(int value);							// 0x002783F6
};

#include "../../Include/GameClient/Drawable.h"



// --- 0x0027C226 (10B, cdecl): sets the word at VA 0x00DBB708.
extern int g_Va00DBB708;


// --- 0x0027C280 (36B): stores three floats at +0x1C.
// --- 0x0028565F (19B): calls the cdecl function pointer at +0x9C;
// 0x002856B7 (15B): the argument is at most +0x3C.
// --- 0x00285760 (13B): drops a reference (+4) and frees through the rowed
// 0x0020DAE0 at zero.
void Rva0020DAE0(void *p);

// --- 0x00285A0A (12B, cdecl): the argument's slot 11 with 0.
// --- 0x00285A16, 0x0028878C (16B each): the rowed comparisons of the first
// argument with the second; the receiver is unused.
class Rva00285672
{
public:
	bool rva00285672(const Rva00285672 &other) const;		// 0x00285672
};

class ExperienceLevel
{
public:
	bool operator<(const ExperienceLevel &other) const;	// 0x00288621
};

// --- 0x0028667F (20B): the rowed 0x00286214 find returned by value.
struct Rva00286214Node;
struct Rva0028667FIterator
{
	Rva0028667FIterator(Rva00286214Node *node) : m_node(node) {}
	Rva00286214Node *m_node;
};

class Rva00286214
{
public:
	Rva00286214Node *rva00286214(const Rva00285672 *key);	// 0x00286214
	Rva0028667FIterator rva0028667F(const Rva00285672 *key);
};


// --- 0x002895AF (11B): erases every marker through the rowed erase.
class CameraMarkerVec
{
public:
	CameraMarker *erase(CameraMarker *first, CameraMarker *last);	// 0x0048D042
	void rva002895AF();
	CameraMarker *m_start;
	CameraMarker *m_finish;
	CameraMarker *m_end;
};


// --- Object-region leaves: 0x0028A638 (12B) +0x464 set; 0x0028A644 (12B)
// bit 1 of +0x438; float setters 0x0028A6B6 (+0x444), 0x0028A7C7 (+0x200),
// 0x0028BB8D (+0x1B8); 0x0028A7B7 (16B) byte +1 equals the argument;
// 0x0028A84B (23B) bit test of +0x30; 0x0028B975 (15B) resets +0x490/+0x48C;
// 0x0028C8CD (18B) and 0x0028F2E6 (18B) pointer-vector counts at +0x234 and
// +0x4A4.
// --- 0x0028BC29 (18B): the +0x23C field's rowed flag, false without one.
class Rva003B8ACFCmpBoolField
{
public:
	bool get() const;										// 0x003B8ACF
};

// --- 0x0028BC3B (18B): the same +0x23C field's second query, false without
// one; the tail jump to 0x004DF49C (list size != 0) shows a bool result.
class Rva00256AB0Owner
{
public:
	bool hasEntries() const;								// 0x004DF49C
};

class Rva0028BC3B
{
public:
	bool rva0028BC3B() const;
private:
	char m_pad000[0x23C];
	Rva00256AB0Owner *m_field;
};

bool Rva0028BC3B::rva0028BC3B() const
{
	if (m_field == 0)
		return false;
	return m_field->hasEntries();
}

// --- 0x0028C59F (14B): zeroes twenty bytes of this through the CRT memset
// thunk 0x006291AE.
// memset is msvcr71's, called through its import thunk at 0x006291AE
// rather than expanded inline: <string.h>'s memset with
// #pragma function(memset).
#include <string.h>
#pragma function(memset)

// --- 0x0028D611 (111B): unless the other object shares this one's +0x484
// relation (against its +0x74 id) or both carry one, each module whose
// +0x0C interface (slot 1) yields a handler passes it the three arguments,
// stopping when this object has status 4.
// --- 0x00282206 (12B): pops the last 8-byte element, running its rowed
// destructor 0x0027EA49.
class Rva0027EA49
{
public:
	~Rva0027EA49();											// 0x0027EA49
private:
	int m_00;
	int m_04;
};

// --- 0x00282794 (11B): reserves the +0x578 module-data vector;
// 0x0028A665 (11B): the +0x330 material pass's texture for a stage;
// 0x0028C8BD (11B): ORs a bitset into +0x284.
class ModuleData;
class TextureClass;
namespace _STL
{
	template <class T> class allocator;
	template <class T, class A> class vector
	{
	public:
		void reserve(unsigned int n);
	private:
		T *m_start;
		T *m_finish;
		T *m_end;
	};
	template <int N> struct _Base_bitset
	{
		void _M_do_or(const _Base_bitset &other);
		unsigned int m_words[N / 32];
	};
}

#include "../../../Libraries/Source/WWVegas/WW3D2/MaterialPassClass.h"

// --- 0x0028F898 (11B): assigns the argument to the +0x94 member through its
// rowed operator=.
class Rva001EAFC1
{
public:
	Rva001EAFC1 &operator=(const Rva001EAFC1 &other);		// 0x001EAFC1
};

// --- 0x00294D4B (22B, cdecl): the rowed 0x00294C1A on the first object with
// the second, false and 1.0.
void Rva00294D4B(Object *obj, Object *other)
{
	obj->rva00294C1A(other, false, 1.0f);
}

// --- 0x0028F92B (21B): returns by value the rowed 0x0028F633 pair of 0 and
// this +0x38 word.
class Rva0028F633
{
public:
	Rva0028F633(int a, int b);								// 0x0028F633
private:
	int m_00;
	int m_04;
};

// --- 0x00298941, 0x0029894C (11B, 14B): erase every element of the vector
// at +0 / +0x20 through the rowed EraseRange.
class Rva00297360Element;
class Rva002983DAVector
{
public:
	Rva00297360Element *EraseRange(Rva00297360Element *first, Rva00297360Element *last);	// 0x002983DA
	void rva00298941();
	void clear() { EraseRange(m_start, m_finish); }
	Rva00297360Element *m_start;
	Rva00297360Element *m_finish;
	Rva00297360Element *m_end;
};


// --- 0x0029A48A (30B): sets the low end of the +0x58 range of the +0
// record, if any.
// --- 0x0029B5CD (11B): forwards to the rowed body on the +0x9BC object.
class AnimateWindow;
class ProcessAnimateWindowSlideFromBottomTimed
{
public:
	virtual bool reverseAnimateWindow(AnimateWindow *win);	// 0x005CB265
};

// --- 0x0029E0E6 (24B): one node from the freelist pool at VA 0x00DA60E8
// (rowed pop), none for a count above one.
extern FreelistPool g_freelistPool;

// --- 0x0029FE9E (29B): the rowed 0x0029BA28 with the word, then appends it
// to the +0x18 int list.
namespace _STL
{
	template <class T, class A> class list
	{
	public:
		void push_back(const T &value);
	private:
		void *m_node;
	};
}

class Rva0029BA28
{
public:
	void rva0029BA28(int value);							// 0x0029BA28
	void rva0029FE9E(int value);
private:
	char m_pad00[0x18];
	_STL::list<int, _STL::allocator<int> > m_18;
};


// --- Small Player-region leaves: 0x002A71B1 (11B) word of the +0x60 array;
// 0x002A73A4/0x002A73AE (10B) add/subtract +0x0C; 0x002A97ED/0x002A97F7
// (10B) add to +0x18/+0x1C.
// --- 0x002A7F6C (20B): the +0x0C field of the indexed 16-byte record at
// *(+0xF50); 0x002AAE59 (20B) and 0x002AAE6D (20B): the +0 halfword and the
// +0x0C field of the indexed 16-byte record at *(+0xF6C).
// --- 0x002A87F9 (15B, cdecl): clears the two skirmish-AI words at VA
// 0x00DFEFC0 and 0x00DFEFC4.
extern unsigned g_00DFEFC0, g_AITargetThreatFinderSerial;


// --- 0x002A9BE3 (15B): constructor from a flag with a cleared +4 word.
// --- 0x002AA2BB (14B): count of the 0xD8-byte records of the vector at +0;
// 0x002AAC2E (15B): the indexed record.
// --- 0x002AA842 (21B): the pointer-vector count at +0x18C of the +0x34
// object.
// --- 0x002AAC3D (24B): returns a node to the free list at VA 0x00DBBD34.
struct PoolNode002ABAC0
{
	PoolNode002ABAC0 *m_next;
};

// --- 0x002AAEB5 (16B): the indexed 0x24-byte record at *(+0x324).
// --- 0x002ABB86 (24B): one node from the freelist pool at VA 0x00DBBD2C,
// none for a count above one; 0x002ACF8A (18B): constructor running the
// rowed init.
extern FreelistPool g_freelistPool009BBD2C;

class Rva002AC026Member
{
public:
	Rva002AC026Member(void *context);
	void *init(void *context);								// 0x002AC026
private:
	void *m_head;
};


// --- 0x002AD7E9 (61B): the +8 interface of a player feeds the record's
// +0x34 word to its +0x3B4 member (rowed 0x0039B668), then grants each
// science of the record's +0x38 list through Player's rowed private
// addScience; 0x002B1192 (21B): the +4 interface stores Player's rowed
// 0x002AB855 answer for the hero data.
enum ScienceType { SCIENCE_INVALID = -1 };
class CreateAHeroData;

class Rva0039B668
{
public:
	void rva0039B668(int value);							// 0x0039B668
};

struct Rva002AD7E9Record
{
	char m_pad00[0x34];
	int m_34;
	int *m_sciencesStart;
	int *m_sciencesFinish;
};

class Rva002AD7E9Base0
{
	int m_00;
};

class Rva002B1192Interface
{
public:
	void rva002B1192(CreateAHeroData *data, bool *out);
private:
	int m_00;
};

class Rva002AD7E9Interface
{
public:
	void rva002AD7E9(const Rva002AD7E9Record *record);
private:
	char m_pad000[0x3B4];
	Rva0039B668 m_3B4;
};

#include "../../Include/Common/Player.h"



// --- LivingWorld-region leaves: 0x002B2221 (18B) copies a pair to +0x20;
// 0x002B2260 (14B) the +8 record's +0x4C word or 0; 0x002B229B (10B) ORs
// into +0x14; 0x002B238A (17B) float setter +0x1C8; 0x002B244D (14B) the
// +0x0C field of the indexed 16-byte record at +0.
// --- 0x002B22FA (21B): 1 for a second argument of 0 or 1.
// --- 0x002B2997 (38B): when TheLivingWorldLogic's +0xC8 flag is set, the
// campaign manager's rowed 0x003B8CAC runs and the flag clears.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva00E02D6C;
extern Rva00E02D6C *TheCampaignManager;
#include "../../Include/Common/LivingWorldCampaignManager.h"

// --- 0x002B29EA (14B): stores the second argument at +0x38 of the first.
// --- 0x002B2B3F (28B): the current item's +0x88 flag when the +0xB0
// region manager exists; 0x002B2B94 (11B): the manager's rowed
// UpdateBattleMarkers.
struct Rva002B3740Item
{
	char m_pad00[0x88];
	bool m_88;
};

#include "../../Include/GameLogic/LivingWorldRegionManager.h"

class Rva002E2903Player;
struct Rva002B488EResult;

#include "../../Include/GameLogic/Rva002BA8F1Logic.h"



// --- 0x002B2B9F (11B): TheScriptEngine's slot 10.
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

// --- 0x002B30D9 (19B): the +0x154 pointer vector is not empty;
// 0x002B30EC (15B): count of the 8-byte records of the +0x40 vector of the
// +0x78 object; 0x002B3150 (11B): pre-increments +0x9C.
static __forceinline bool GapVoidVectorAny(const GapVoidVector *gapVoidVector) { return gapVoidVector->m_start != gapVoidVector->m_finish; }

struct Rva002B30ECVector
{
	Rva002226A2Pair *m_start;
	Rva002226A2Pair *m_finish;
};

static __forceinline int Rva002B30ECCount(const Rva002B30ECVector *v) { return v->m_finish - v->m_start; }



// --- 0x002B386A (35B): names the campaign's GUI image by the campaign
// manager's +0x2C evil flag.
// --- 0x002B3DA4 (14B, cdecl): the rowed 0x002B3D81 value divided by the
// word at VA 0x00DBA4E4.
int rva002B3D81();
extern int BfmeLogicFramesPerSecond;


// --- 0x002B4404 (12B, cdecl): the rowed 0x002B2F49 with 0 on the argument.
class Rva002B2F49
{
public:
	void *rva002B2F49(unsigned int value);					// 0x002B2F49
};


// --- 0x002B4640 (16B): the indexed word of the array *(+0x170).
// --- 0x002B4E6D (22B): copies the argument's +0x14 flag to +0xC8, then the
// rowed 0x002B4CED with it.
struct Rva002B4E6DArg
{
	char m_pad00[0x14];
	bool m_14;
};

class Rva002B4CED
{
public:
	void rva002B4CED(void *arg);							// 0x002B4CED
	void rva002B4E6D(Rva002B4E6DArg *arg);
private:
	char m_pad00[0xC8];
	bool m_C8;
};


// --- 0x002B685D (24B): the rowed 0x002B5B55 on the rowed 0x002B488E result.
struct Rva002B488EResult;
class Rva002B5B55Arg;

class Rva002B5B55
{
public:
	void rva002B5B55(Rva002B5B55Arg *arg);					// 0x002B5B55
};


// --- 0x002B77A2 (11B): clears the +0xF0 unicode-string list.
namespace _STL
{
	template <class T, class A> class _List_base
	{
	public:
		void clear();
	private:
		void *m_node;
	};
}

// Unattempted scalar leaves from the native gap audit. Each complete body
// starts after a preceding body's RET or padding and ends in its own RET.
// Native accesses establish the offsets and the 32-bit/byte ABI below;
// original classes, field meanings and signedness remain unasserted. These
// neutral views describe only the observed operations, as above.
// --- 0x00235A00 (14B, RET4): a constructor copying its one word argument
// into both +0 and +4 and returning this (twin skeleton of
// Rva006CD500WordPair 0x006CD500). It follows the MultiPlayMults getters; the
// owner and the word's meaning are unknown.
