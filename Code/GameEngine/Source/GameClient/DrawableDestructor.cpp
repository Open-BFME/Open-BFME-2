// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /ICode/Libraries/Include/Lib
// stlport
// ??1Drawable@@UAE@XZ, retail 0x002793F0..0x00279669 (633 bytes, EH).
//
// Drawable::~Drawable (Zero Hour's Drawable::~Drawable donor; the scalar
// deleting destructor 0x00279FFC reaches it through the opaque pin
// ??1Rva002793F0). It frees the two display strings, empties the interface
// vector, deletes every module of the three module lists in Zero Hour's
// `m && *m` loop and frees the lists, then runs the rowed 0x002743D7,
// 0x002714CA and 0x00279354(false), leaves TheGameClient (slot 19), clears
// the object and deletes its seven owned objects. Retail's unwind map
// (FuncInfo 0x00D1A4F4) then destroys the +0x458 string, the +0x3AC member,
// the three +0x38C release slots, the +0x36C vector, the +0x34C/+0x348
// strings, the +0x158 vector, the +0x110/+0x10C release handles (inline;
// unwind copy 0x0010F149), Snapshot at +0x60 and Thing (rowed 0x0030A120).
// Layout from the banked constructor work (Drawable::Drawable is landed in
// DrawableConstructor.cpp); member names past the cited offsets are
// placeholders.

#include <vector>
#include <new>
#include "ascii_string.h"
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#include "Common/Snapshot.h"
#include "Coord3D.h"
#include "../Common/GameLogicObjectLookupView.h"

class ModuleData;
void __cdecl Rva00030830GameFree(void *);
namespace _STL {
// Inlined into every caller here; the census keeps ModuleFactory.cpp's copy, so this unit emits none.
template<> __declspec(dllimport) __declspec(nothrow) __forceinline _Vector_base<const ModuleData *, allocator<const ModuleData *> >::~_Vector_base() { if (_M_start) Rva00030830GameFree(_M_start); }
}

class Thing;
class Object;
class Module;
class ModuleData;
class Matrix3D;
enum DrawableStatus { DRAWABLE_STATUS_NONE = 0 };
enum ModuleType { MODULETYPE_DRAW = 1, MODULETYPE_CLIENT_UPDATE = 2, MODULETYPE_3 = 3 };

class BFMERetailAsciiString : public AsciiString
{
};

struct ModuleInfoEntry { unsigned char m_data[0x14]; };
class ModuleInfo
{
public:
	int getCount() const { return m_end - m_begin; }
	BFMERetailAsciiString getNthName(int i) const;
	const ModuleData *getNthData(int i) const;
	ModuleInfoEntry *m_begin;
	ModuleInfoEntry *m_end;
	ModuleInfoEntry *m_capacity;
};

class ThingTemplate
{
public:
	virtual ~ThingTemplate();
	unsigned char m_pad004[0x2F0 - 0x4];
	ModuleInfo m_drawModuleInfo;			// +0x2F0
	ModuleInfo m_clientUpdateModuleInfo;		// +0x2FC
	ModuleInfo m_moduleInfo308;			// +0x308
	unsigned char m_pad314[0x4E0 - 0x314];
	float m_assetScale;				// +0x4E0
	float getAssetScale() const { return m_assetScale; }
	unsigned char m_pad4E4[0x594 - 0x4E4];
	int m_594;					// +0x594
	int getX594() const { return m_594; }
};

class ModuleData
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21();
	virtual int getMinimumRequiredGameLOD() const;		// +0x58
	virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
	virtual void s27(); virtual void s28(); virtual void s29();
	virtual bool rva78() const;				// +0x78
};

class Xfer;
enum NameKeyType { NAMEKEY_INVALID = 0 };

