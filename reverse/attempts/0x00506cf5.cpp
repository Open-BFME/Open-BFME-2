// ?Rva00506CF5@@YA?AUCoord3D@@PAXPAU1@@Z
// partial score=0.9216 date=2026-10-05
// cl: /O1 /MD /GX /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_vector3 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// The skirmish-AI object behind vtable 0x00863FAC, newed by 0x004EC430 in the
// AITactic.cpp range (its assert path is at 0x00862968; the neighbouring
// asserts at 0x005061FD.. name AITacticsGenerator.cpp). No RTTI and no donor:
// the class keeps the address-derived name its matched member 0x00506B74
// already carries (Rva00506B74CopyCompare.cpp).
//
// Target evidence for the layout:
//   +0x00 base Rva00506B1B (ctor 0x00506B1B, dtor 0x00506B28, vtable
//         0x00863F9C with __purecall in slots 1 and 2)
//   +0x08 the pointer the ctor is given
//   +0x0C vector of owned pointers: slot 2 (0x005071A1) runs each through
//         dtor 0x005ADA40 plus operator delete, then erase 0x0031BD55
//   +0x18 Coord3D, +0x24 flag, +0x28 Coord3D, both points seeded from the
//         -1 triple at 0x00DD0870 (Gen00DD0870)
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "ascii_string.h"
#include "vector3.h"

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

struct Coord3D : public Coord3DBase
{
	Coord3D() {}
	Coord3D(const Coord3D &that) { x = that.x; y = that.y; z = that.z; }
	bool equals(const Coord3DBase &that) const;
	void set(const Coord3DBase *that) { x = that->x; y = that->y; z = that->z; }
};

extern Coord3DBase Gen00DD0870;

class Rva005AD9C0Hit
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3(void *arg);
};

// BFME2's Xfer: operator== overloads, grouped by cl at the first overload
// slot in reverse declaration order (Rva004E0513Xfer.cpp has the same view).
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class Rva00506FE9Hit;

class Rva005ADA40
{
public:
	Rva005ADA40(unsigned int index, void *owner);
	~Rva005ADA40();
	void rva005AE0AD(Xfer *xfer);
	void rva005AE26A(Coord3D *point, float angle, int more);
	void rva005AD99C(const AsciiString &name, _STL::vector<Rva00506FE9Hit *> *hits);
	void rva005ADC63();
	Rva005AD9C0Hit *rva005AD9C0(void *arg);
private:
	unsigned char m_data[0x2C];	// new'd at 0x2C by 0x005073D6
};

class Rva00506B1B
{
public:
	Rva00506B1B();
	virtual ~Rva00506B1B();
	virtual void v1() = 0;
	virtual void v2() = 0;
private:
	bool m_04;
};

// 0x00506FE9's collaborators. Object and RebuildHoleBehaviorInterface stay
// opaque; the views below carry only what that body reads.
class Object;
class RebuildHoleBehaviorInterface;

class RebuildHoleBehavior
{
public:
	static RebuildHoleBehaviorInterface *getRebuildHoleBehaviorInterfaceFromObject(Object *obj);
};

struct Rva00506FE9Template
{
	char m_pad00[0x64];
	AsciiString m_name;		// +0x64
};

class Rva00506FE9RebuildView
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual const Rva00506FE9Template *getRebuildTemplate();	// slot 3
};

struct Rva00506FE9ObjectView
{
	void *m_vptr;
	const Rva00506FE9Template *m_template;	// +0x04
	char m_pad08[0x74 - 8];
	int m_id;				// +0x74
};

class Rva00506FE9Hit
{
public:
	virtual void v0(); virtual void v1(); virtual void v2();
	virtual void v3(); virtual void v4(); virtual void v5();
	virtual void v6(void *owner, int flag);	// +0x18
	void rva0055ADBA(void *owner);
	float m_04;
	char m_pad08[0x24 - 8];
	int m_24;
};

struct Rva002A8B59Data
{
	char m_pad00[0x88];
	float m_88;
};

class Rva002A8F24
{
public:
	Rva002A8B59Data *rva002A8B59(void *owner);
};

extern Rva002A8F24 *g_00DFEEF8;

