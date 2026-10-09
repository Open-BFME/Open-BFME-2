// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /ICode/Libraries/Include/Lib
// stlport
// ??0Drawable@@QAE@PBVThingTemplate@@W4DrawableStatus@@H@Z retail 0x002797BD 2111 bytes RET 0xC.
//
// Drawable::Drawable (WorldBuilder twin 0x00C9F5C0 in Drawable.cpp; Zero
// Hour's Drawable::Drawable donor). Sole caller 0x0004C75F allocates 0x470
// bytes and passes three arguments: the template, the status bits (stored at
// +0x114) and a third value stored at +0x364. Target evidence: the rowed
// Thing::Thing 0x0030A188 base, the Snapshot base at +0x60 (vftable
// 0x00BBB554 then the Drawable pair 0x00BFB0B4/0x00BFB0A4), and the retail
// FuncInfo 0x00D1A580 unwind map whose 14 states name each destructible
// member: two release handles at +0x10C/+0x110 (dtor 0x0010F149), the
// interface vector at +0x158 and a second vector at +0x36C (ctor 0x00211E58,
// dtor 0x0007FAB3), AsciiStrings at +0x348/+0x34C/+0x458, three 8-byte
// release slots at +0x38C through the eh vector iterator (ctor 0x0007E81F,
// dtor 0x0010F149) and the 0x90-byte Rva002701F4 member at +0x3AC; states
// 11-13 are the getNthName temporaries of the three module loops. Matrix3D
// members at +0x170/+0x1A0/+0x1D0/+0x208 use the Vector4 iterator 0x00001423;
// the three condition-state members at +0x258/+0x2A4/+0x2F0 use the rowed
// Rva0042526Member ctor. Offsets named by matched Drawable units:
// +0xFC object, +0x14C module lists, +0x170/+0x1A0 instance matrices,
// +0x204 expiration, +0x378 frame, +0x43F identity flag, +0x443 dirty flag,
// +0x454 indicator color. The body follows the donor: identity matrices,
// drawable info (+0x248) bound to this, tint color from 0xFFFFFFFF via the
// rowed RGBColor::setFromInt, asset scale from template +0x4E0, register with
// TheGameClient (slot 15), then draw / client-update / third module lists from
// template +0x2F0/+0x2FC/+0x308 (types 1/2/3) with the draw-module LOD filter
// (TheWritableGlobalData +0x24 against TheGameLODManager +0x1774, default 3).
// BFME2 additions: each new module's slot-10 interface is appended to the
// +0x158 vector and a draw module failing its data's slot-30 query sets
// +0x3AB. Then onObjectCreated on every module, the rowed static-image init
// 0x00274E7D, the rowed ambient-sound start 0x002783F6(0) unless the map or
// a save game is loading, and the two +0x348/+0x34C strings are cleared.
// The donor's template null test after registration folds away (the
// template is dereferenced first). The real STLport vector is required: its
// allocator temporaries take the dead template slot [ebp+0xB] as retail does.
// Member names past the cited offsets are placeholders.

#include <vector>
#include "ascii_string.h"
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#include "Common/Snapshot.h"
#include "Coord3D.h"
#include "../Common/GameLogicObjectLookupView.h"

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

class Module
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04();
	virtual void onObjectCreated();				// +0x14
	virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
	virtual const ModuleData *rva28();			// +0x28
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
};
extern GameClient *TheGameClient;

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

class RGBColor
{
public:
	void setFromInt(int c);
	float red, green, blue;
};

class Rva0010F149Handle
{
public:
	Rva0010F149Handle() : m_p(0) {}
	~Rva0010F149Handle();
	void *m_p;
};

// Rowed release worker 0x00050ED3 (the tail jump of retail's 0x0010F149).
class OpaqueRefCounted
{
public:
	void Release_Ref();
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

class Rva0042526Member { public: Rva0042526Member(); unsigned char m_data[0x4C]; };
class Rva002701F4 { public: Rva002701F4(); ~Rva002701F4(); unsigned char m_data[0x90]; };

struct DrawableInfo
{
	DrawableInfo() : m_shroudStatusObjectID(0), m_drawable(0), m_ghostObject(0), m_flags(0) {}
	int m_shroudStatusObjectID;
	Drawable *m_drawable;
	void *m_ghostObject;
	int m_flags;
};

class Thing
{
public:
	Thing(const ThingTemplate *thingTemplate);
	virtual ~Thing();
	const ThingTemplate *m_template;			// +0x04
	unsigned char m_pad08[0x58];
};

class Drawable : public Thing, public Snapshot
{
public:
	Drawable(const ThingTemplate *thingTemplate, DrawableStatus statusBits, int arg);
	__forceinline void addIface(const ModuleData *iface) { if (iface) m_158.push_back(iface); }
	virtual ~Drawable();
	virtual void LoadPostProcess();
	virtual void GetSnapshotName();
	virtual void DoXfer(Xfer *xfer);

