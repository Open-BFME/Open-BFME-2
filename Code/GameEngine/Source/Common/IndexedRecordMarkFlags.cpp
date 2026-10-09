// cl: -O1 -arch:SSE -G7 -DNDEBUG -MD
// BFME1 donor1399ad37d42ea52a63829e417c46a1ba9ed2cd20,
// game/GameEngine/Source/Common/IndexedListTailWalkers.cpp (two marker bodies).
// Target: this+0x1C is the initial index and this+0xC the record base. Each
// 20-byte record has its next index at+0 and a byte flag at+0xC. The native
// loop reloads the record base after each store and terminates at index-1.
// Mark body3B3ECB follows rowed deque decrement3B3EA8/35, then clear3B3EEA
// follows immediately; both close31-byte RET extents. Original owners and
// method names remain unknown, so both views use their actual target RVAs.
class Rva003B3ECBOwner
{
public:
	void rva003B3ECB();

private:
	char m_padding00[ 0x0C ];
	unsigned char *m_records;
	char m_padding10[ 0x0C ];
	int m_index;
};

// ?rva003B3ECB@Rva003B3ECBOwner@@QAEXXZ
void Rva003B3ECBOwner::rva003B3ECB()
{
	unsigned char mark = 1;
	int index = m_index;
	if (index != -1)
	{
		unsigned int p = (unsigned int)m_records;
		do
		{
			unsigned int i = (unsigned int)index * 20;
			*(unsigned char *)(i + p + 0x0C) = mark;
			p = (unsigned int)m_records;
			index = *(int *)(i + p);
		}
		while (index != -1);
	}
}

struct Rva003B3EEAOwner
{
	char m_padding00[ 0x0c ];
	unsigned int m_entries;
	char m_padding10[ 0x0c ];
	int m_index;

	void rva003B3EEA();
};

static __forceinline void rva003B3EEAClear(unsigned int offset,
	unsigned int pointer)
{
	*(unsigned char *)(offset + pointer) = 0;
}

static __forceinline int rva003B3EEARead(unsigned int offset,
	unsigned int pointer)
{
	return *(int *)(offset + pointer);
}

// ?rva003B3EEA@Rva003B3EEAOwner@@QAEXXZ
void Rva003B3EEAOwner::rva003B3EEA()
{
	int index = m_index;
	if (index != -1)
	{
		do
		{
			rva003B3EEAClear((unsigned int)(index * 20 + 0x0c),
				m_entries);
			index = rva003B3EEARead((unsigned int)(index * 20), m_entries);
		}
		while (index != -1);
	}
}

// Whole BF1 f98983a7d3 Common/Rva000BE720Arr.cpp supplies the clean
// this-based indexing guide; its two owner names share one placed body.
// Native300015..300021 is complete afterRET300014 and before a fresh
// entry300021: multiply stackword4 by20, add incomingECX, RET4. Only
// these32-bit address bits are established, not an original owner, element
// identity, signed index, payload, declaration, or complete array extent.
// ?elementAddressBits@Rva00300015@@QBEII@Z
struct Rva00300015
{
    unsigned int elementAddressBits(unsigned int index) const;
};
unsigned int Rva00300015::elementAddressBits(unsigned int index) const
{
    return reinterpret_cast<unsigned int>(this) + index * 20u;
}
