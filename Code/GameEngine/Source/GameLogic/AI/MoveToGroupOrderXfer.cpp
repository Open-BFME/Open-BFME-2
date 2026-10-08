// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// Xfer of the two MoveTo group orders (vftable slot 3 of 0x00C6A478 /
// 0x00C6A4CC) and of their hash_map<ObjectID, Coord3D> member (see
// MoveToGroupOrderCtor.cpp for the layouts).
//
// ?xfer@MoveToGroupOrder@@UAEXPAVXfer@@@Z @0x00547805 (112B): GroupOrder xfer
//   0x00548AC2, version {1,2}, the +0x18 Coord3D (Xfer slot 0x60), bool +0x24
//   (slot 0x90), the map, then bool +0x25 from version 2 on (cleared when an
//   older save loads).
// ?xfer@MoveToFormationGroupOrder@@UAEXPAVXfer@@@Z @0x00547DE9 (115B):
//   version {1,1}, int +0x18 (slot 0x7C), Coord3D +0x1C, float +0x28 (slot
//   0x70), bool +0x2C, the map at +0x30, bool +0x44.
// 0x0054755B (241B): the map xfer, the hash_map twin of the rowed
//   map<int,int> xfer Rva00470222Xfer: version {1,1}, type name
//   "std::hash_map" (0x00C14DF4), count, then per-pair xfer on save; on load
//   it throws "Map must be empty on load" for a non-empty map, else reads
//   count pairs and stores each value through operator[] (0x005474E7).
// 0x00547245 (30B): the pair xfer, XferObjectID 0x003060B2 on the key, then
//   the Coord3D slot on the value through the Xfer XferObjectID returns
//   (retail reuses its eax rather than reloading the xfer).
// Callees that are ICF-folded STLport bodies resolve through pins: begin
// 0x00427195, iterator ++ 0x0041E832, the converting pair copy 0x0004254E and
// the default pair ctor 0x00326BE6.

#include <hash_map>
#include <cstddef>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;
typedef int Int;

enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_LONG = 0x7fffffff
};

namespace rts
{

// ZH's identity hash (STLTypedefs.h): retail's _M_insert 0x00547430 hashes
// the key inline as its own value.
template <typename T> struct hash
{
	size_t operator()(const T &value) const
	{
		return (size_t)value;
	}
};

}

// The WWMath Coord3D shape (Libraries/Source/WWVegas/WWMath/coord3d.cpp):
// empty default ctor and dtor plus a memberwise copy ctor.
struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &that)
	{
		x = that.x;
		y = that.y;
		z = that.z;
	}
	~Coord3D() {}

	float x;
	float y;
	float z;
};

typedef std::hash_map<
	ObjectID,
	Coord3D,
	rts::hash<ObjectID>,
	std::equal_to<ObjectID> > ObjectCoord3DMap;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual Bool isLoading();
	virtual Bool isSaving();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Xfer &xferVersion(XferVersion *version);
	virtual Xfer &xferTypeName(const char *const &name);
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void xferCoord3D(Coord3D *value);
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void xferReal(Real *value);
	virtual void slot29();
	virtual Xfer &xferUnsignedInt(UnsignedInt *value);
	virtual void xferInt(Int *value);
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void xferBool(Bool *value);
};

extern Xfer &XferObjectID(Xfer *xfer, ObjectID *id);

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(XferException *result, int tag, const char *format, ...);
extern int g_guardTargetTypeThrowInfo;
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *object, void *throwInfo);
#pragma comment(linker, "/alternatename:?_CxxThrowException@@YGXPAX0@Z=__CxxThrowException@8")

typedef _STL::pair<ObjectID, Coord3D> ObjectCoord3DPair;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

class Object
{
public:
	char m_pad0[0x31C];
	int m_31C; // +0x31C float bits
	int m_320; // +0x320 float bits
};

class Rva00295A0FCommands
{
public:
	void Rva00295A0FCommand(void *pos, int maxShots, int source);
};

class AICommandInterface
{
public:
	void aiMoveToPositionAmphibious(const Coord3D *position, CommandSourceType cmdSource);
	void aiMoveToPosition(const Coord3D *pos, int cmdSource);
};

class AIUpdateInterface
{
public:
	char m_pad0[0x20];
	AICommandInterface m_commands; // +0x20
};

