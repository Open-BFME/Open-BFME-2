// cl: /O1 /G7 /arch:SSE /EHs /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva005E8C54@@QAE@PAXH0PBURva005E8C54Source@@@Z, retail 0x005E8C54..
// 0x005E8CB0 (92 bytes, EH, RET 16), and the holder constructor that builds
// it, ??0Rva005E8CB0@@QAE@PAXH0PBURva005E8C54Source@@@Z, retail 0x005E8CB0..
// 0x005E8CF8 (72 bytes, EH, RET 16). No WorldBuilder names; both are
// address-derived.
//
// The 12-byte object keeps the source's +0x18 at +0x00 and builds its +0x04
// member through the rowed Rva005F86FE constructor (0x005F86FE). It then runs
// its own 0x005E8B66 (238 bytes, not yet rowed; pinned) with the second
// argument and, when the member reports entries (rowed 0x005F8408), its
// rowed forwarder 0x005F841F. The holder allocates it with operator new and
// keeps the pointer at +0x00. The earlier verdicts were blocked on
// 0x005F8408 and 0x005F841F, which are rowed now.

#include <vector>

class Rva005F86FE
{
public:
	Rva005F86FE(void *a1, void *a2);
	virtual ~Rva005F86FE();
private:
	void *m_04;
};

// A counted object: the rowed fastcall release 0x0007DEEF drops the +0x04
// count and destroys it at zero.
struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

// The 0x14-byte counted record of three words, rowed constructor 0x005CEAE6.
class Rva005CEAE6 : public TargetRef00217D4C
{
public:
	struct Payload { int v[3]; };
	Rva005CEAE6(const Payload *src) throw();
private:
	Payload m_data;					// +0x08
};

// A typed handle on it, and the member list's generic handle it converts to.
class Rva005CEAE6Handle
{
public:
	explicit Rva005CEAE6Handle(Rva005CEAE6 *object) : m_object(object) { if (object) ++object->references; }
	~Rva005CEAE6Handle() { if (m_object) ReleaseTreeHintRef00217D4C(m_object); }
	Rva005CEAE6 *m_object;
};

struct Rva005F888CRef
{
	Rva005F888CRef(const Rva005CEAE6Handle &other) : m_object(other.m_object) { if (m_object) ++m_object->references; }
	~Rva005F888CRef() { if (m_object) ReleaseTreeHintRef00217D4C(m_object); }
	TargetRef00217D4C *m_object;
};

// The member's rowed count and forwarders, spelled on this address class.
class Rva005F8427
{
public:
	int rva005F8408() const;
	void rva005F841F();
	void rva005F88CE(const Rva005F888CRef &ref);
};

// The three-word value the record copies; its constructor is rowed at
// 0x005CC49A under WWMath's ICoord3D, which this body shares.
struct ICoord3D
{
	ICoord3D(int x, int y, int z);
	int x, y, z;
};

struct Rva005E8C54Source
{
	unsigned char m_pad00[0x18];
	void *m_18;
};

class Rva005E8C54
{
public:
	Rva005E8C54(void *a, int b, void *c, const Rva005E8C54Source *source);
	void rva005E8B66(int b);

private:
	void *m_source18;				// +0x00
	Rva005F86FE m_member04;			// +0x04
};

Rva005E8C54::Rva005E8C54(void *a, int b, void *c, const Rva005E8C54Source *source)
	: m_source18(source->m_18),
	  m_member04(a, c)
{
	rva005E8B66(b);
	if (reinterpret_cast<Rva005F8427 *>(&m_member04)->rva005F8408() > 0)
		reinterpret_cast<Rva005F8427 *>(&m_member04)->rva005F841F();
}

class Rva005E8CB0
{
public:
	Rva005E8CB0(void *a, int b, void *c, const Rva005E8C54Source *source);

private:
	Rva005E8C54 *m_object;			// +0x00
};

Rva005E8CB0::Rva005E8CB0(void *a, int b, void *c, const Rva005E8C54Source *source)
	: m_object(new Rva005E8C54(a, b, c, source))
{
}

