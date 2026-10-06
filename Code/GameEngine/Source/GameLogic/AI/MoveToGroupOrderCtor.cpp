// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ??0MoveToGroupOrder@@QAE@XZ @0x005479C3 and
// ??0MoveToFormationGroupOrder@@QAE@XZ @0x00547FF2: the two MoveTo group
// orders the byte-verified GroupOrder factory 0x00354EFC news (0x40 and 0x48
// bytes, keyed by the MoveToGroupOrder / MoveToFormationGroupOrder name
// caches 0x00DD20D8 / 0x00DD211C). Both build the GroupOrder base 0x005488C5,
// install their own vftable (0x00C6A478 / 0x00C6A4CC) and default-construct a
// hash_map member through 0x00547944 (+0x28 / +0x30).
//
// The member's element type is target evidence: the map xfer helper
// 0x0054755B (called by the MoveTo xfer 0x00547805 on +0x28) xfers each
// 16-byte pair through 0x00547245 = XferObjectID on the key then Xfer slot
// 0x60 on the 12 bytes after it, the same slot the xfer uses on the
// zero-initialised 3-float +0x18 (a Coord3D), and copies values with three
// movsd. So hash_map<ObjectID, Coord3D>. The hasher spelling follows ZH's
// ObjectID maps (rts::hash, equal_to); the bytes do not distinguish it.
//
// 0x00547944 is this map's default ctor (100 buckets) and 0x00547875 the
// hashtable ctor it calls: the instantiation emitted in this unit, with its
// own EH funcinfo (0x00B980E0), which ICF could not fold into the
// NameKeyType/ArmorTemplate twin at 0x00360B59. Its callees (vector base
// 0x00025100, _M_initialize_buckets 0x00148DDF) are ICF-folded; so is the
// clear 0x001DBCDC called by the unit's hashtable dtor 0x005473F7.
// The two dtors (0x0054747E / 0x00547B8A) and their deleting dtors (slot 0,
// 0x0054752B / 0x00547C9A) close the pair. The dtors' EH frames need /GX
// (this compiler drops the hashtable dtor's frame under /EHsc).

// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <hash_map>
#include <cstddef>

enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_LONG = 0x7fffffff
};

namespace rts
{

template <typename T> struct hash
{
	size_t operator()(const T &value) const;
};

}

// Retail stores the zeros before the map ctor call, so they come from member
// construction in declaration order: the float-triple ctor in the init lists
// and the memberwise copy ctor (same inline bodies as WWMath/coord3d.cpp).
struct Coord3D
{
	inline Coord3D(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Coord3D(const Coord3D &that)
	{
		x = that.x;
		y = that.y;
		z = that.z;
	}

	float x;
	float y;
	float z;
};

typedef std::hash_map<
	ObjectID,
	Coord3D,
	rts::hash<ObjectID>,
	std::equal_to<ObjectID> > ObjectCoord3DMap;

class Rva0036E346;

class GroupOrder
{
public:
	GroupOrder();
	GroupOrder(const GroupOrder &other);
	GroupOrder(Rva0036E346 *holder);
	virtual ~GroupOrder();

private:
	unsigned char m_pad04[0x18 - 4];
};

class MoveToGroupOrder : public GroupOrder
{
public:
	MoveToGroupOrder();
	MoveToGroupOrder(Rva0036E346 *holder, const Coord3D &destination, bool flag24, bool flag25);
	MoveToGroupOrder(const MoveToGroupOrder &other);
	virtual ~MoveToGroupOrder();

private:
	Coord3D m_destination;             // +0x18
	bool m_flag24;                     // +0x24
	bool m_flag25;                     // +0x25
	ObjectCoord3DMap m_positions;      // +0x28
	int m_value3C;                     // +0x3C
};

class MoveToFormationGroupOrder : public GroupOrder
{
public:
	MoveToFormationGroupOrder();
	MoveToFormationGroupOrder(Rva0036E346 *holder, int value18, const Coord3D &destination,
		float angle, bool flag2C);
	MoveToFormationGroupOrder(const MoveToFormationGroupOrder &other);
	virtual ~MoveToFormationGroupOrder();

private:
	int m_value18;                     // +0x18
	Coord3D m_destination;             // +0x1C
	float m_angle;                     // +0x28
	bool m_flag2C;                     // +0x2C
	ObjectCoord3DMap m_positions;      // +0x30
	bool m_flag44;                     // +0x44
};

MoveToGroupOrder::MoveToGroupOrder()
	: m_destination(0.0f, 0.0f, 0.0f), m_flag24(false), m_flag25(false), m_value3C(0)
{
}

MoveToFormationGroupOrder::MoveToFormationGroupOrder()
	: m_value18(-1), m_destination(0.0f, 0.0f, 0.0f), m_angle(0.0f), m_flag2C(false), m_flag44(false)
{
}

// 0x00547963: holder ctor (GroupOrder holder base 0x00548A25).
MoveToGroupOrder::MoveToGroupOrder(Rva0036E346 *holder, const Coord3D &destination,
	bool flag24, bool flag25)
	: GroupOrder(holder), m_destination(destination), m_flag24(flag24), m_flag25(flag25),
	  m_value3C(0)
{
}

// 0x00547A18: copy ctor; retail sets +0x24 and starts an empty map.
MoveToGroupOrder::MoveToGroupOrder(const MoveToGroupOrder &other)
	: GroupOrder(other), m_destination(other.m_destination), m_flag24(true),
	  m_flag25(other.m_flag25), m_value3C(0)
{
}

// 0x00547F88: holder ctor.
MoveToFormationGroupOrder::MoveToFormationGroupOrder(Rva0036E346 *holder, int value18,
	const Coord3D &destination, float angle, bool flag2C)
	: GroupOrder(holder), m_value18(value18), m_destination(destination), m_angle(angle),
	  m_flag2C(flag2C), m_flag44(false)
{
}

// 0x0054804C: copy ctor; retail sets +0x2C and starts an empty map.
MoveToFormationGroupOrder::MoveToFormationGroupOrder(const MoveToFormationGroupOrder &other)
	: GroupOrder(other), m_value18(other.m_value18), m_destination(other.m_destination),
	  m_angle(other.m_angle), m_flag2C(true), m_flag44(false)
{
}

MoveToGroupOrder::~MoveToGroupOrder()
{
}

MoveToFormationGroupOrder::~MoveToFormationGroupOrder()
{
}