Coord3D __cdecl Rva00506CF5(void *owner, Coord3D *point);

class Rva00506B74 : public Rva00506B1B
{
public:
	Rva00506B74(void *owner);
	virtual ~Rva00506B74();
	virtual void v1();
	virtual void v2();
	bool rva00506B74(Coord3D *out);
	void rva0050722A(Coord3D *point);
	void rva00506B96(const Coord3D *point);
	Rva005AD9C0Hit *rva00506BF7(void *arg);
	bool rva00506C39(void *arg);
	Rva005ADA40 *rva00506C64(unsigned int index);
	void rva00507522();
	void rva00506FE9(Object *obj);
	void rva005073D6(Xfer *xfer);
private:
	void *m_08;
	_STL::vector<Rva005ADA40 *> m_0C;
	Coord3D m_18;
	bool m_24;
	Coord3D m_28;
};

// ??0Rva00506B74@@QAE@PAX@Z
Rva00506B74::Rva00506B74(void *owner)
	: m_08(owner)
{
	m_18.set(&Gen00DD0870);
	m_24 = false;
	m_28.set(&Gen00DD0870);
	m_28 = Rva00506CF5(m_08, &m_18);
}

// ??1Rva00506B74@@UAE@XZ
Rva00506B74::~Rva00506B74()
{
	v2();
}

// Slot 1 (0x00506BDC).
void Rva00506B74::v1()
{
	for (Rva005ADA40 **it = m_0C.begin(), **end = m_0C.end(); it != end; ++it)
		(*it)->rva005ADC63();
}

// Slot 2 (0x005071A1): free every element, then empty the vector.
void Rva00506B74::v2()
{
	for (Rva005ADA40 **it = m_0C.begin(), **end = m_0C.end(); it != end; ++it)
		delete *it;
	m_0C.clear();
}

void Rva00506B74::rva00506B96(const Coord3D *point)
{
	if (!m_24)
		m_18 = *point;
}

Rva005AD9C0Hit *Rva00506B74::rva00506BF7(void *arg)
{
	Rva005ADA40 **end = m_0C.end();
	for (Rva005ADA40 **it = m_0C.begin(); it != end; ++it) {
		Rva005AD9C0Hit *hit = (*it)->rva005AD9C0((char *)arg + 0xC);
		if (hit) {
			hit->v3(arg);
			return hit;
		}
	}
	return 0;
}

bool Rva00506B74::rva00506C39(void *arg)
{
	for (Rva005ADA40 **it = m_0C.begin(), **end = m_0C.end(); it != end; ++it) {
		if ((*it)->rva005AD9C0(arg))
			return true;
	}
	return false;
}

Rva005ADA40 *Rva00506B74::rva00506C64(unsigned int index)
{
	if (index < m_0C.size())
		return m_0C[index];
	return 0;
}

void Rva00506B74::rva00507522()
{
	if (!m_24) {
		if (rva00506B74(&m_28))
			rva0050722A(&m_28);
	}
	m_24 = true;
}

// 0x00506FE9: collect the owned elements' hits for the object's template name
// (its rebuild template when it is a rebuild hole), then rescale and re-run
// every hit that belongs to this object.
void Rva00506B74::rva00506FE9(Object *obj)
{
	_STL::vector<Rva00506FE9Hit *> hits;
	AsciiString name;
	RebuildHoleBehaviorInterface *rebuild = RebuildHoleBehavior::getRebuildHoleBehaviorInterfaceFromObject(obj);
	if (rebuild)
		name = ((Rva00506FE9RebuildView *)rebuild)->getRebuildTemplate()->m_name;
	else
		name = ((Rva00506FE9ObjectView *)obj)->m_template->m_name;
	Rva005ADA40 **end = m_0C.end();
	for (Rva005ADA40 **it = m_0C.begin(); it != end; ++it)
		(*it)->rva005AD99C(name, &hits);
	if (!hits.empty()) {
		Rva002A8B59Data *data = g_00DFEEF8->rva002A8B59(m_08);
		for (Rva00506FE9Hit **h = hits.begin(); h != hits.end(); ++h) {
			Rva00506FE9Hit *hit = *h;
			if (hit->m_24 == ((Rva00506FE9ObjectView *)obj)->m_id) {
				hit->rva0055ADBA(m_08);
				float v = hit->m_04;
				hit->m_04 = data->m_88 * v;
				hit->v6(m_08, 0);
			}
		}
	}
}