void Rva00547245Xfer(Xfer *xfer, ObjectCoord3DPair *pair)
{
	XferObjectID(xfer, &pair->first).xferCoord3D(&pair->second);
}

Xfer *Rva0054755BXfer(Xfer *xfer, ObjectCoord3DMap *map)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	UnsignedInt count = map->size();
	xfer->xferTypeName("std::hash_map").xferUnsignedInt(&count);

	if (xfer->isSaving()) {
		for (ObjectCoord3DMap::iterator it = map->begin(); it != map->end(); ++it) {
			ObjectCoord3DPair item(*it);
			Rva00547245Xfer(xfer, &item);
		}
	} else {
		if (map->size() != 0) {
			XferException error;
			bfmeFormatText(&error, 4, "Map must be empty on load");
			_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
		}
		ObjectCoord3DPair item;
		while (count != 0) {
			--count;
			Rva00547245Xfer(xfer, &item);
			(*map)[item.first] = item.second;
		}
	}
	return xfer;
}

class GroupOrder
{
public:
	virtual ~GroupOrder();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad04[0x18 - 4];
};

class MoveToGroupOrder : public GroupOrder
{
public:
	virtual void xfer(Xfer *xfer);
	bool rva00547188(Object *obj, int dummy);
	void rva0054764C(Object *obj, AIUpdateInterface *aiUpdate, Coord3D *pos);

private:
	Coord3D m_destination;             // +0x18
	Bool m_flag24;                     // +0x24
	Bool m_flag25;                     // +0x25
	ObjectCoord3DMap m_positions;      // +0x28
	Int m_value3C;                     // +0x3C
};

class MoveToFormationGroupOrder : public GroupOrder
{
public:
	virtual void xfer(Xfer *xfer);

private:
	Int m_value18;                     // +0x18
	Coord3D m_destination;             // +0x1C
	Real m_angle;                      // +0x28
	Bool m_flag2C;                     // +0x2C
	ObjectCoord3DMap m_positions;      // +0x30
	Bool m_flag44;                     // +0x44
};

void MoveToGroupOrder::xfer(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 2;
	GroupOrder::xfer(xfer);
	xfer->xferVersion(&version);
	xfer->xferCoord3D(&m_destination);
	xfer->xferBool(&m_flag24);
	Rva0054755BXfer(xfer, &m_positions);
	if (version.m_currentVersion >= 2)
		xfer->xferBool(&m_flag25);
	else if (xfer->isLoading())
		m_flag25 = false;
}

void MoveToFormationGroupOrder::xfer(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	GroupOrder::xfer(xfer);
	xfer->xferVersion(&version);
	xfer->xferInt(&m_value18);
	xfer->xferCoord3D(&m_destination);
	xfer->xferReal(&m_angle);
	xfer->xferBool(&m_flag2C);
	Rva0054755BXfer(xfer, &m_positions);
	xfer->xferBool(&m_flag44);
}

// ?rva0054764C@MoveToGroupOrder@@QAEXPAVObject@@PAVAIUpdateInterface@@PAUCoord3D@@@Z, retail 0x0054764C 124B.
// Chain from 0x00547188: if destination check passes copy x/y to obj+0x31C and
// issue aiMoveToPositionAmphibious else branch on m_flag24 to Rva00295A0FCommand or aiMoveToPosition.
// Evidence: this+0x18/+0x24 MoveTo layout plus caller 0x005478B5 (slot 4) passing
// Object+AIUpdate+Coord3D plus rowed callees.
void MoveToGroupOrder::rva0054764C(Object *obj, AIUpdateInterface *aiUpdate, Coord3D *pos)
{
	if (rva00547188(obj, (int)pos)) {
		float xy[2];
		xy[0] = m_destination.x;
		xy[1] = m_destination.y;
		obj->m_31C = *(int *)&xy[0];
		obj->m_320 = *(int *)&xy[1];
		aiUpdate->m_commands.aiMoveToPositionAmphibious(&m_destination, CMD_FROM_PLAYER);
	} else {
		if (m_flag24)
			((Rva00295A0FCommands *)&aiUpdate->m_commands)->Rva00295A0FCommand(pos, 0x7FFFFFFF, 0);
		else
			aiUpdate->m_commands.aiMoveToPosition(pos, 0);
	}
}
