// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// class-gate: allow GameLogic the destructor needs the full two-base class whose vtables 0x00BEE130/0x00BEE120 it stores; the shared view header is a non-virtual lookup view
// class-gate: allow SubsystemInterface GameLogicInit.cpp's 14-slot view, so this unit emits the same ??_7GameLogic COMDAT as the constructor's unit (the shared header declares only the destructor)
// ??1GameLogic@@UAE@XZ, retail 0x00243BA0..0x00243EDF (831 bytes, EH):
// GameLogic::~GameLogic: it stores the tables 0x00BEE130 (+0) and Snapshot's
// 0x00BEE120 (+0xC) that GameLogic's constructor 0x002470AE installs, its
// scalar deleting destructor 0x00246213 is slot 0 of 0x00BEE130, and
// ~W3DGameLogic 0x0004208C tail-jumps to it as its base destructor. Under a TheGameLogic
// guard (rowed constructor 0x0004224C; its inline destructor folds away once
// TheGameLogic is cleared, the unwind copy is 0x00042262) it clears the
// +0x1C0 name list, destroys every object (rowed destroyAllObjectsImmediate
// 0x00243B52), deletes the terrain logic, ghost object, partition, shroud
// and collision managers, its three +0x170.. owned objects, the script
// actions and conditions, the large group audio and the buff logic, runs
// the rowed 0x0023E7D9 and GameLogic::rva00376D49 on itself and clears
// TheGameLogic. Retail's 24-state unwind map then destroys the members:
// +0x1C4 records (eh vector iterator, element 0x0023DC86), the +0x1C0 list
// (unwind copy 0x00207F08), +0x184 (rowed 0x0040DB52), +0x164 buffer
// (0x001F22A3), +0x108 (its destructor body runs 0x001EB769; unwind copy
// 0x001EB940), +0xF8
// buffer, four +0xC8 buffers, the +0xB4 table (0x00240C27, unwind thunk
// 0x00240E13), the +0x8C/+0x88 handles, eight strings, the +0x58 string
// vector, the +0x50 observer list (unwind 0x00200667), the +0x24 member
// (0x00242EAF, thunk 0x00243B4D), the +0x10 table (0x00242E71, thunk
// 0x00243B48), Snapshot and SubsystemInterface.
#include <list>
#include <vector>
#include "ascii_string.h"
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

void __cdecl Rva00030830GameFree(void *);

struct Rva004FA1FObserver;
namespace _STL {
template<> void _List_base<AsciiString, allocator<AsciiString> >::clear();
template<> _List_base<AsciiString, allocator<AsciiString> >::~_List_base();
template<> _List_base<Rva004FA1FObserver *, allocator<Rva004FA1FObserver *> >::~_List_base();
template<> vector<AsciiString, allocator<AsciiString> >::~vector();
}


class GameLogic;

struct Rva0004224CLogic
{
	unsigned char m_pad00[0x1B4];
	int m_1B4;
};

extern GameLogic *TheGameLogic;

// Holds TheGameLogic's +0x1B4 count raised for its lifetime.
class Rva0004224C
{
public:
	Rva0004224C();
	~Rva0004224C() { if (TheGameLogic) --((Rva0004224CLogic *)TheGameLogic)->m_1B4; }
};

class Rva00243BA0Owned
{
public:
	virtual ~Rva00243BA0Owned();
};

class TerrainLogic;
class GhostObjectManager;
class PartitionManager;
class CollisionManager;
class ScriptActions;
class ScriptConditions;
class LargeGroupAudio;
class BuffLogic;
extern TerrainLogic *TheTerrainLogic;
extern GhostObjectManager *TheGhostObjectManager;
extern PartitionManager *ThePartitionManager;
extern PartitionManager *TheShroudManager;
extern CollisionManager *TheCollisionManager;
extern ScriptActions *TheScriptActions;
extern ScriptConditions *TheScriptConditions;
extern LargeGroupAudio *TheLargeGroupAudio;
extern BuffLogic *TheBuffLogic;

struct Rva0023E7D9Link;
class Rva0023E7D9
{
public:
	void rva0023E7D9();
	void rva0023F88C(bool loadingSaveGame);
	char m_lead[0x48]; // +0x00
	Rva0023E7D9Link *m_head; // +0x48
	_STL::list<int, _STL::allocator<int> >::iterator m_cur; // +0x4C
	_STL::list<int, _STL::allocator<int> > m_list; // +0x50
};

// GameLogicInit.cpp's view of the retail 0x00BEE130 slots, so this unit's copy
// of the GameLogic vtable is the one the constructor's unit emits. The
// canonical header declares only the destructor, so adopting it here emits a
// one-slot ??_7GameLogic@@6BSubsystemInterface@@@ that loses to the
// constructor's 13-slot copy; keep the same 13 virtuals instead.
class SubsystemInterface
{
public:
	SubsystemInterface(void);
	virtual ~SubsystemInterface(void);
	virtual void init(void) = 0;
	virtual bool loadIniFilesFromLegend();
	virtual void postProcessLoad();
	virtual bool vslot04(int);
	virtual bool vslot05();
	virtual int vslot06();
	virtual void vslot07(int);
	virtual void vslot08();
	virtual void reset(void);
	virtual void update(void) {}

private:
	int m_04;
	AsciiString m_name;
};


class Rva00242E71 { public: ~Rva00242E71(); private: unsigned char m_data[0x14]; };
struct Rva00243B48 { ~Rva00243B48() {} Rva00242E71 m_table; };