// 0x005073D6: save/load. Version 2 added the +0x28 point; on load the owned
// elements are rebuilt (0x2C bytes each, ctor 0x005AD9FF) before each one
// transfers itself (0x005AE0AD).
void Rva00506B74::rva005073D6(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	*xfer == m_18;
	*xfer == m_24;
	if (version.m_minimum >= 2)
		*xfer == m_28;
	unsigned int count = m_0C.size();
	*xfer == count;
	if (xfer->IsLoading()) {
		if (!m_0C.empty()) {
			for (Rva005ADA40 **it = m_0C.begin(), **end = m_0C.end(); it != end; ++it)
				delete *it;
			m_0C.clear();
		}
		for (unsigned int i = 0; i < count; ++i) {
			Rva005ADA40 *element = new Rva005ADA40(i, m_08);
			m_0C.push_back(element);
		}
	}
	Rva005ADA40 **end = m_0C.end();
	for (Rva005ADA40 **it = m_0C.begin(); it != end; ++it)
		(*it)->rva005AE0AD(xfer);
}

// 0x00506CC3: the waypoint with this name, walking TheTerrainLogic's list from
// its first-waypoint virtual (+0x84) along the +0x1C links and comparing the
// +0x08 name through AsciiString::compare (0x000069D6). Eight callers in the
// script-engine range (0x0023FDBD..) plus two in this cluster.
class Waypoint
{
public:
	const AsciiString &getName() const { return m_name; }
	Waypoint *getNext() const { return m_pNext; }
	const Coord3D *getLocation() const { return &m_location; }
private:
	int m_00;
	int m_04;
	AsciiString m_name;		// +0x08
	Coord3D m_location;		// +0x0C
	int m_18;
	Waypoint *m_pNext;		// +0x1C
};

class TerrainLogic
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual float getGroundHeight(float x, float y, Coord3D *normal) const; virtual void v07();
	virtual void v08(); virtual void getExtent(Region3D *extent) const; virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32();
	virtual Waypoint *getFirstWaypoint();	// +0x84
};

extern TerrainLogic *TheTerrainLogic;

Waypoint *Rva00506CC3FindWaypoint(const AsciiString &name)
{
	for (Waypoint *way = TheTerrainLogic->getFirstWaypoint(); way; way = way->getNext()) {
		if (way->getName() == name)
			return way;
	}
	return 0;
}

float ACos(float x);
float normalizeAngle(float angle);

struct Rva0050722AExtent
{
	Coord3DBase lo;
	Coord3DBase hi;
};

// 0x0050722A: add an element facing from the point towards the map centre.
void Rva00506B74::rva0050722A(Coord3D *point)
{
	Rva0050722AExtent extent;
	TheTerrainLogic->getExtent((Region3D *)&extent);
	Vector3 dir;
	dir.Set((extent.hi.x - extent.lo.x) * 0.5f, (extent.hi.y - extent.lo.y) * 0.5f, 0.0f);
	Vector3 pos;
	pos.Set(point->x, point->y, 0.0f);
	dir -= pos;
	dir.Normalize();
	Vector3 xAxis;
	xAxis.Set(1.0f, 0.0f, 0.0f);
	float angle = ACos(WWMath::Clamp(Vector3::Dot_Product(dir, xAxis), -1.0f, 1.0f));
	if (Vector3::Cross_Product_Z(dir, xAxis) > 0.0f)
		angle *= -1.0f;
	angle = normalizeAngle(angle - 1.5707964f);
	unsigned int index = m_0C.empty() ? 0 : m_0C.size();
	Rva005ADA40 *element = new Rva005ADA40(index, m_08);
	m_0C.push_back(element);
	element->rva005AE26A(point, angle, index != 0);
}

