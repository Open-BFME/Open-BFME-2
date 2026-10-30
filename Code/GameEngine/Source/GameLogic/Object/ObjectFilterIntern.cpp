// cl: /O1 /DNDEBUG /MD
// stlport
//
// ?Rva00361790@@YAHPAVRva00360F55@@@Z at 0x00361790 (135 bytes).
// Pool intern for the 0x94-byte ObjectFilter science-cluster record: returns
// the index of an equal record (bumping its use count) or appends the record
// with a use count of 1 and returns the new last index. Closed from the 0.96
// bank with a top-tested for loop over the typed array (the bank's do-while
// with a byte offset swapped the count and offset registers).

struct BfmePod148
{
	int m_words[37];
};

#include <vector>

namespace _STL
{
	// Bind push_back to the rowed worker.
	template <> void vector<BfmePod148, allocator<BfmePod148> >::push_back(const BfmePod148 &value);
}

#include "../../../../../reference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib/ascii_string.h"

typedef unsigned int UnsignedInt;
typedef _STL::vector<AsciiString> AsciiStringVector;

struct BfmeAttributeBits
{
	UnsignedInt m_values[7];	// BitFlags<218>
};

class Rva00360F55
{
public:
	Rva00360F55();
	~Rva00360F55();
	bool rva00360E64(const Rva00360F55 &other);

	AsciiStringVector m_names;			// +0x00
	AsciiStringVector m_values;			// +0x0C
	AsciiStringVector m_lists[4];		// +0x18
	BfmeAttributeBits m_firstPlain;		// +0x48
	BfmeAttributeBits m_secondPlain;	// +0x64
	UnsignedInt m_kind;					// +0x80
	UnsignedInt m_relationship;			// +0x84
	bool m_enabled;						// +0x88
	unsigned char m_pad89[3];
	UnsignedInt m_useCount;				// +0x8C
	UnsignedInt m_alignment;			// +0x90
};

extern unsigned char *g_validityBegin;
extern unsigned char *g_validityEnd;

// ?Rva00361790@@YAHPAVRva00360F55@@@Z
int Rva00361790(Rva00360F55 *record)
{
	int count = (g_validityEnd - g_validityBegin) / (int)sizeof(Rva00360F55);
	for (int index = 0; index < count; ++index)
	{
		if (((Rva00360F55 *)g_validityBegin)[index].rva00360E64(*record))
		{
			((Rva00360F55 *)g_validityBegin)[index].m_useCount++;
			return index;
		}
	}
	record->m_useCount = 1;
	((_STL::vector<BfmePod148, _STL::allocator<BfmePod148> > *)&g_validityBegin)->push_back((const BfmePod148 &)*record);
	count = (g_validityEnd - g_validityBegin) / (int)sizeof(Rva00360F55);
	return count - 1;
}
