// cl: /Ireference/shims/bfme2_ascii
// cl: /DNDEBUG /MD /EHsc

// BFME 1 donor89d88dcd24: game/Libraries/Source/WWVegas/WWLib/S4SortElem12Swap.cpp.
// BFME 2 native 0x003319FB..0x00331A46 is75B (Ghidra boundary).
// Verified iter_swap331BD2 and sort siblings call the existing pinned name.
// Native reads/writes integer0, owning string4, byte8; the sibling loops
// establish12B stride. Those are target facts; the donor supplies swap semantics.
// Use the canonical one-pointer AsciiString ownership rather than a private
// StringBase class. Its constructor, assignment and destructor reach the
// same verified copy/set/release workers, and the complete body remains exact.

#include "ascii_string.h"

struct S4Name
{
	S4Name(const S4Name &other) : m_base(other.m_base) {}
	~S4Name(void) {}
	S4Name &operator=(const S4Name &other)
	{
		m_base = other.m_base;
		return *this;
	}

	AsciiString m_base;
};

struct S4SortElem12
{
	int m_bfmeA;
	S4Name m_bfmeName;
	char m_bfmeC;

	S4SortElem12(const S4SortElem12 &other) :
		m_bfmeA(other.m_bfmeA),
		m_bfmeName(other.m_bfmeName),
		m_bfmeC(other.m_bfmeC)
	{
	}
	~S4SortElem12(void) {}
	S4SortElem12 &operator=(const S4SortElem12 &other)
	{
		m_bfmeA = other.m_bfmeA;
		m_bfmeName = other.m_bfmeName;
		m_bfmeC = other.m_bfmeC;
		return *this;
	}
};

void Rva002E00E0Swap(S4SortElem12 &left, S4SortElem12 &right)
{
	S4SortElem12 temporary(left);
	left = right;
	right = temporary;
}