// 0x00506CF5: where an AI player should consider home. In mode 3 that is its
// slot's "Player_%d_Start" waypoint (else the given point when it is set);
// otherwise the nearest start waypoint to the first of the owner's living-world
// entries that reports a position, skipping the first slot when the
// living-world lookup names another owner. The height comes from the terrain.
class GameLogic;
class GameSlot;
struct Rva00506C82Arg;

extern GameLogic *TheGameLogic;
GameSlot *Rva00506C82Find(const Rva00506C82Arg *arg);

struct Rva00506CF5GameLogicView
{
	char m_pad00[0x114];
	int m_mode;		// +0x114
};

struct Rva00506CF5SlotView
{
	char m_pad00[0x10];
	int m_startIndex;	// +0x10
};

struct Rva00506CF5OwnerView
{
	int getId() const { return m_id; }
	char m_pad00[0x3AC];
	int m_id;		// +0x3AC
};

class Rva00506CF5Entry
{
public:
	bool rva0040CCC6(int id, Coord3D *pos, Coord3D *aux, int flag);
};

struct Rva003F4D09Result
{
	char m_pad00[0x14];
	int m_id;		// +0x14
};

class Rva0020E6B7Result
{
public:
	Rva003F4D09Result *rva003F4D09();
};

class Rva0020E6B7Owner
{
public:
	Rva0020E6B7Result *rva0020E6B7();
};

class Rva002BA8F1Logic
{
public:
	void rva002B323C(_STL::vector<Rva00506CF5Entry *> *entries, int id);
	char m_pad00[0xB0];
	Rva0020E6B7Owner *m_B0;	// +0xB0
};

extern Rva002BA8F1Logic *g_009FEF10;

Coord3D __cdecl Rva00506CF5(void *owner, Coord3D *point)
{
	Coord3D result(*(const Coord3D *)&Gen00DD0870);
	if (((Rva00506CF5GameLogicView *)TheGameLogic)->m_mode == 3) {
		GameSlot *slot = Rva00506C82Find((const Rva00506C82Arg *)owner);
		if (slot) {
			int startIndex = ((Rva00506CF5SlotView *)slot)->m_startIndex;
			AsciiString name;
			name.format("Player_%d_Start", startIndex + 1);
			Waypoint *way = Rva00506CC3FindWaypoint(name);
			if (way) {
				result = *way->getLocation();
				result.z = TheTerrainLogic->getGroundHeight(result.x, result.y, 0);
				return result;
			}
		} else if (point && !point->equals(Gen00DD0870)) {
			result = *point;
		}
	} else {
	float bestDist = 0.0f;
	Waypoint *best = 0;
	bool found = false;
	_STL::vector<Rva00506CF5Entry *> entries;
	int id = ((Rva00506CF5OwnerView *)owner)->m_id;
	g_009FEF10->rva002B323C(&entries, id);
	if (!entries.empty()) {
		Coord3D pos;
		Coord3D aux;
		Rva00506CF5Entry **end = entries.end();
		Rva00506CF5Entry **it = entries.begin();
		for (; it != end; ++it) {
			if (found)
				break;
			if ((*it)->rva0040CCC6(((Rva00506CF5OwnerView *)owner)->getId(), &pos, &aux, 0))
				found = true;
		}
		if (found) {
			Rva003F4D09Result *other = g_009FEF10->m_B0->rva0020E6B7()->rva003F4D09();
			bool skipFirst = other && ((Rva00506CF5OwnerView *)owner)->m_id != other->m_id;
			for (int i = skipFirst; i < 8; ++i) {
				AsciiString name;
				name.format("Player_%d_Start", i + 1);
				Waypoint *way = Rva00506CC3FindWaypoint(name);
				if (way) {
					const Coord3D *loc = way->getLocation();
					float dx = loc->x - pos.x;
					float dy = loc->y - pos.y;
					float dz = loc->z - pos.z;
					float dist = dx * dx + dy * dy + dz * dz;
					if (!best || dist < bestDist) {
						best = way;
						bestDist = dist;
					}
				}
			}
			if (best) {
				result = *best->getLocation();
				result.z = TheTerrainLogic->getGroundHeight(result.x, result.y, 0);
				return result;
			}
		}
	}
	}
	return result;
}
