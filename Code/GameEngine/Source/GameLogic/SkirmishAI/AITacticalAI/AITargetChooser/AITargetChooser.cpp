// cl: /MD /GX /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// The skirmish-AI object built at 0x0050542B (newed by 0x002C6144, freed by
// 0x002C5F91 / 0x002C61D5). Its member 0x005052AE passes
// "...\SkirmishAI\AITacticalAI\AITargetChooser\AITargetChooser.cpp" to
// GameLogicRandomValueReal, so this is AITargetChooser.cpp's object, and its
// entries are the "AIThreatFinder%d" objects (Rva002C589B). With no RTTI the
// class keeps its address-derived name.
//
// Target evidence for the layout:
//   +0x00 owner, kept for the AI-manager lookup in 0x0050535A
//   +0x04 a 0x18-byte Rva005A9562 built from the owner (dtor 0x000796BC)
//   +0x08 vector of owned Rva002C589B entries (non-virtual dtor 0x002C589B)
//   +0x14 a second pointer vector, cleared with the first
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

class AsciiString;
struct Coord3DBase;
// BFME2's Xfer: operator== overloads, grouped by cl at the first overload
// slot in reverse declaration order (Rva004E0513Xfer.cpp has the same view).
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


// Elements of the four vectors at +0x10/+0x28/+0x40/+0x58: each gets
// 0x004EDF03 then 0x004ECE1C from the 0x00505924 pass (both in the
// AITactic.cpp range).

class Rva005A9562
{
public:
	Rva005A9562(void *owner);
	~Rva005A9562();
	void rva005A9693();
	void rva005A9824();
	void rva005A91BE(Xfer *xfer);
	struct Rva0050542BTarget *rva005A910E();
private:
	unsigned char m_data[0x18];
};

struct Rva0050535AStore
{
	char m_pad00[0x54];
	float m_threshold;	// +0x54
};

// What the AI manager's per-owner record (0x002A8AB1) holds at +0x160.
struct Rva00505289Data
{
	char m_pad00[0x54];
	_STL::vector<int> m_54;		// +0x54 one entry per value
	_STL::vector<int> m_60;		// +0x60 optional per-entry kinds
	float m_6C;			// +0x6C seconds between rethinks
	float m_70;			// +0x70 keep chance
};

struct Rva002A8AB1Record
{
	char m_pad00[0x160];
	Rva00505289Data *m_160;		// +0x160
};

struct Rva002A8F24Record
{
	void *m_00;
	char m_pad04[0x10 - 4];
	int m_10;			// +0x10
};

class Rva002A8F24
{
public:
	Rva0050535AStore **rva002A8F24(void *owner);
	Rva002A8F24Record *rva002A8F24Record(void *owner);
	Rva002A8AB1Record *rva002A8AB1(void *owner);
	struct Rva002A8AE4Record *rva002A8AE4(void *owner);
};

class GameLogic;
extern GameLogic *TheGameLogic;

struct Rva005052AEGameLogicView
{
	char m_pad00[0x40];
	int m_frame;			// +0x40
};

extern int g_Va00DBA4E4;
float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);
int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

extern Rva002A8F24 *g_00DFEEF8;

class Object;

class Rva002C589B
{
public:
	Rva002C589B(int value, int kind, void *owner);
	~Rva002C589B();
	Object *rva002C5DA6();
	void rva002C5B46(Xfer *xfer);
	int rva0030F2C7() const;
	float rva002C5AE6();
	char m_pad00[4];
	int m_04;		// +0x04
	int m_08;		// +0x08 last rethink frame
	char m_pad0C[0x18 - 0xC];
	bool m_18;		// +0x18
	bool m_19;		// +0x19
	char m_pad1A[0x20 - 0x1A];
	int m_limit;		// +0x20
	char m_pad24[0x34 - 0x24];
	int m_34;		// +0x34
	int m_id;		// +0x38
};

