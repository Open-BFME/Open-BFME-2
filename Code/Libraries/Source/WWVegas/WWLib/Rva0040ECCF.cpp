// cl: /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /EHsc
// stlport
// ?AddArmyEntry@ArmySummary@@QAEHABVRva004F6093Holder@@@Z @0x0040ECCF 128B
// Adds holder to sorted entry vector and broadcasts to listener list.
// Evidence: callees rowed (forEach 0x0040D8D6, Entry ctor 0x0040CB11,
// push_back 0x0040E8D1, Release 0x0007DEEF, forwarders 0x001FF3A9 slot0 and
// 0x005CC208 slot2); callers at 0x0040EE4E 0x0040F0CB 0x0040F178 0x0040F291
// 0x0040F428 0x004F7D07; vector at +0x40 and index at +0x3c shared with
// 0x0040ED4F; Entry (int plus Holder) and Holder layouts from
// stlport_sort_rva0040cb11entry.cpp.
// ?MergeUnitsFromArmy@ArmySummary@@QAEXAAV1@@Z @0x0040ED4F 314B: drains another
// instance's entries (back to front, notifying its listeners through vslots
// 4 and 3) into a holder vector, resets its flag at +0x14 and index to 1,
// then re-adds each holder here through AddArmyEntry. Target evidence: retail
// REL32s at 0x0040ED7A..0x0040EE75 and the shared +0x40/+0x3C layout. The
// /Ireference/shims/bfmealloc include matches the vector reserve/push_back
// copies; the visible entry ctor (noinline, holder copy kept out of line as
// at 0x0040CB11) lets MSVC keep the loop-2 holder in ESI across the call.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/arch:SSE /G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva0040F454Target
{
	char m_pad00[8];
	float m_value;
	char m_pad0C[0x94 - 0xC];
	int m_94;
	char m_pad98[0xAC - 0x98];
	TargetRef00217D4C m_ac;
};

class Rva004F6093Holder
{
public:
	explicit Rva004F6093Holder(Rva0040F454Target *ptr) : m_ptr(ptr)
	{
		if (m_ptr)
			++m_ptr->m_ac.references;
	}
	Rva004F6093Holder(const Rva004F6093Holder &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->m_ac.references;
	}
	~Rva004F6093Holder()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(&m_ptr->m_ac);
	}
	Rva004F6093Holder &operator=(const Rva004F6093Holder &other)
	{
		if (this != &other)
		{
			if (other.m_ptr)
				++other.m_ptr->m_ac.references;
			if (m_ptr)
				ReleaseTreeHintRef00217D4C(&m_ptr->m_ac);
			m_ptr = other.m_ptr;
		}
		return *this;
	}

public:
	Rva0040F454Target *m_ptr;
};

// Retail's dtor (0x002B703F) was built under different EH flags; call it.
extern template _STL::vector<Rva004F6093Holder>::~vector();

class Rva0040CB11Entry
{
public:
	Rva0040CB11Entry(int key, const Rva004F6093Holder &val);

public:
	int m_first;
	Rva004F6093Holder m_second;
};

#pragma inline_depth(0)
inline __declspec(noinline) Rva0040CB11Entry::Rva0040CB11Entry(int key, const Rva004F6093Holder &val) : m_first(key), m_second(val)
{
}
#pragma inline_depth()

class Rva0040D8D6Listener
{
public:
	virtual void notify0(void *arg, int value);
	virtual void dummy();
	virtual void notify2(void *arg, int value);
	virtual void notify3(void *arg, int value);
	virtual void notify4(void *arg, int value);
};

class Rva0040D8D6List
{
public:
	void forEach(void (Rva0040D8D6Listener::*notify)(void *, int), void *arg, int value);

private:
	Rva0040D8D6Listener **m_begin;
	Rva0040D8D6Listener **m_end;
	Rva0040D8D6Listener **m_capacity;
	unsigned int m_index;
};

class INI;

class ArmySummaryEntry : public Rva0040F454Target
{
public:
	ArmySummaryEntry();
	void Parse(INI *ini);

private:
	char m_padB4[0xC8 - 0xB4];
};

