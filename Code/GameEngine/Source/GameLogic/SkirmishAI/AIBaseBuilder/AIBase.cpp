// cl: /MD /GX /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_vector3 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
//
// The 0x2C-byte elements the skirmish-AI object Rva00506B74 owns in its +0x0C
// vector (Rva00506B74Tactic.cpp builds them with operator new and this ctor,
// deletes them, and calls their pinned members). Layout from the ctor:
//   +0x00 vector of owned Rva005DCE08 (non-virtual dtor 0x005DCE08)
//   +0x0C the element's index, +0x10 cleared, +0x14 the owner
//   +0x18 Coord3D and +0x24 float, both zeroed
//   +0x28 an owned polymorphic object
//
//   0x005AD9FF  ctor (index, owner)
//   0x005ADA40  dtor: delete every item, ::delete the +0x28 object, free
//               the vector
//   0x005AD9C0  the first item hit (0x005DCC86) by the argument
//   0x005AD964  whether the owner's start position is not yet among
//               TheSkirmishAIManager's +0x864 list
//   0x005ADC63  update: retire the +0x28 object once done (0x004E9378), or
//               start one (0x005ADAB2); then update every item
//   0x005ADCBE  pick a base template for the current map (or the .bss name
//               when the start is still open) that fits the owner's start
//               position, at random when several do
//   0x005ADE1D  lay out: copy each template order (copy ctor 0x00573EB8),
//               grow the items up to its 1-based slot, rotate its offset by
//               the angle about Z, then hand it to that item (0x005DCE62)
//   0x005AE26A  place: pick a template for the owner's side (0x005ADCBE),
//               take the point (and the angle when the template keeps it),
//               then lay the base out (0x005ADE1D)
//   0x005AE0AD  xfer: index, point, angle, the base template by name, the
//               items, then the +0x28 order
//
// The assert path these bodies share with 0x005ADCBE names the retail file
// GameLogic/SkirmishAI/AIBaseBuilder/AIBase.cpp; the templates come from
// TheBaseTemplateLibrary (0x00A03124).
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

#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
// STLport already supplies the placement forms always.h would redefine.
#define _OPERATOR_NEW_DEFINED_
#include "matrix3d.h"
#include <algorithm>

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

struct Rva005AE26AOwner
{
	char m_pad00[0x58];
	AsciiString m_58;	// +0x58
};

struct Coord3D : public Coord3DBase
{
	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
};

class Rva005AD9C0Hit;

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


class Rva00573E7C;

class Rva005DCE08
{
public:
	~Rva005DCE08();
	Rva005AD9C0Hit *rva005DCC86(void *arg);
	void rva005DCCFB();
	void rva005DCEAD(Xfer *xfer);
	void rva005DCE62(Rva00573E7C *order);
};

class Rva005DCDD9
{
public:
	Rva005DCDD9(int index, int owner);
private:
	char m_data[0x18];
};

class Rva004E9378
{
public:
	bool rva004E9378();
};

class Rva00506FE9Hit
{
public:
	void rva0055ADBA(void *owner);
};

class GameSlot
{
public:
	char m_pad00[0x10];
	int m_10;		// +0x10, the slot's start position index
};

struct Rva00506C82Arg;
GameSlot *__cdecl Rva00506C82Find(const Rva00506C82Arg *arg);

class Rva002A8F24
{
public:
	char m_pad000[0x864];
	_STL::vector<int> m_usedStarts;	// +0x864
};
extern Rva002A8F24 *g_00DFEEF8;

class Rva005ADA40Owned
{
public:
	virtual ~Rva005ADA40Owned();
	virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
	virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
	virtual void v9(); virtual void v10(); virtual void v11();
	virtual void xfer(Xfer *xfer, void *owner);	// slot 12
	virtual Coord3D getOffset() const;		// slot 13
};

class Rva00573E7C : public Rva005ADA40Owned
{
public:
	Rva00573E7C();
	Rva00573E7C(const Rva00573E7C &that);
	char m_pad04[0x40 - 4];
	Coord3D m_point;	// +0x40
	float m_angle;		// +0x4C
	int m_50;		// +0x50, the 1-based item it goes to
	char m_pad54[0x60 - 0x54];
};

