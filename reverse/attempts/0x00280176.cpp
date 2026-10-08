// ?rva00280176@TerrainLogic@@QAEXPBVThingTemplate@@PBUCoord3D@@PBVMatrix3D@@M@Z
// partial score=0.99 date=2026-10-08
// Banked 2026-10-08 at session wind-down. Scratch flags: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB (stlport).
// 0x00280176 (shrub placement) compiles byte-exact here; 0x00283642 (tree placement) is exact except the
// m_records push_back REL32, which resolves once landed in TerrainLogicXfer.cpp through its FoldedAppendVector view.
// Caller: GameLogic 0x00246422 with ecx = TheTerrainLogic, args (tmpl, &pos, &identity Matrix3D, 1.0f).
// Levers: TreeLocation by-value arg with user ctor AND dtor (gives mov [ebp+X],esp); record ctor declared throw()
// (no EH frame); TerrainLogic view needs a virtual dtor (+4); nested ifs not a ternary; break + if(!md) in shrub.
// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include "ascii_string.h"
#include "Lib/Coord3D.h"

#include <vector>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef float Real;

#define NULL 0

enum DrawableID
{
	INVALID_DRAWABLE_ID = 0
};

class Matrix3D;
class W3DTreeDrawModuleData;

class ModuleData
{
public:
	virtual void slot00() const; virtual void slot01() const; virtual void slot02() const;
	virtual void slot03() const; virtual void slot04() const; virtual void slot05() const;
	virtual void slot06() const; virtual void slot07() const; virtual void slot08() const;
	virtual void slot09() const; virtual void slot10() const; virtual void slot11() const;
	virtual void slot12() const; virtual void slot13() const; virtual void slot14() const;
	virtual void slot15() const;
	virtual const W3DTreeDrawModuleData *getAsW3DTreeDrawModuleData() const; // +0x40
};

class ModuleInfo
{
public:
	Int getCount() const { return (Int)(m_info.end - m_info.begin); }
	const ModuleData *getNthData(Int i) const;
private:
	struct Nugget
	{
		char m_data[0x14];
	};
	struct
	{
		Nugget *begin;
		Nugget *end;
		Nugget *capacity;
	} m_info;
};

class ThingTemplate
{
public:
	const ModuleInfo &getDrawModuleInfo() const { return m_drawModuleInfo; }
	const AsciiString &getName() const { return m_name; }
	UnsignedShort getShadowType() const { return m_shadowType; }
	Int get5B8() const { return m_5B8; }
	unsigned char get5EB() const { return m_5EB; }
	unsigned char get5EC() const { return m_5EC; }
	const AsciiString &getShadowTextureName() const { return m_shadowTextureName; }
private:
	char m_pad00[0x64];
	AsciiString m_name; // +0x64
	char m_pad68[0x90 - 0x68];
	AsciiString m_shadowTextureName; // +0x90
	char m_pad94[0x2F0 - 0x94];
	ModuleInfo m_drawModuleInfo; // +0x2F0
	char m_pad2FC[0x5B8 - 0x2FC];
	Int m_5B8; // +0x5B8
	char m_pad5BC[0x5E2 - 0x5BC];
	UnsignedShort m_shadowType; // +0x5E2
	char m_pad5E4[0x5EB - 0x5E4];
	unsigned char m_5EB; // +0x5EB
	unsigned char m_5EC; // +0x5EC
};

// GameClient::allocDrawableID, named for its address.
class Rva00238E1B
{
public:
	Int rva00238E1B();
};
class GameClient;
extern GameClient *TheGameClient;

// W3DTerrainVisual::addTree's by-value location: retail builds the argument
// through a copy constructor and keeps its address.
struct TreeLocation
{
	TreeLocation(const Coord3D &that) : x(that.x), y(that.y), z(that.z) {}
	~TreeLocation() {}
	Real x, y, z;
};

class G00DFF080Obj
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20();
	virtual void addTree(DrawableID id, TreeLocation location, Real scale, const Matrix3D *mtx,
		Real randomScaleAmount, const W3DTreeDrawModuleData *data, Int shadowType,
		const AsciiString *shadowTextureName, const AsciiString *name); // +0x54
	virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25();
	virtual void addShrub(DrawableID id, TreeLocation location, Real scale, const Matrix3D *mtx,
		Real randomScaleAmount, const W3DTreeDrawModuleData *data, Int shadowType,
		const AsciiString *shadowTextureName, const AsciiString *name); // +0x68
};
extern G00DFF080Obj *g_00DFF080;

class DebugReport
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
	virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1C();
	virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2C();
	virtual void s30(); virtual void s34();
	virtual DebugReport *setText(const char *text); // +0x38
	virtual void s3C(); virtual void s40(); virtual void s44(); virtual void s48();
	virtual void show(int mode); // +0x4C
};

class Debug
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
	virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1C();
	virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2C();
	virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3C();
	virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4C();
	virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5C();
	virtual void beginReport(); // +0x60
	virtual void s64(); virtual void s68();
	virtual DebugReport *getReport(int, int, int); // +0x6C
};
extern Debug *theDebug;
bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int kind);