class ArmySummary
{
public:
	int AddArmyEntry(const Rva004F6093Holder &holder);
	void MergeUnitsFromArmy(ArmySummary &other);
	static void parseArmyEntry(INI *ini, void *instance, void *store, const void *userData);

private:
	char m_pad00[4];
	Rva0040D8D6List m_list;
	bool m_14;
	char m_pad15[0x3C - 0x15];
	int m_next;
	_STL::vector<Rva0040CB11Entry, _STL::allocator<Rva0040CB11Entry> > m_vec;
};

int ArmySummary::AddArmyEntry(const Rva004F6093Holder &holder)
{
	int argVal = (int)holder.m_ptr;
	m_list.forEach(&Rva0040D8D6Listener::notify0, this, argVal);
	int old = m_next;
	m_next = old + 1;
	{
		m_vec.push_back(Rva0040CB11Entry(old, holder));
	}
	m_list.forEach(&Rva0040D8D6Listener::notify2, this, old);
	return old;
}

void ArmySummary::MergeUnitsFromArmy(ArmySummary &other)
{
	m_vec.reserve(m_vec.size() + other.m_vec.size());
	_STL::vector<Rva004F6093Holder> holders;
	holders.reserve(other.m_vec.size());
	while (!other.m_vec.empty())
	{
		Rva0040CB11Entry &back = other.m_vec.back();
		other.m_list.forEach(&Rva0040D8D6Listener::notify4, &other, back.m_first);
		Rva004F6093Holder holder(back.m_second);
		holders.push_back(holder);
		other.m_vec.pop_back();
		other.m_list.forEach(&Rva0040D8D6Listener::notify3, &other, (int)holder.m_ptr);
	}
	other.m_14 = false;
	other.m_next = 1;
	while (!holders.empty())
	{
		const Rva004F6093Holder holder(holders.back());
		holders.pop_back();
		AddArmyEntry(holder);
	}
}

// ?parseArmyEntry@ArmySummary@@SAXPAVINI@@PAX1PBX@Z @0x0040F077 121B: the
// "ArmyEntry" field parser (FieldParse row at 0x0083957C beside DisplayNameTag,
// Color, NightColor and SurvivalThreshhold; offset 0, so it reads the instance):
// news a 0xC8-byte ArmySummaryEntry (ctor 0x0040C351), parses it with 0x0040C5FA and
// adds the holder here. The method name follows the INI field name.
void ArmySummary::parseArmyEntry(INI *ini, void *instance, void *store, const void *userData)
{
	ArmySummaryEntry *army = new ArmySummaryEntry;
	Rva004F6093Holder holder(army);
	army->Parse(ini);
	((ArmySummary *)instance)->AddArmyEntry(holder);
}

class Rva0037EB1D
{
public:
	void rva0037EB1D(void *dest);

private:
	char m_pad00[0xA8];

public:
	int m_a8;
};

class BfmeY1038;
BfmeY1038 * __stdcall bfmeFind1038(int a);

// ?rva0040F10F@Rva002E2903Player@@QAEXPAVRva0037EB1D@@@Z @0x0040F10F 142B:
// called with ECX = the player found by 0x002B51F8 (caller 0x0037EBBA) but never
// reads it. Looks up the list by the source's +0xA8 id via bfmeFind1038, copies
// the source into a new ArmySummaryEntry (0x0037EB1D), bumps its +0x94 and adds it.
class Rva002E2903Player
{
public:
	void rva0040F10F(Rva0037EB1D *source);
};

void Rva002E2903Player::rva0040F10F(Rva0037EB1D *source)
{
	ArmySummary *list = (ArmySummary *)bfmeFind1038(source->m_a8);
	if (list != 0)
	{
		ArmySummaryEntry *army = new ArmySummaryEntry;
		Rva004F6093Holder holder(army);
		source->rva0037EB1D(army);
		++army->m_94;
		list->AddArmyEntry(holder);
	}
}