class Rva00573A00
{
public:
	void rva00573A00(const Coord3D *point);
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
	const AsciiString &keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Rva00573E7C;

// One base layout from TheBaseTemplateLibrary (+0x08 map name, +0x0C start
// positions it fits).
class Rva0041E912Template
{
public:
	char m_pad00[0x08];
	AsciiString m_name;			// +0x08
	_STL::vector<int> m_starts;		// +0x0C
	bool m_18;				// +0x18
	_STL::vector<Rva00573E7C *> m_orders;	// +0x1C
};

class MapMetaData
{
public:
	UnicodeString rva00300D0E();
};

class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};
extern MapCache *TheMapCache;

class GlobalData
{
public:
	char m_pad00[0x0C];
	AsciiString m_mapName;	// +0x0C
};
extern class GlobalData *TheWritableGlobalData;

// A file-level AsciiString in .bss that a template name may also match.
extern const AsciiString g_00E06448;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

// TheBaseTemplateLibrary (registered at 0x0022F9C0, global 0x00A03124)
class Rva0022BD9ASubsystem
{
public:
	bool rva0041E912(const AsciiString &side, _STL::vector<Rva0041E912Template *> &out);
	Rva0041E912Template *rva0041E764(NameKeyType key);
	NameKeyType rva0041E971(Rva0041E912Template *tmpl);
};
extern Rva0022BD9ASubsystem *g_00E03124;

class Rva005ADA40
{
public:
	Rva005ADA40(unsigned int index, void *owner);
	~Rva005ADA40();
	Rva005AD9C0Hit *rva005AD9C0(void *arg);
	bool rva005AD964();
	void rva005ADAB2();
	void rva005ADC63();
	void rva005AE0AD(Xfer *xfer);
	Rva0041E912Template *rva005ADCBE(int notFirst, const _STL::vector<Rva0041E912Template *> &list);
	void rva005ADE1D(const Coord3D *point, float angle, Rva0041E912Template *tmpl);
	void rva005AE26A(Coord3D *point, float angle, int notFirst);
private:
	_STL::vector<Rva005DCE08 *> m_items;	// +0x00
	int m_index;				// +0x0C
	Rva0041E912Template *m_10;		// +0x10
	void *m_owner;				// +0x14
	Coord3D m_point;			// +0x18
	float m_angle;				// +0x24
	Rva00573E7C *m_owned;			// +0x28
};

Rva005ADA40::Rva005ADA40(unsigned int index, void *owner)
{
	m_10 = 0;
	m_index = index;
	m_owner = owner;
	m_point.zero();
	m_owned = 0;
	m_angle = 0.0f;
}

Rva005ADA40::~Rva005ADA40()
{
	for (Rva005DCE08 **it = m_items.begin(); it != m_items.end(); ++it)
		delete *it;
	if (m_owned) {
		::delete m_owned;
		m_owned = 0;
	}
}

Rva005AD9C0Hit *Rva005ADA40::rva005AD9C0(void *arg)
{
	Rva005AD9C0Hit *hit = 0;
	for (Rva005DCE08 **it = m_items.begin(); it != m_items.end(); ++it) {
		hit = (*it)->rva005DCC86(arg);
		if (hit)
			break;
	}
	return hit;
}

void Rva005ADA40::rva005ADC63()
{
	Rva00573E7C *owned = m_owned;
	if (owned) {
		if (((Rva004E9378 *)owned)->rva004E9378()) {
			((Rva00506FE9Hit *)owned)->rva0055ADBA(m_owner);
			::delete m_owned;
			m_owned = 0;
		}
	} else {
		rva005ADAB2();
	}
	for (Rva005DCE08 **it = m_items.begin(); it != m_items.end(); ++it)
		(*it)->rva005DCCFB();
}

bool Rva005ADA40::rva005AD964()
{
	GameSlot *slot = Rva00506C82Find((const Rva00506C82Arg *)m_owner);
	if (slot) {
		int start = slot->m_10 + 1;
		_STL::vector<int> &used = g_00DFEEF8->m_usedStarts;
		int *end = used.end();
		for (int *it = used.begin(); it != end; ++it) {
			if (*it == start)
				return false;
		}
	}
	return true;
}

