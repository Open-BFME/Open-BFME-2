// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// stlport46
// platformsdk
// Small bodies from .text gaps no Ghidra function covers (forty-ninth
// batch; see GapBodiesGE01.cpp), all from /O1 retail regions between
// 0x00167E5A and 0x001DFFFF (reverse/retail_inventory/flag_regions.csv).
// Each begins after its neighbour's padding or ret and ends in its own ret.
// Retail bytes establish every shape; owning classes are not recovered, so
// each keeps an address-derived name and a view of only the members it
// touches. Callees use the ledger's existing spellings.

#include <windows.h>

class AsciiString;

// --- 0x00167E77 (15B): the +0xE8 word returned as a one-word handle; 0x00167F26 (17B): store a
// word's truth into the +0x104 flag.
struct GapHandle
{
	GapHandle(int v) : m_value(v) {}
	GapHandle(const GapHandle &that) : m_value(that.m_value) {}
	int m_value;
};

class Rva00167E77
{
public:
	GapHandle rva00167E77() const;
	void rva00167F26(int value);
private:
	char m_pad00[0xE8];
	int m_E8;
	char m_padEC[0x104 - 0xEC];
	bool m_104;
};

GapHandle Rva00167E77::rva00167E77() const
{
	return m_E8;
}

void Rva00167E77::rva00167F26(int value)
{
	m_104 = value != 0;
}

// --- 0x00167E86 (29B): copy the three-float +0xF0 value out through a
// reference.
struct GapFloat3
{
	GapFloat3 &operator=(const GapFloat3 &that)
	{
		x = that.x;
		y = that.y;
		z = that.z;
		return *this;
	}
	float x;
	float y;
	float z;
};

class Rva00167E86
{
public:
	void rva00167E86(GapFloat3 &out) const;
private:
	char m_pad00[0xF0];
	GapFloat3 m_F0;
};

void Rva00167E86::rva00167E86(GapFloat3 &out) const
{
	out = m_F0;
}

// --- 0x001B49B3 (17B): count the nodes of the ring whose sentinel is at
// +0x0C.
struct GapRingLink
{
	GapRingLink *m_next;
};

class Rva001B49B3
{
public:
	int rva001B49B3() const;
private:
	char m_pad00[0x0C];
	GapRingLink *m_sentinel;								// +0x0C
};

int Rva001B49B3::rva001B49B3() const
{
	int count = 0;
	for (GapRingLink *link = m_sentinel->m_next; link != m_sentinel; link = link->m_next)
		++count;
	return count;
}

// --- 0x001D9715 (10B) / 0x001D971F (12B): set / clear bits of the +0x48
// mask.
class Rva001D9715
{
public:
	void rva001D9715(unsigned int bits);
	void rva001D971F(unsigned int bits);
private:
	char m_pad00[0x48];
	unsigned int m_48;
};

void Rva001D9715::rva001D9715(unsigned int bits)
{
	m_48 |= bits;
}

void Rva001D9715::rva001D971F(unsigned int bits)
{
	m_48 &= ~bits;
}

// --- 0x001DBA77 (14B): both the +0x24 and +0x28 words are clear.
class Rva001DBA77
{
public:
	int rva001DBA77() const;
private:
	char m_pad00[0x24];
	int m_24;
	int m_28;
};

int Rva001DBA77::rva001DBA77() const
{
	return m_24 == 0 && m_28 == 0;
}

// --- 0x001DBA85 (22B): a scoped critical-section lock.
class Rva001DBA85
{
public:
	Rva001DBA85(void *section);
private:
	void *m_section;
};

Rva001DBA85::Rva001DBA85(void *section) : m_section(section)
{
	EnterCriticalSection((CRITICAL_SECTION *)section);
}

// --- 0x001DFE98 (18B): hold a counted object (+0x2C count).
struct GapCounted2C
{
	char m_pad00[0x2C];
	int m_refs;												// +0x2C
};

class Rva001DFE98
{
public:
	Rva001DFE98(GapCounted2C *object);
private:
	GapCounted2C *m_object;
};

Rva001DFE98::Rva001DFE98(GapCounted2C *object) : m_object(object)
{
	if (object)
		++object->m_refs;
}

// --- 0x001DE77C (18B): construct through the rowed 0x001DE3E3 initialiser.
class Rva001DE3E3
{
public:
	Rva001DE3E3(Rva001DE3E3 *source);
	Rva001DE3E3 *rva001DE3E3(Rva001DE3E3 *source);		// 0x001DE3E3
};

Rva001DE3E3::Rva001DE3E3(Rva001DE3E3 *source)
{
	rva001DE3E3(source);
}

// --- 0x001DED4A (20B): out-parameter forwarder over the rowed 0x001DE84F
// insert, returning its first argument.
struct InsertResult;
struct NoCaseTreeValue4;

namespace _STL
{
	template <class T1, class T2> struct pair
	{
		T1 first;
		T2 second;
	};
}

class Rva001DE556
{
public:
	InsertResult *rva001DE84F(InsertResult *out, const _STL::pair<const AsciiString, NoCaseTreeValue4> &value);
	InsertResult *rva001DED4A(InsertResult *out, const _STL::pair<const AsciiString, NoCaseTreeValue4> &value);
};

InsertResult *Rva001DE556::rva001DED4A(InsertResult *out, const _STL::pair<const AsciiString, NoCaseTreeValue4> &value)
{
	rva001DE84F(out, value);
	return out;
}