// The +0x14 list's elements (filled from the global list by 0x005055DE):
// matched to entries by their +0x04 kind; slot 1 acts on a picked entry.
struct Rva0050542BTarget;

struct Rva0050542BOther
{
	virtual void v0();
	virtual void act(Rva002C589B *entry, int value, Rva0050542BTarget *target);
	int m_04;		// +0x04
};

struct Rva002A8AE4Record
{
	char m_pad00[0x15C];
	int m_15C;		// +0x15C
};

class Rva0050542B
{
public:
	void rva005058F7();
	void rva00505911();
	Rva0050542B(void *owner);
	~Rva0050542B();
	Rva002C589B *rva00505408(int id);
	Rva002C589B *rva005053A4();
	void xfer(Xfer *xfer);
private:
	bool rva0050535A(Rva002C589B *entry);
	Rva00505289Data *rva00505289();
	int rva0050529D();
	bool rva005052AE(Rva002C589B *entry);
	void rva00505544();
	void rva005055DE();
	void rva00505606();

	void *m_owner;					// +0x00
	Rva005A9562 *m_04;				// +0x04
	_STL::vector<Rva002C589B *> m_08;		// +0x08
	_STL::vector<Rva0050542BOther *> m_14;		// +0x14
};

Rva0050542B::Rva0050542B(void *owner)
	: m_owner(owner), m_04(0)
{
	m_04 = new Rva005A9562(owner);
}

Rva0050542B::~Rva0050542B()
{
	if (m_04) {
		delete m_04;
		m_04 = 0;
	}
	for (Rva002C589B **it = m_08.begin(); it != m_08.end(); ++it)
		delete *it;
	m_08.clear();
	m_14.clear();
}

Rva002C589B *Rva0050542B::rva00505408(int id)
{
	Rva002C589B **end = m_08.end();
	for (Rva002C589B **it = m_08.begin(); it != end; ++it)
		if ((*it)->m_id == id)
			return *it;
	return 0;
}

bool Rva0050542B::rva0050535A(Rva002C589B *entry)
{
	if (!entry->m_19 && !entry->m_18) {
		if (entry->m_04 == 1)
			return true;
		Rva0050535AStore *store = *g_00DFEEF8->rva002A8F24(m_owner);
		if (store->m_threshold > entry->rva002C5AE6())
			return true;
	}
	return false;
}

Rva002C589B *Rva0050542B::rva005053A4()
{
	Rva002C589B **it;
	for (it = m_08.begin(); it != m_08.end(); ++it) {
		Rva002C589B *entry = *it;
		if (rva0050535A(entry) && entry->rva0030F2C7() == 0)
			return entry;
	}
	for (it = m_08.begin(); it != m_08.end(); ++it) {
		Rva002C589B *entry = *it;
		if (rva0050535A(entry)) {
			int limit = entry->m_limit;
			if (entry->rva0030F2C7() < limit)
				return entry;
		}
	}
	return 0;
}

Rva00505289Data *Rva0050542B::rva00505289()
{
	return g_00DFEEF8->rva002A8AB1(m_owner)->m_160;
}

int Rva0050542B::rva0050529D()
{
	return g_00DFEEF8->rva002A8F24Record(m_owner)->m_10;
}

