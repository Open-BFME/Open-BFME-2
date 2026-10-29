#include "BuffManager.h"
// cl: /I. /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// Drawable::createEmbeddedPortals (0x0027A018) against the Drawable view this
// unit shares with the Drawable::DoXfer recovery; DoXfer itself (0x0027A219)
// is matched in DrawableDoXfer.cpp. The members below sit at their
// Snapshot-relative offsets (Snapshot subobject at full Drawable +0x60).
// Donor: BFME1 Drawable
// (reference/open-bfme-1/game/GameEngine/Source/GameClient/DrawableXfer.cpp).

// Preserve the vector growth comparison inline without emitting a competing
// max<unsigned> copy under this unit's compiler settings.
#include <stl/_algobase.h>
namespace _STL {
template <> __declspec(dllimport) __forceinline
const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
	return a < b ? b : a;
}
}
#include <vector>
#include <string.h>
// /D_CRTIMP= keeps free() direct (0x30830, as the vector<Waypoint *> fold
// needs); retail still calls _strcmpi through its import slot.
extern "C" int (__cdecl * const _imp___strcmpi)(const char *, const char *);

#include "ascii_string.h"
#include "Code/Libraries/Include/Lib/ICoord2D.h"
#include "Code/Libraries/Include/Lib/RGBColor.h"
#include "Code/Libraries/Include/Lib/IRegion2D.h"

class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class Region2D;
class RealRange;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../Include/Common/BfmeXfer.h"

// Retail stores {1, 11} and gates on the second byte.
class Xfer::Version
{
public:
	Version(unsigned char first, unsigned char version)
		: m_first(first), m_version(version) {}

	unsigned char m_first;
	unsigned char m_version;
};

#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#include "reference/shims/moduledata/Common/Snapshot.h"

// Retail constructs the thrown object through bfmeFormatText, the varargs
// constructor, and throws it with __TI1?AVXferException@@.
class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *m_text;
	int m_tag;
};

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);
void XferDrawableID(Xfer *xfer, int *value);
void XferStealthLookType(Xfer *xfer, int *value);
void XferWaypointID(Xfer *xfer, int *value);
Xfer *Rva003062FEXfer(Xfer *xfer, float *vals);
void Rva0030612AXfer(Xfer *xfer, float *vals);

extern const char *TheDrawableIconNames[];

class OpaqueRefCounted
{
public:
	void Release_Ref();
	void *vtable;
	long volatile count;
};

// Counted four-byte owners (target-neutral views; see OpaqueRefOwnership.cpp).
struct OpaqueRefElement4
{
	OpaqueRefCounted *referent;
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &);
};

class Rva000A8C9B
{
public:
	void clear();
	void rva000A8CE5(OpaqueRefCounted *);
	OpaqueRefCounted *m_ptr;
};

class Rva0036CA00Str
{
public:
	Rva0036CA00Str() : item(0) {}
	Rva0036CA00Str(const Rva0036CA00Str &);
	~Rva0036CA00Str() { if (item) item->Release_Ref(); }
	operator const OpaqueRefElement4 &() const { return *reinterpret_cast<const OpaqueRefElement4 *>(this); }
	OpaqueRefCounted *item;
};

Rva0036CA00Str Rva00274DD4();

struct Rva0010F149Handle
{
	Rva0010F149Handle() : referent(0) {}
	Rva0010F149Handle(const Rva0010F149Handle &);
	~Rva0010F149Handle() { if (referent) referent->Release_Ref(); }
	void set(OpaqueRefCounted *opaqueRefCounted) { reinterpret_cast<Rva000A8C9B *>(this)->rva000A8CE5(opaqueRefCounted); }
	OpaqueRefCounted *referent;
};

class Rva001DA2D5;
class Rva004333C0
{
public:
	virtual ~Rva004333C0();
	Rva004333C0(int);
	Rva004333C0(const Rva001DA2D5 &, int);
	char unknown[0xD0 - 4];
};

class DynamicAudioEventInfo
{
public:
	void xferNoName(Xfer *xfer);
};

class Rva000B56F0Object
{
public:
	void *selectStorage();
};

// TheAudio's slots 74, 75 and 88.
class DrawableXferAudioView
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	V(70) V(71) V(72) V(73)
	virtual void addAudioEventInfo(OpaqueRefCounted *info);
	virtual Rva0036CA00Str findAudioEventInfo(const AsciiString &name);
	V(76) V(77) V(78) V(79)
	V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87)
	virtual void xferHandle(Xfer *xfer, int *handle);
#undef V
};

class AudioManager;
extern AudioManager *TheAudio;