// Retail slot order (docs/linking_obstacles.md, "Module base chain"):
// Snapshot's three slots, then getModuleNameKey and the four empty hooks.
class Module
{
public:
	virtual void *deleteInstance(int arg);
	virtual void loadPostProcess() = 0;
	virtual const char *GetSnapshotName() const = 0;
	virtual void xfer(Xfer *xfer) = 0;
	virtual NameKeyType getModuleNameKey() const = 0;
	virtual void onObjectCreated() {}
	virtual void onDrawableBoundToObject() {}
	virtual void preloadAssets() {}
	virtual void onDelete() {}
};

class ModuleFactory
{
public:
	Module *newModule(Thing *thing, const AsciiString &name, const ModuleData *data, ModuleType type);
};
extern ModuleFactory *TheModuleFactory;

class Drawable;
class GameClient
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
	virtual void registerDrawable(Drawable *draw);		// +0x3C
	virtual void s16(); virtual void s17(); virtual void s18();
	virtual void removeFromRayEffects(Drawable *draw);	// +0x4C
};
extern GameClient *TheGameClient;

class DisplayStringManager
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13();
	virtual void *newDisplayString();			// +0x38
	virtual void freeDisplayString(void *string);	// +0x3C
};
extern DisplayStringManager *TheDisplayStringManager;

class GameLODManager
{
public:
	unsigned char m_pad[0x1774];
	int m_staticLODLevel;					// +0x1774
};
extern GameLODManager *TheGameLODManager;

class GlobalData
{
public:
	unsigned char m_pad[0x24];
	bool m_useDrawModuleLOD;				// +0x24
};
extern GlobalData *TheWritableGlobalData;

extern GameLogic *TheGameLogic;

class GameState
{
public:
	unsigned char m_pad[0xE18];
	bool m_isInLoadGame;					// +0xE18
};
extern GameState *TheGameState;

void Rva00274E7DInit();

class Rva002783F6Host
{
public:
	void rva002783F6(int v);
};

class Vector4 { public: __forceinline Vector4() {} __forceinline void Set(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; } float X, Y, Z, W; };
class Matrix3D
{
public:
	__forceinline Matrix3D() {}
	__forceinline void Make_Identity()
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
	}
	Vector4 Row[3];
};

struct Coord3DZero
{
	static void zero(Coord3D &c) { c.x = 0.0f; c.y = 0.0f; c.z = 0.0f; }
};

struct DrawableICoord2D { int x, y; };

#include "../../../Libraries/Include/Lib/RGBColor.h"

// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * * vector<void *,allocator<void *> >::end() { return this->_M_finish; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * * vector<void *,allocator<void *> >::begin() { return this->_M_start; } }
// Rowed release worker 0x00050ED3 (the tail jump of retail's 0x0010F149).
class OpaqueRefCounted
{
public:
	void Release_Ref();
};

// Release handle; its out-of-line copy (the unwind maps' target) is the rowed
// 0x0010F149, inline in the destructor body.
class Rva0010F149Handle
{
public:
	Rva0010F149Handle() : m_p(0) {}
	~Rva0010F149Handle() { if (m_p) ((OpaqueRefCounted *)m_p)->Release_Ref(); }
	void *m_p;
};

// The three 8-byte slots at +0x38C. The eh vector iterator takes the
// addresses of these members, so cl emits them as COMDATs: the zeroing
// ctor is retail's 10-byte 0x0007E81F and the releasing dtor retail's
// 12-byte 0x0010F149 (both ICF-folded with other owners).
class DrawableRefSlot
{
public:
	DrawableRefSlot() : m_p(0), m_v(0) {}
	~DrawableRefSlot()
	{
		if (m_p)
			m_p->Release_Ref();
	}
	OpaqueRefCounted *m_p;
	int m_v;
};

class DrawableDisposable
{
public:
	virtual void *deleteInstance(int arg);
};

class Rva0042526Member { public: Rva0042526Member(); unsigned char m_data[0x4C]; };
class BfmeThingDSF
{
public:
	void bfmeGoDSF();
	char m_bfmeHead[0x60];
};
class Rva002701F4
{
public:
	Rva002701F4();
	__forceinline ~Rva002701F4() { ((BfmeThingDSF *)this)->bfmeGoDSF(); }
	unsigned char m_data[0x90];
};