// True when the entry is done with (killed, finished, or its object gone);
// otherwise, once its rethink time is up, keep it with the data's chance or
// restart its clock.
bool Rva0050542B::rva005052AE(Rva002C589B *entry)
{
	if (entry->m_19 || entry->m_18)
		return true;
	if (entry->m_34 != 0 && entry->rva002C5DA6() == 0)
		return true;
	float elapsed = (float)(((Rva005052AEGameLogicView *)TheGameLogic)->m_frame - entry->m_08);
	if (elapsed >= (float)g_Va00DBA4E4 * rva00505289()->m_6C) {
		float roll = GetGameLogicRandomValueReal(0.0f, 1.0f, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITargetChooser\\AITargetChooser.cpp", 129);
		if (roll >= rva00505289()->m_70)
			return true;
		entry->m_08 = ((Rva005052AEGameLogicView *)TheGameLogic)->m_frame;
	}
	return false;
}

// One entry per value in the data, with the matching kind when there is
// one and kind 1 otherwise.
void Rva0050542B::rva00505544()
{
	Rva00505289Data *data = rva00505289();
	int *kind = data->m_60.begin();
	for (int *value = data->m_54.begin(); value != data->m_54.end(); ++value, ++kind) {
		if (kind != data->m_60.end())
			m_08.push_back(new Rva002C589B(*value, *kind, m_owner));
		else
			m_08.push_back(new Rva002C589B(*value, 1, m_owner));
	}
}

void Rva0050542B::rva005058F7()
{
	m_04->rva005A9693();
	rva00505544();
	rva005055DE();
}

void Rva0050542B::rva00505911()
{
	m_04->rva005A9824();
	rva00505606();
}

// Every entry that is done is either marked finished (it still has a count)
// or, when the +0x04 object offers a target, handed to a random element of
// the +0x14 list of its kind (AITargetChooser.cpp line 184).
void Rva0050542B::rva00505606()
{
	for (Rva002C589B **it = m_08.begin(); it != m_08.end(); ++it) {
		Rva002C589B *entry = *it;
		if (!rva005052AE(entry))
			continue;
		if (entry->rva0030F2C7() > 0) {
			entry->m_19 = true;
			continue;
		}
		Rva0050542BTarget *target = m_04->rva005A910E();
		if (!target)
			continue;
		_STL::vector<Rva0050542BOther *> matches;
		for (Rva0050542BOther **it2 = m_14.begin(); it2 != m_14.end(); ++it2) {
			Rva0050542BOther *other = *it2;
			if (other->m_04 == entry->m_04)
				matches.push_back(other);
		}
		if (matches.size() != 0) {
			int pick = GetGameLogicRandomValue(0, matches.size() - 1, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITargetChooser\\AITargetChooser.cpp", 184);
			Rva0050542BOther *chosen = matches[pick];
			int value = g_00DFEEF8->rva002A8AE4(m_owner)->m_15C;
			chosen->act(entry, value, target);
		}
	}
}

// 0x00505710: Version(1, 2) then the entries (count, then each entry);
// loading trims surplus entries and makes any missing ones. Version 1 saves
// carried an extra list of entries that go in front. Then the +0x04 object
// and the +0x14 list's size.
void Rva0050542B::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	unsigned int count = m_08.size();
	*xfer == count;
	if (xfer->IsStoring()) {
		Rva002C589B **end = m_08.end();
		for (Rva002C589B **it = m_08.begin(); it != end; ++it)
			(*it)->rva002C5B46(xfer);
	} else if (xfer->IsLoading()) {
		if (m_08.size() > count) {
			Rva002C589B **it = m_08.begin() + count;
			while (it != m_08.end()) {
				delete *it;
				it = m_08.erase(it);
			}
		}
		for (unsigned int i = 0; i < count; ++i) {
			Rva002C589B *entry = m_08[i];
			if (entry) {
				entry->rva002C5B46(xfer);
			} else {
				entry = new Rva002C589B(-1, 1, m_owner);
				entry->rva002C5B46(xfer);
				m_08.push_back(entry);
			}
		}
	}
	if (version.m_minimum < 2 && xfer->IsLoading()) {
		unsigned int extra = 0;
		*xfer == extra;
		for (unsigned int i = 0; i < extra; ++i) {
			Rva002C589B *entry = new Rva002C589B(-1, 1, m_owner);
			entry->rva002C5B46(xfer);
			m_08.insert(m_08.begin(), entry);
		}
	}
	m_04->rva005A91BE(xfer);
	unsigned int others = m_14.size();
	*xfer == others;
}