	int m_64;						// +0x64
	int m_68;						// +0x68
	RGBColor m_tintColor;					// +0x6C
	int m_78;						// +0x78
	int m_7c;						// +0x7C
	int m_80;						// +0x80
	float m_84;						// +0x84
	float m_88;						// +0x88
	int m_8c;						// +0x8C
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
	int m_118, m_11c, m_120, m_124, m_128, m_12c, m_130, m_134, m_138, m_13c;	// +0x118
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
	int m_340;						// +0x340
	int m_344;						// +0x344
	AsciiString m_348;					// +0x348
	AsciiString m_34c;					// +0x34C
	int m_350;						// +0x350
	int m_354;						// +0x354
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
	int m_450;						// +0x450
	int m_indicatorColor;					// +0x454
	AsciiString m_458;					// +0x458
	int m_45c;						// +0x45C
	unsigned char m_pad460[0x470 - 0x460];
};

Drawable::Drawable(const ThingTemplate *thingTemplate, DrawableStatus statusBits, int arg) :
	Thing(thingTemplate),
	m_64(0),
	m_68(0),
	m_78(0),
	m_7c(0),
	m_80(0),
	m_84(0.0f),
	m_88(0.0f),
	m_8c(0),
	m_a8(7),
	m_ac(1.0f), m_b0(1.0f), m_b4(1.0f), m_b8(1.0f), m_bc(1.0f), m_c0(1.0f), m_c4(1.0f),
	m_c8(0.0f),
	m_cc(1.0f),
	m_d0(0.0f),
	m_d4(10),
	m_d8(0.0f),
	m_dc(0.0f),
	m_e0(0.0f),
	m_e4(false),
	m_f0(0),
	m_f4(1.0f),
	m_f8(0.03f),
	m_object(0),
	m_100(0),
	m_104(0),
	m_108(0),
	m_status(statusBits),
	m_118(0), m_11c(0), m_120(0), m_124(0), m_128(0), m_12c(0), m_130(0), m_134(0), m_138(0), m_13c(0),
	m_140(0.0f),
	m_144(1),
	m_148(1),
	m_164(0),
	m_168(0),
	m_16c(0),
	m_expirationDate(-1),
	m_244(-1),
	m_33c(-1.0f),
	m_340(0),
	m_344(0),
	m_350(0),
	m_354(0),
	m_358(0.0f),
	m_35c(0),
	m_360(0),
	m_368(0),
	m_frame(-1),
	m_37c(0),
	m_380(0),
	m_384(0),
	m_388(TheGameLogic->getFrame() + (thingTemplate == 0 ? 0 : thingTemplate->getX594())),
	m_3a4(0),
	m_3a8(false),
	m_3a9(false),
	m_3aa(false),
	m_3ab(false),
	m_43c(false),
	m_43d(false),
	m_43e(false),
	m_instanceIsIdentity(true),
	m_440(false),
	m_442(true),
	m_isModelDirty(true),
	m_444(false),
	m_445(false),
	m_446(false),
	m_447(true),
	m_448(true),
	m_449(true),
	m_44a(true),
	m_44b(true),
	m_44c(0),
	m_450(0),
	m_45c(0)
{
	int i;
	for (i = 0; i < 3; ++i)
		m_modules[i] = 0;

	m_instance.Make_Identity();
	m_208.Make_Identity();
	Coord3DZero::zero(m_238);
	m_previousInstance.Make_Identity();

	m_drawableInfo.m_shroudStatusObjectID = 0;
	m_drawableInfo.m_drawable = this;
	m_drawableInfo.m_ghostObject = 0;
	m_drawableInfo.m_flags = 0;

	DrawableICoord2D size;
	size.x = 0x60;
	size.y = 0x60;
	m_e8 = size;

	m_tintColor.setFromInt(-1);
	Coord3DZero::zero(m_90);
	Coord3DZero::zero(m_9c);

	m_instanceScale = thingTemplate->getAssetScale();
	m_364 = arg;

	TheGameClient->registerDrawable(this);

	if (TheGameClient == 0 || thingTemplate == 0)
		return;

	int lodLevel = 3;
	if (TheGameLODManager)
		lodLevel = TheGameLODManager->m_staticLODLevel;

	int modIdx;
	Module **m;

	const ModuleInfo &drawMI = thingTemplate->m_drawModuleInfo;
	m = m_modules[0] = new Module *[drawMI.getCount() + 1];
	for (modIdx = 0; modIdx < drawMI.getCount(); ++modIdx)
	{
		const ModuleData *newModData = drawMI.getNthData(modIdx);
		if (TheWritableGlobalData->m_useDrawModuleLOD && newModData->getMinimumRequiredGameLOD() > lodLevel)
			continue;
		*m = TheModuleFactory->newModule(this, drawMI.getNthName(modIdx), newModData, MODULETYPE_DRAW);
		addIface((*m)->rva28());
		if (!newModData->rva78())
			m_3ab = true;
		++m;
	}
	*m = 0;

	const ModuleInfo &cuMI = thingTemplate->m_clientUpdateModuleInfo;
	if (cuMI.getCount())
	{
		m = m_modules[1] = new Module *[cuMI.getCount() + 1];
		for (modIdx = 0; modIdx < cuMI.getCount(); ++modIdx)
		{
			const ModuleData *newModData = cuMI.getNthData(modIdx);
			*m = TheModuleFactory->newModule(this, cuMI.getNthName(modIdx), newModData, MODULETYPE_CLIENT_UPDATE);
			addIface((*m)->rva28());
			++m;
		}
		*m = 0;
	}

	const ModuleInfo &mi3 = thingTemplate->m_moduleInfo308;
	if (mi3.getCount())
	{
		m = m_modules[2] = new Module *[mi3.getCount() + 1];
		for (modIdx = 0; modIdx < mi3.getCount(); ++modIdx)
		{
			const ModuleData *newModData = mi3.getNthData(modIdx);
			*m = TheModuleFactory->newModule(this, mi3.getNthName(modIdx), newModData, MODULETYPE_3);
			addIface((*m)->rva28());
			++m;
		}
		*m = 0;
	}

	for (i = 0; i < 3; ++i)
	{
		for (Module **mm = m_modules[i]; mm && *mm; ++mm)
			(*mm)->onObjectCreated();
	}

	Rva00274E7DInit();

	if (TheGameLogic && !TheGameLogic->m_6d && TheGameState && !TheGameState->m_isInLoadGame)
		((Rva002783F6Host *)this)->rva002783F6(0);

	m_indicatorColor = 0;
	m_348.clear();
	m_34c.clear();
}
