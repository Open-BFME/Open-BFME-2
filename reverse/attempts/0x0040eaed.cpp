// ??4ArmySummary@@QAEAAV0@ABV0@@Z
// partial score=0.95 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// stlport
// NEAR draft: ArmySummary::operator= at 0x0040EAED (399 bytes). Pinned
// spelling ??4BfmeAssignRecord104@@QAEAAU0@ABU0@@Z is a placeholder for this
// class. 396B vs 399B: same residue family as the copy ctor (holder kept in
// memory/iterator in a register where retail does the opposite).
#include <vector>
#include "ascii_string.h"
class Xfer;

// Snapshot base as a novtable view: retail never stores the base vtable
// 0x00BBB554 in this constructor; its dtor 0x0049B47C stays out of line.
class __declspec(novtable) Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot();

protected:
	virtual void loadPostProcess() = 0;
	virtual const char *GetSnapshotName() const = 0;
	virtual void xfer(Xfer *xfer) = 0;
};

enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7fffffff
};

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva0040F454Target
{
	char m_pad00[0xAC];
	TargetRef00217D4C m_ac;
};

class ArmySummaryEntry : public Rva0040F454Target
{
public:
	ArmySummaryEntry(const ArmySummaryEntry &other);

private:
	char m_padB4[0xC8 - 0xB4];
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

	Rva0040F454Target *m_ptr;
};

class Rva0040CB11Entry
{
public:
	Rva0040CB11Entry(int key, const Rva004F6093Holder &value) : m_first(key), m_second(value) {}

	int m_first;
	Rva004F6093Holder m_second;
};

namespace _STL
{
template <> void vector<Rva0040CB11Entry>::reserve(size_type n);
template <> void vector<Rva0040CB11Entry>::push_back(const Rva0040CB11Entry &value);
template <> vector<int> &vector<int>::operator=(const vector<int> &other);
}

class Rva0040E0EB : public _STL::vector<Rva0040CB11Entry>
{
public:
	__forceinline Rva0040E0EB() {}
	~Rva0040E0EB();
};

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
};

class Rva00330757Member
{
public:
	Rva00330757Member();
	~Rva00330757Member();

private:
	void *m_begin;
	void *m_end;
	void *m_limit;
	unsigned int m_index;
};

class ArmySummary : public Snapshot, public Rva00330757Member
{
public:
	ArmySummary(const ArmySummary &other);
	ArmySummary &operator=(const ArmySummary &other);
	void rva0040DED9();
	virtual ~ArmySummary();
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);

private:
	bool m_14;
	AsciiString m_18;
	int m_1C;
	AsciiString m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	int m_3C;
	Rva0040E0EB m_entries; // +0x40
	_STL::vector<int> m_4C;
	int m_58;
	int m_5C;
	int m_60;
	AsciiString m_64;
};

ArmySummary &ArmySummary::operator=(const ArmySummary &other)
{
	if (&other != this)
	{
		rva0040DED9();
		m_14 = other.m_14;
		m_18 = other.m_18;
		m_1C = other.m_1C;
		m_20 = other.m_20;
		m_24 = other.m_24;
		m_28 = other.m_28;
		m_2C = other.m_2C;
		m_30 = other.m_30;
		m_34 = other.m_34;
		m_38 = other.m_38;
		m_3C = other.m_3C;
		m_58 = other.m_58;
		m_5C = other.m_5C;
		m_60 = other.m_60;
		m_64 = other.m_64;
		m_entries.reserve(other.m_entries.size());
		const Rva0040CB11Entry *end = other.m_entries.end();
		for (const Rva0040CB11Entry *it = other.m_entries.begin(); it != end; ++it)
		{
			Rva004F6093Holder holder(new ArmySummaryEntry(*static_cast<ArmySummaryEntry *>(it->m_second.m_ptr)));
			Rva0040D8D6List *list = reinterpret_cast<Rva0040D8D6List *>(static_cast<Rva00330757Member *>(this));
			list->forEach(&Rva0040D8D6Listener::notify0, this, (int)holder.m_ptr);
			m_entries.push_back(Rva0040CB11Entry(it->m_first, holder));
			list->forEach(&Rva0040D8D6Listener::notify2, this, it->m_first);
		}
		m_4C = other.m_4C;
	}
	return *this;
}