void Rva005ADA40::rva005AE0AD(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	*xfer == m_index;
	*xfer == m_point;
	*xfer == m_angle;
	AsciiString name;
	if (xfer->IsStoring() && m_10)
		name = TheNameKeyGenerator->keyToName(g_00E03124->rva0041E971(m_10));
	*xfer == name;
	if (xfer->IsLoading() && name != AsciiString::TheEmptyString)
		m_10 = g_00E03124->rva0041E764(TheNameKeyGenerator->nameToKey(name));
	unsigned int count = m_items.size();
	*xfer == count;
	if (xfer->IsLoading()) {
		for (unsigned int i = 0; i < count; ++i)
			m_items.push_back((Rva005DCE08 *)new Rva005DCDD9(i, (int)m_owner));
	}
	Rva005DCE08 **end = m_items.end();
	for (Rva005DCE08 **it = m_items.begin(); it != end; ++it)
		(*it)->rva005DCEAD(xfer);
	bool hasOwned = m_owned != 0;
	*xfer == hasOwned;
	if (hasOwned) {
		if (xfer->IsLoading())
			m_owned = new Rva00573E7C;
		m_owned->xfer(xfer, m_owner);
	}
}

Rva0041E912Template *Rva005ADA40::rva005ADCBE(int notFirst, const _STL::vector<Rva0041E912Template *> &list)
{
	Rva0041E912Template *chosen = 0;
	const MapMetaData *map = TheMapCache->findMap(TheWritableGlobalData->m_mapName);
	if (map) {
		bool open = rva005AD964();
		_STL::vector<Rva0041E912Template *> candidates;
		AsciiString mapName = ((MapMetaData *)map)->rva00300D0E();
		for (Rva0041E912Template *const *it = list.begin(); it != list.end(); ++it) {
			Rva0041E912Template *tmpl = *it;
			if (tmpl->m_name.compare(mapName) != 0) {
				if (!open || tmpl->m_name.compare(g_00E06448) != 0)
					continue;
			}
			if (tmpl->m_starts.begin() == tmpl->m_starts.end()) {
				candidates.push_back(tmpl);
			} else {
				int start = Rva00506C82Find((const Rva00506C82Arg *)m_owner)->m_10 + 1;
				int *end = tmpl->m_starts.end();
				if (_STL::find(tmpl->m_starts.begin(), end, start) != end)
					candidates.push_back(tmpl);
			}
		}
		if (!candidates.empty()) {
			unsigned int count = candidates.size();
			if (count > 1)
				chosen = candidates[GetGameLogicRandomValue(0, count - 1,
					"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AIBaseBuilder\\AIBase.cpp",
					211)];
			else
				chosen = candidates[0];
		}
	}
	return chosen;
}

void Rva005ADA40::rva005AE26A(Coord3D *point, float angle, int notFirst)
{
	_STL::vector<Rva0041E912Template *> templates;
	if (g_00E03124->rva0041E912(((Rva005AE26AOwner *)m_owner)->m_58, templates)) {
		Rva0041E912Template *chosen = rva005ADCBE(notFirst, templates);
		if (chosen) {
			m_10 = chosen;
			m_point = *point;
			if (chosen->m_18)
				m_angle = angle;
			rva005ADE1D(&m_point, m_angle, chosen);
			return;
		}
	}
}

// Coord3D from a WWMath vector (retail copies the returned temporary).
static inline void copyVector(Coord3D *dst, const Vector3 &v)
{
	dst->x = v.X;
	dst->y = v.Y;
	dst->z = v.Z;
}

void Rva005ADA40::rva005ADE1D(const Coord3D *point, float angle, Rva0041E912Template *tmpl)
{
	Matrix3D rotation(true);
	rotation.Rotate_Z(angle);
	for (Rva00573E7C **it = tmpl->m_orders.begin(); it != tmpl->m_orders.end(); ++it) {
		Rva00573E7C *order = new Rva00573E7C(**it);
		int slot = order->m_50;
		int missing = slot - m_items.size();
		for (int i = 0; i < missing; ++i) {
			int index = m_items.empty() ? 0 : m_items.size();
			m_items.push_back((Rva005DCE08 *)new Rva005DCDD9(index, (int)m_owner));
		}
		Vector3 offset(order->getOffset().x, order->getOffset().y, order->getOffset().z);
		Coord3D at;
		copyVector(&at, rotation.Rotate_Vector(offset));
		((Rva00573A00 *)order)->rva00573A00(&at);
		order->m_point = *point;
		order->m_angle = angle;
		m_items[slot - 1]->rva005DCE62(order);
	}
}