// The bone array is built and torn down through BFME 2's out-of-line empty
// Coord3D constructor and destructor (the eh vector iterators push 0x0047A6A9
// and 0x000B3FD0).
#define COORD3D_VIEW_EXTERN_CTOR
#define COORD3D_VIEW_EXTERN_DTOR
#include "../../../Libraries/Include/Lib/Coord3DCtorView.h"

class Waypoint
{
public:
	Waypoint(unsigned int id, AsciiString name, const Coord3D *loc, AsciiString label1,
		AsciiString label2, AsciiString label3, bool biDirectional, int extra, AsciiString extraLabel);
	void addLink(Waypoint *other);
	void *m_vtable;
	int m_id;
	char m_pad08[0xc0 - 8];
};

// TheTerrainLogic's slot 35.
class DrawableXferTerrainView
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34)
	virtual Waypoint *getWaypointByID(int id);
#undef V
};

class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

template<int N>
class BitFlags
{
public:
	void xfer(Xfer *xfer);
	unsigned int m_bits[(N + 31) / 32];
};

class ModelConditionFlags : public BitFlags<591>
{
};

#include "../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"

#include "../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"

class Rva00271826
{
public:
	Rva00271826() throw();
	char bytes[0x50];
};

class DrawableLocoInfo
{
public:
	DrawableLocoInfo();
	int m_vtable;
	float m_4[12];
	float m_34[2];
	float m_3c[5];
	int m_50;
	int m_54;
};

class Anim2DTemplate
{
public:
	char m_pad[8];
	AsciiString m_name;
};

class Anim2DCollection;
extern Anim2DCollection *TheAnim2DCollection;

struct Rva002D752DNode;
class Rva002D752D
{
public:
	Rva002D752DNode *rva002D752D(const StringBase<char> &name);
};

class Anim2D
{
public:
	Anim2D(Anim2DTemplate *animTemplate, Anim2DCollection *collectionSystem);
	char m_pad[0xc];
	Anim2DTemplate *m_template;
	char m_rest[0x34 - 0x10];
};

class Rva00270025
{
public:
	void rva00270041();
	void *m_vtable;
	Anim2D *m_icon[14];
	unsigned int m_keepTillFrame[14];
};

class Rva00270BA8 { public: Rva00270025 *rva00270BA8(); };
class Rva002716Holder { public: void rva00271547(); };
class Rva0027974B { public: void rva0027974B(); };
class Rva00279354Host { public: void rva00279354(bool); };



class ThingTemplate
{
public:
	char m_pad[0x11a];
	unsigned char m_kindOfByte11A;
};

class Object
{
public:
	char m_pad[4];
	ThingTemplate *m_template;
	char m_pad8[0x74 - 8];
	ObjectID m_id;
	ObjectID getID() const { return m_id; }
	int getMultiLogicalBonePosition(const char *boneNamePrefix, int maxBones, Coord3D *positions,
		Matrix3D *transforms, bool convertToWorld, int extra) const;
};

// Slot 44 fills one record per index: the waypoint extra at +0 and the bone
// name prefix at +4 (retail passes one address and reads both fields).
struct EmbeddedPortalInfo
{
	int extra;
	AsciiString boneName;
};

// The draw module's slot 42 hands out the portal-bone interface whose slot
// 44 reports, per index, whether a portal exists and fills its record.
class DrawablePortalBones
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43)
	virtual bool getEmbeddedPortal(int index, EmbeddedPortalInfo *info);
#undef V
};

class DrawModule
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41)
	virtual DrawablePortalBones *getPortalBones();
#undef V
};

// Pathfinder::AddPortal (WB name lead) is still rowed under its placeholder.
class Rva002E9042 { public: void AddPortal(void *portal); };

class Pathfinder
{
public:
	void RemoveObjectFromPathfindMap(Object *obj);
	void AddObjectToPathfindMap(Object *obj);
};

class AI;
extern AI *TheAI;

class DrawableXferAIView
{
public:
	char m_pad[0x10];
	Pathfinder *m_pathfinder;
};

#include "../Common/Thing/thing.h"

class Drawable : public Thing, public Snapshot
{
public:
	void setID(void *);	// 0x00271058
	const Matrix3D *getTransformMatrix() const;
	void rva00272870(int decal);
	void xferDrawableModules(Xfer *xfer);
	void rva002781DA(Rva0010F149Handle info);
	void rva002791E7(const ModelConditionFlags &flags, unsigned int a, unsigned int b);
	bool rva00272C1E();

	void setID(int id) { setID((void *)id); }
	Rva00270025 *getIconInfo() { return reinterpret_cast<Rva00270BA8 *>(this)->rva00270BA8(); }

	void createEmbeddedPortals();

	virtual void DoXfer(Xfer *xfer);