// Rva005E908C's constructor, retail 0x005E908C..0x005E90EC (96 bytes, EH,
// RET 20), and its holder Rva005E90EC's, retail 0x005E90EC..0x005E9137 (75
// bytes): the 16-byte sibling of the pair above.
// It keeps the third and fourth arguments at +0x00/+0x04, builds the same
// Rva005F86FE member at +0x08 from the first and third, runs its own
// 0x005E8FEC with the second and fifth arguments, then calls the member's
// forwarder when it reports entries.
//
// 0x005E8FEC (160 bytes, EH, RET 8) fills the member when the +0x04 object's
// +0x20 is clear: TheLivingWorldBuildingTemplateStore lists the keys for the
// source's +0x40 (rowed 0x002E02F0) and, for each it resolves (rowed
// 0x002B6498), a counted record of (second argument, +0x04, template) is
// added through the free helper 0x005E8F6F (125 bytes, EH, cdecl). The
// unit builds with /EHs: retail treats the vector's inlined free as able to
// throw (state -1 is stored before it) and evaluates the +0x40 key first.
enum ScienceType
{
	SCIENCE_NONE = 0
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class ArmorTemplate;

class Rva002E02F0
{
public:
	void rva002E02F0(int key, _STL::vector<ScienceType> *out);
};

class Rva002B6498
{
public:
	ArmorTemplate *rva002B6498(NameKeyType key);
};

class Rva0022C0CDSubsystem;
extern Rva0022C0CDSubsystem *TheLivingWorldBuildingTemplateStore;

struct Rva005E8FECSource
{
	unsigned char m_pad00[0x40];
	int m_40;
};

struct Rva005E8FECOwner
{
	unsigned char m_pad00[0x20];
	int m_20;
};

void rva005E8F6F(Rva005F86FE *list, const ICoord3D &value)
{
	Rva005CEAE6Handle record(new Rva005CEAE6(reinterpret_cast<const Rva005CEAE6::Payload *>(&value)));
	reinterpret_cast<Rva005F8427 *>(list)->rva005F88CE(record);
}

class Rva005E908C
{
public:
	Rva005E908C(void *a, int b, void *c, Rva005E8FECOwner *d, Rva005E8FECSource *e);
	void rva005E8FEC(int b, Rva005E8FECSource *e);

private:
	void *m_00;						// +0x00
	Rva005E8FECOwner *m_04;			// +0x04
	Rva005F86FE m_member08;			// +0x08
};

void Rva005E908C::rva005E8FEC(int b, Rva005E8FECSource *e)
{
	Rva005E8FECOwner *owner = m_04;
	if (owner->m_20 == 0)
	{
		_STL::vector<ScienceType> keys;
		int key = e->m_40;
		reinterpret_cast<Rva002E02F0 *>(TheLivingWorldBuildingTemplateStore)->rva002E02F0(key, &keys);
		_STL::vector<ScienceType>::iterator end = keys.end();
		for (_STL::vector<ScienceType>::iterator it = keys.begin(); it != end; ++it)
		{
			ArmorTemplate *found = reinterpret_cast<Rva002B6498 *>(TheLivingWorldBuildingTemplateStore)->rva002B6498((NameKeyType)*it);
			if (found)
				rva005E8F6F(&m_member08, ICoord3D(b, (int)m_04, (int)found));
		}
	}
}

Rva005E908C::Rva005E908C(void *a, int b, void *c, Rva005E8FECOwner *d, Rva005E8FECSource *e)
	: m_00(c),
	  m_04(d),
	  m_member08(a, c)
{
	rva005E8FEC(b, e);
	if (reinterpret_cast<Rva005F8427 *>(&m_member08)->rva005F8408() > 0)
		reinterpret_cast<Rva005F8427 *>(&m_member08)->rva005F841F();
}

class Rva005E90EC
{
public:
	Rva005E90EC(void *a, int b, void *c, Rva005E8FECOwner *d, Rva005E8FECSource *e);

private:
	Rva005E908C *m_object;			// +0x00
};

Rva005E90EC::Rva005E90EC(void *a, int b, void *c, Rva005E8FECOwner *d, Rva005E8FECSource *e)
	: m_object(new Rva005E908C(a, b, c, d, e))
{
}
