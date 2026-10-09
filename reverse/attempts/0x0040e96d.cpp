// ??0ArmySummary@@QAE@ABV0@@Z
// partial score=0.97 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// stlport
// NEAR draft: ArmySummary copy constructor (vtable 0x00C394F0) at 0x0040E96D
// (384 bytes). Pinned spelling ??0BfmePod104@@QAE@ABU0@@Z is a placeholder for
// this class. 387B vs 384B: members/base/EH states match; the deep-copy loop
// differs in register choice (iterator esi vs retail ebx) and the entry
// temporary's holder release reloads its pointer from the stack where retail
// reuses the register. Uses a private novtable Snapshot view (class-gate).
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
}

class Rva0040E0EB : public _STL::vector<Rva0040CB11Entry>
{
public:
	__forceinline Rva0040E0EB() {}
	~Rva0040E0EB();
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
	_STL::vector<ObjectID> m_4C;
	int m_58;
	int m_5C;
	int m_60;
	AsciiString m_64;
};

ArmySummary::ArmySummary(const ArmySummary &other)
	: m_14(other.m_14), m_18(other.m_18), m_1C(other.m_1C), m_20(other.m_20),
	  m_24(other.m_24), m_28(other.m_28), m_2C(other.m_2C), m_30(other.m_30),
	  m_34(other.m_34), m_38(other.m_38), m_3C(other.m_3C),
	  m_4C(other.m_4C), m_58(other.m_58), m_5C(other.m_5C), m_60(other.m_60),
	  m_64(other.m_64)
{
	m_entries.reserve(other.m_entries.size());
	const Rva0040CB11Entry *end = other.m_entries.end();
	for (const Rva0040CB11Entry *it = other.m_entries.begin(); it != end; ++it)
	{
		Rva004F6093Holder holder(new ArmySummaryEntry(*static_cast<ArmySummaryEntry *>(it->m_second.m_ptr)));
		m_entries.push_back(Rva0040CB11Entry(it->m_first, holder));
	}
}