class Rva0027D02F
{
public:
	Rva0027D02F(const unsigned int *words, int a, int b, int c,
		unsigned short tag, int d, unsigned char e, unsigned char f) throw();
private:
	char m_data[0x30];
};

class Rva002834E6Owner
{
public:
	void rva002834E6(void *p);
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
private:
	char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};
extern GameLogic *TheGameLogic;

class GlobalData
{
public:
	char m_pad00[0xA60];
	Int m_A60; // +0xA60
};
extern GlobalData *TheWritableGlobalData;

class FireLogicSystem
{
public:
	void rva00286373(Int drawableID, const Coord3D *pos, const ThingTemplate *tmpl);
};
class Rva002872BA;
extern Rva002872BA *TheTriggerManager;
inline FireLogicSystem *TheFireLogicSystem() { return (FireLogicSystem *)TheTriggerManager; }

class TerrainLogic
{
public:
	virtual ~TerrainLogic();
	void rva00280176(const ThingTemplate *tmpl, const Coord3D *pos, const Matrix3D *mtx, Real scale);
	void rva00283642(const ThingTemplate *tmpl, const Coord3D *pos, const Matrix3D *mtx, Real scale);
	Int getPartitionBucket(float *src);
private:
	char m_pad04[0x48 - 0x04];
	UnsignedInt m_field48; // +0x48
	char m_pad4C[0x578 - 0x4C];
	_STL::vector<Rva0027D02F *> m_records; // +0x578
	Rva002834E6Owner *m_584; // +0x584
	short m_words[2500]; // +0x588
	UnsignedInt m_field1910; // +0x1910
};

// ?rva00280176@TerrainLogic@@QAEXPBVThingTemplate@@PBUCoord3D@@PBVMatrix3D@@M@Z @0x00280176
void TerrainLogic::rva00280176(const ThingTemplate *tmpl, const Coord3D *pos, const Matrix3D *mtx, Real scale)
{
	const ModuleInfo &mi = tmpl->getDrawModuleInfo();
	const W3DTreeDrawModuleData *md = NULL;
	for (Int i = 0; i < mi.getCount(); ++i)
	{
		const ModuleData *mdd = mi.getNthData(0);
		md = mdd ? mdd->getAsW3DTreeDrawModuleData() : NULL;
		if (md)
			break;
	}
	if (!md)
	{
		if (bfmeRva000387C0())
		{
		_bfme_debugRecordCallsite(1);
		theDebug->beginReport();
		theDebug->getReport(0, 0, 0)->setText("Shrub ")->setText(tmpl->getName().str())
			->setText(" requires a W3DTreeDrawModule.\n")->show(2);
		}
		return;
	}
	DrawableID id = (DrawableID)((Rva00238E1B *)TheGameClient)->rva00238E1B();
	Int shadowType = tmpl->getShadowType();
	g_00DFF080->addShrub(id, *pos, scale, mtx, 0.0f, md, shadowType,
		&tmpl->getShadowTextureName(), &tmpl->getName());
}

// ?rva00283642@TerrainLogic@@QAEXPBVThingTemplate@@PBUCoord3D@@PBVMatrix3D@@M@Z @0x00283642
void TerrainLogic::rva00283642(const ThingTemplate *tmpl, const Coord3D *pos, const Matrix3D *mtx, Real scale)
{
	m_field1910 = TheGameLogic->getFrame();
	const ModuleInfo &mi = tmpl->getDrawModuleInfo();
	const W3DTreeDrawModuleData *md = NULL;
	for (Int i = 0; i < mi.getCount(); ++i)
	{
		const ModuleData *mdd = mi.getNthData(0);
		if (mdd)
		{
			const W3DTreeDrawModuleData *data = mdd->getAsW3DTreeDrawModuleData();
			if (data)
				md = data;
		}
	}
	if (!md)
	{
		if (bfmeRva000387C0())
		{
			_bfme_debugRecordCallsite(1);
			theDebug->beginReport();
			theDebug->getReport(0, 0, 0)->setText("Tree ")->setText(tmpl->getName().str())
				->setText(" requires a W3DTreeDrawModule.\n")->show(2);
		}
		return;
	}
	DrawableID id = (DrawableID)((Rva00238E1B *)TheGameClient)->rva00238E1B();
	short *bucket = &m_words[(short)getPartitionBucket((float *)pos)];
	short next = *bucket;
	*bucket = (short)m_records.size();
	Int v = TheWritableGlobalData->m_A60;
	if (tmpl->get5B8() > 0)
		v = tmpl->get5B8();
	Rva0027D02F *rec = new Rva0027D02F((const unsigned int *)pos, id, m_field48++, (int)tmpl, next, v,
		tmpl->get5EB(), tmpl->get5EC());
	m_records.push_back(rec);
	m_584->rva002834E6(rec);
	Int shadowType = tmpl->getShadowType();
	g_00DFF080->addTree(id, *pos, scale, mtx, 0.0f, md, shadowType,
		&tmpl->getShadowTextureName(), &tmpl->getName());
	if (TheFireLogicSystem())
		TheFireLogicSystem()->rva00286373(id, pos, tmpl);
}