struct DrawableInfo
{
	DrawableInfo() : m_shroudStatusObjectID(0), m_drawable(0), m_ghostObject(0), m_flags(0) {}
	int m_shroudStatusObjectID;
	Drawable *m_drawable;
	void *m_ghostObject;
	int m_flags;
};

// Thing: its constructor is the rowed Thing::Thing 0x0030A188 and its
// destructor the rowed Thing::~Thing 0x0030A120 (same vtable 0x008086E0 and instance count).
class Thing
{
protected:
	virtual ~Thing();	// protected as in Zero Hour's MEMORY_POOL_GLUE_ABC(Thing)
public:
	const ThingTemplate *m_template;			// +0x04
	unsigned char m_pad08[0x58];
};

class Drawable : public Thing, public Snapshot
{
public:
	Drawable(const ThingTemplate *thingTemplate, DrawableStatus statusBits, int arg);
	__forceinline void addIface(const ModuleData *iface) { if (iface) m_158.push_back(iface); }
	virtual ~Drawable();
	void stopAmbientSound();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void DoXfer(Xfer *xfer);

	DrawableDisposable *m_64;					// +0x64; deleted through virtual slot 0
	DrawableDisposable *m_68;					// +0x68; deleted through virtual slot 0
	RGBColor m_tintColor;					// +0x6C
	int m_78;						// +0x78
	int m_7c;						// +0x7C
	int m_80;						// +0x80
	float m_84;						// +0x84
	float m_88;						// +0x88
	DrawableDisposable *m_8c;					// +0x8C; deleted through virtual slot 0
	Coord3D m_90;						// +0x90
	Coord3D m_9c;						// +0x9C
	int m_a8;						// +0xA8
	float m_ac, m_b0, m_b4, m_b8, m_bc, m_c0, m_c4;		// +0xAC
	float m_c8;						// +0xC8
	float m_cc;						// +0xCC
	float m_d0;						// +0xD0
	int m_d4;						// +0xD4
	float m_d8;						// +0xD8
	float m_dc;						// +0xDC
	float m_e0;						// +0xE0
	bool m_e4;						// +0xE4
	DrawableICoord2D m_e8;					// +0xE8
	int m_f0;						// +0xF0
	float m_f4;						// +0xF4
	float m_f8;						// +0xF8
	Object *m_object;					// +0xFC
	int m_100;						// +0x100
	int m_104;						// +0x104
	int m_108;						// +0x108
	Rva0010F149Handle m_10c;				// +0x10C
	Rva0010F149Handle m_110;				// +0x110
	DrawableStatus m_status;				// +0x114
	int m_118, m_11c, m_120, m_124, m_128, m_12c, m_130, m_134, m_138;	// +0x118
	DrawableDisposable *m_13c;				// +0x13C; deleted through virtual slot 0
	float m_140;						// +0x140
	int m_144;						// +0x144
	int m_148;						// +0x148
	Module **m_modules[3];					// +0x14C
	_STL::vector<const ModuleData *> m_158;			// +0x158
	int m_164;						// +0x164
	int m_168;						// +0x168
	int m_16c;						// +0x16C
	Matrix3D m_previousInstance;				// +0x170
	Matrix3D m_instance;					// +0x1A0
	Matrix3D m_1d0;						// +0x1D0
	float m_instanceScale;					// +0x200
	int m_expirationDate;					// +0x204
	Matrix3D m_208;						// +0x208
	Coord3D m_238;						// +0x238
	int m_244;						// +0x244
	DrawableInfo m_drawableInfo;				// +0x248
	Rva0042526Member m_conditionState;			// +0x258
	Rva0042526Member m_pendingClear;			// +0x2A4
	Rva0042526Member m_pendingSet;				// +0x2F0
	float m_33c;						// +0x33C
	void *m_340;						// +0x340; DisplayStringManager-owned
	void *m_344;						// +0x344; DisplayStringManager-owned
	AsciiString m_348;					// +0x348
	AsciiString m_34c;					// +0x34C
	int m_350;						// +0x350
	DrawableDisposable *m_354;					// +0x354; deleted through virtual slot 0
	float m_358;						// +0x358
	int m_35c;						// +0x35C
	int m_360;						// +0x360
	int m_364;						// +0x364
	int m_368;						// +0x368
	_STL::vector<const ModuleData *> m_36c;			// +0x36C
	int m_frame;						// +0x378
	int m_37c;						// +0x37C
	int m_380;						// +0x380
	int m_384;						// +0x384
	unsigned int m_388;					// +0x388
	DrawableRefSlot m_38c[3];				// +0x38C
	int m_3a4;						// +0x3A4
	bool m_3a8;						// +0x3A8
	bool m_3a9;						// +0x3A9
	bool m_3aa;						// +0x3AA
	bool m_3ab;						// +0x3AB
	Rva002701F4 m_3ac;					// +0x3AC
	bool m_43c;						// +0x43C
	bool m_43d;						// +0x43D
	bool m_43e;						// +0x43E
	bool m_instanceIsIdentity;				// +0x43F
	bool m_440;						// +0x440
	bool m_441;						// +0x441
	bool m_442;						// +0x442
	bool m_isModelDirty;					// +0x443
	bool m_444;						// +0x444
	bool m_445;						// +0x445
	bool m_446;						// +0x446
	bool m_447;						// +0x447
	bool m_448;						// +0x448
	bool m_449;						// +0x449
	bool m_44a;						// +0x44A
	bool m_44b;						// +0x44B
	int m_44c;						// +0x44C
	DrawableDisposable *m_450;					// +0x450; deleted through virtual slot 0
	int m_indicatorColor;					// +0x454
	AsciiString m_458;					// +0x458
	DrawableDisposable *m_45c;					// +0x45C; deleted through virtual slot 0
	unsigned char m_pad460[0x470 - 0x460];
};