	// Members at their Snapshot-relative offsets.
	Rva00271826 *m_04;
	Rva00271826 *m_08;
	RGBColor m_0c;
	unsigned int m_18;
	unsigned int m_1c;
	unsigned int m_20;
	float m_24;
	float m_28;
	char m_pad2c[4];
	float m_30[3];
	float m_3c[3];
	unsigned int m_48;
	float m_4c;
	float m_50;
	float m_54;
	float m_58;
	float m_5c;
	float m_60;
	float m_64;
	float m_68;
	float m_6c;
	float m_70;
	unsigned int m_74;
	float m_78;
	float m_7c;
	float m_80;
	bool m_84;
	char m_pad85[3];
	ICoord2D m_88;
	int m_90;
	float m_94;
	float m_98;
	Object *m_9c;
	int m_a0;
	char m_pada4[8];
	OpaqueRefElement4 m_ac;
	Rva000A8C9B m_b0;
	unsigned int m_b4;
	unsigned int m_b8;
	unsigned int m_bc;
	char m_padc0[8];
	unsigned int m_c8;
	unsigned int m_cc;
	unsigned int m_d0;
	char m_padd4[4];
	unsigned int m_d8;
	DrawableLocoInfo *m_dc;
	float m_e0;
	int m_e4;
	int m_e8;
	DrawModule **m_ec;
	char m_padf0[0x14];
	int m_104;
	int m_108;
	int m_10c;
	float m_110[12];
	float m_140[12];
	float m_170[12];
	float m_1a0;
	char m_pad1a4[0x44];
	ObjectID m_1e8;
	char m_pad1ec[0xc];
	ModelConditionFlags m_1f8;
	BitFlags<591> m_244;
	BitFlags<591> m_290;
	float m_2dc;
	char m_pad2e0[8];
	AsciiString m_2e8;
	AsciiString m_2ec;
	unsigned int m_2f0;
	Rva00270025 *m_2f4;
	float m_2f8;
	int m_2fc;
	unsigned int m_300;
	int m_304;
	int m_308;
	_STL::vector<Waypoint *> m_30c;
	unsigned int m_318;
	unsigned int m_31c;
	unsigned int m_320;
	unsigned int m_324;
	unsigned int m_328;
	char m_pad32c[0x18];
	unsigned int m_344;
	bool m_348;
	bool m_349;
	bool m_34a;
	char m_pad34b[0x3dd - 0x34b];
	bool m_3dd;
	bool m_3de;
	bool m_3df;
	bool m_3e0;
	bool m_3e1;
	bool m_3e2;
	bool m_3e3;
	bool m_3e4;
	bool m_3e5;
	bool m_3e6;
	bool m_3e7;
	bool m_3e8;
	bool m_3e9;
	bool m_3ea;
	bool m_3eb;
	char m_pad3ec[4];
	BuffManager *m_3f0;
	int m_3f4;
	char m_pad3f8[8];
	IRegion2D m_400;
};

// ?createEmbeddedPortals@Drawable@@QAEXXZ, retail 0x0027A018, 513 bytes; its
// one caller is the direct call at 0x0053023A. Identity: WB
// Drawable::createEmbeddedPortals (Drawable.cpp:1210, "Found only ... bones
// from" assert string); the "#embed" waypoint name, the 0x7FFFFFFE id, the
// draw-module slots and the pathfinder registration come from the retail body.
void Drawable::createEmbeddedPortals()
{
	Object *obj = m_9c;
	for (DrawModule **dm = m_ec; *dm; ++dm)
	{
		DrawablePortalBones *bones = (*dm)->getPortalBones();
		if (!bones)
			continue;
		EmbeddedPortalInfo info;
		for (int i = 0; bones->getEmbeddedPortal(i, &info); ++i)
		{
			Coord3D positions[10];
			int count = obj->getMultiLogicalBonePosition(info.boneName.str(), 10, positions, 0, true, 0);
			if (count < 2)
				continue;
			Waypoint *prev = 0;
			for (int j = 0; j < count; ++j)
			{
				Waypoint *portal = new Waypoint(0x7ffffffe, AsciiString("#embed"), &positions[j],
					AsciiString::TheEmptyString, AsciiString::TheEmptyString, AsciiString::TheEmptyString,
					false, info.extra, AsciiString::TheEmptyString);
				reinterpret_cast<Rva002E9042 *>(reinterpret_cast<DrawableXferAIView *>(TheAI)->m_pathfinder)->AddPortal(portal);
				if (prev)
				{
					prev->addLink(portal);
					portal->addLink(prev);
				}
				prev = portal;
				m_30c.push_back(portal);
			}
		}
	}
}
