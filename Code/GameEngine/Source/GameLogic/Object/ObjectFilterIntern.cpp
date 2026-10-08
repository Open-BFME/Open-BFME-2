// cl: /O1 /DNDEBUG /MD
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

namespace _STL
{
	template <class _Tp> class allocator
	{
	};
	template <class _Tp, class _Alloc> class vector
	{
	public:
		void push_back(const _Tp &value);
	};
}

class Rva00360F55
{
public:
	bool rva00360E64(const Rva00360F55 &other);

	char m_pad00[0x8C];
	int m_useCount;
	char m_pad90[0x94 - 0x90];
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