class Rva00240CAB { public: ~Rva00240CAB(); private: unsigned char m_data[0x2C]; };
struct Rva00243B4D { ~Rva00243B4D() {} Rva00240CAB m_member; };

struct Rva00200667 { ~Rva00200667() {} _STL::list<Rva004FA1FObserver *> m_list; };

#include "../../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"

struct Rva0010F149Handle
{
	~Rva0010F149Handle() { if (m_ptr) m_ptr->Release_Ref(); }
	OpaqueRefCounted *m_ptr;
};

class Rva00240C27 { public: ~Rva00240C27(); private: unsigned char m_data[0x14]; };
struct Rva00240E13 { ~Rva00240E13() {} Rva00240C27 m_table; };

struct Gen_uw_0007fab3
{
	~Gen_uw_0007fab3() { if (m_begin) Rva00030830GameFree(m_begin); }
	void *m_begin;
	void *m_end;
	void *m_capacity;
};

#include "../../../Include/Common/Rva001EB769.h"
struct Rva001EB940
{
	~Rva001EB940() { ((Rva001EB769 *)this)->rva001EB769(); }
	unsigned char m_data[0x5C];
};

class Object;
// The +0x164 Object pointer vector: the body inlines its free, and the unwind
// funclet calls the out-of-line vector<Object *> destructor (ILT stub
// 0x001F22A3, folded with _Vector_base's rowed 0x001F1609).
namespace _STL {
template <> __forceinline _Vector_base<Object *, allocator<Object *> >::~_Vector_base()
{
	if (_M_start != 0)
		Rva00030830GameFree(_M_start);
}
template <> __forceinline vector<Object *, allocator<Object *> >::~vector()
{
	_Destroy(this->_M_start, this->_M_finish);
}
}

class Rva0040DB52
{
public:
	virtual ~Rva0040DB52();
private:
	unsigned char m_pad04[0x3C - 4];
};

struct Rva00207F08Dtor
{
	~Rva00207F08Dtor() {}
	_STL::list<AsciiString> m_list;
};

class Rva0023DC86StringField
{
public:
	~Rva0023DC86StringField();
private:
	char m_pad[0x18];
	AsciiString m_str;
};

class GameLogic : public SubsystemInterface, public Snapshot
{
public:
	virtual ~GameLogic(void);
	virtual void init(void);
	virtual bool v11(int) { return false; }
	virtual void v12(void) {}
	virtual void update(int phase);
	virtual TerrainLogic *createTerrainLogic(void) = 0;
	virtual GhostObjectManager *createGhostObjectManager(void) = 0;
	virtual BuffLogic *createBuffLogic(void) = 0;
	virtual void reset(void);
	void destroyAllObjectsImmediate();
	void rva00376D49();
protected:
	virtual void crc(Xfer *xfer) = 0;
	virtual void xfer(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
private:
	Rva00243B48 m_10;
	Rva00243B4D m_24;
	Rva00200667 m_50;
	AsciiString m_54;
	_STL::vector<AsciiString> m_58;
	AsciiString m_64;
	AsciiString m_68;
	int m_6C;
	int m_70;
	AsciiString m_74;
	int m_78;
	AsciiString m_7C;
	AsciiString m_80;
	AsciiString m_84;
	Rva0010F149Handle m_88;
	Rva0010F149Handle m_8C;
	unsigned char m_pad90[0xB4 - 0x90];
	Rva00240E13 m_B4;
	Gen_uw_0007fab3 m_C8[4];
	Gen_uw_0007fab3 m_F8;
	int m_104;
	Rva001EB940 m_108;
	_STL::vector<Object *> m_164;
	Rva00243BA0Owned *m_170;
	Rva00243BA0Owned *m_174;
	Rva00243BA0Owned *m_178;
	int m_17C;
	int m_180;
	Rva0040DB52 m_184;
	Rva00207F08Dtor m_1C0;
	Rva0023DC86StringField m_1C4[8];
};

GameLogic::~GameLogic()
{
	Rva0004224C guard;
	m_1C0.m_list.clear();
	destroyAllObjectsImmediate();

	::delete (Rva00243BA0Owned *)TheTerrainLogic;
	TheTerrainLogic = 0;
	::delete (Rva00243BA0Owned *)TheGhostObjectManager;
	TheGhostObjectManager = 0;
	::delete (Rva00243BA0Owned *)ThePartitionManager;
	ThePartitionManager = 0;
	::delete (Rva00243BA0Owned *)TheShroudManager;
	TheShroudManager = 0;
	::delete (Rva00243BA0Owned *)TheCollisionManager;
	TheCollisionManager = 0;

	::delete m_170;
	m_170 = 0;
	::delete m_174;
	m_174 = 0;
	::delete m_178;
	m_178 = 0;

	::delete (Rva00243BA0Owned *)TheScriptActions;
	TheScriptActions = 0;
	::delete (Rva00243BA0Owned *)TheScriptConditions;
	TheScriptConditions = 0;
	::delete (Rva00243BA0Owned *)TheLargeGroupAudio;
	TheLargeGroupAudio = 0;
	::delete (Rva00243BA0Owned *)TheBuffLogic;
	TheBuffLogic = 0;

	((Rva0023E7D9 *)this)->rva0023E7D9();
	rva00376D49();
	TheGameLogic = 0;
}