class Rva002714CA
{
public:
	void rva002714CA();
};

class Rva00279354Host
{
public:
	void rva00279354(bool value);
};

// Target teardown sequence at 0x002793F0; the Zero Hour destructor supplies
// the same module/display-string lifecycle, while offsets and helpers here
// follow BFME2 retail evidence.
Drawable::~Drawable()
{
	if (m_340)
	{
		TheDisplayStringManager->freeDisplayString(m_340);
		m_340 = 0;
	}

	if (m_344)
	{
		TheDisplayStringManager->freeDisplayString(m_344);
		m_344 = 0;
	}

	_STL::vector<void *> *interfaces = reinterpret_cast<_STL::vector<void *> *>(&m_158);
	interfaces->erase(interfaces->begin(), interfaces->end());

	for (int i = 0; i < 3; ++i)
	{
		for (Module **module = m_modules[i]; module && *module; ++module)
		{
			::operator delete((*module)->deleteInstance(0));
			*module = 0;
		}
		delete[] m_modules[i];
		m_modules[i] = 0;
	}

	stopAmbientSound();
	((Rva002714CA *)this)->rva002714CA();
	((Rva00279354Host *)this)->rva00279354(false);
	TheGameClient->removeFromRayEffects(this);

	m_object = 0;
	::operator delete(m_354 ? m_354->deleteInstance(0) : 0);
	m_354 = 0;
	::operator delete(m_64 ? m_64->deleteInstance(0) : 0);
	m_64 = 0;
	::operator delete(m_68 ? m_68->deleteInstance(0) : 0);
	m_68 = 0;
	::operator delete(m_8c ? m_8c->deleteInstance(0) : 0);
	m_8c = 0;
	::operator delete(m_13c ? m_13c->deleteInstance(0) : 0);
	m_13c = 0;
	::operator delete(m_450 ? m_450->deleteInstance(0) : 0);
	m_450 = 0;
	if (m_45c)
	{
		::operator delete(m_45c->deleteInstance(0));
		m_45c = 0;
	}
}
