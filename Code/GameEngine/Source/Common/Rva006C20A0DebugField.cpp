// cl: /DNDEBUG /MD
//
// ?rva006C20A0@GeneralAllocatorDebug@@QAEPAXPAXIGPBXI@Z @ 0x006C20A0 261B, ret 0x14 (Ghidra 254 stops before the null-return epilogue)
//
// Writes one tagged debug-data field into a debug block: (block, block
// length, field id, data, data length). The block's last 16-bit word is the
// size of the field area, which grows down from it; each field is its data
// followed by a 16-bit id and a 16-bit data size. Walking down from the end,
// a field with the same id is overwritten in place when the data fits (the
// rest of the field zeroed) and its data address returned; when it does not
// fit the field is zeroed and null returned. Without a match, a new field is
// appended below the existing ones if the block has room for the data and
// its four-byte header, and the area size word grows by both; otherwise null.
// Null data only reserves the field. `this` is unused.
//
// Evidence: retail body, and WorldBuilder's unoptimized twin at 0x0070E670,
// whose asserts ("nDebugDataSize <= nDebugBlockLength", "dataLength <=
// nFieldSize", "pPosition == pPositionEnd", "((pPosition -
// kDebugRecordOverheadSize) - dataLength) >= pDebugBlock") give the control
// flow and the variable roles. The name is address-derived.

#include <string.h>

class GeneralAllocatorDebug
{
public:
	void *rva006C20A0(void *block, unsigned length, unsigned short id, const void *data, unsigned dataLength);
	static unsigned rva006C16D0(const void *chunk);
	void rva006C1710(int allocationFunction, int freeFunction, int allocationContext);
	int rva006C1770(short option);
	bool Init(void *coreMemory, unsigned int size, bool freeCore, void *trimCore, void *coreFreeFunction, void *coreFreeContext);
};

void *GeneralAllocatorDebug::rva006C20A0(void *block, unsigned length, unsigned short id, const void *data, unsigned dataLength)
{
	char *position = (char *)block + length - 2;
	unsigned short *sizeWord = (unsigned short *)position;
	unsigned short dataSize = *(unsigned short *)position;
	const char *positionEnd = position - dataSize;

	while (position > positionEnd) {
		position -= 2;
		const unsigned short fieldSize = *(unsigned short *)position;
		position -= 2;
		const unsigned short fieldId = *(unsigned short *)position;
		position -= fieldSize;

		if (fieldId == id) {
			if (dataLength <= fieldSize) {
				if (data) {
					memcpy(position, data, dataLength);
					if (dataLength < fieldSize)
						memset(position + dataLength, 0, fieldSize - dataLength);
				}
				return position;
			}
			memset(position, 0, fieldSize);
			return 0;
		}
	}

	if (position - 4 - dataLength >= (char *)block) {
		position -= 2;
		*(unsigned short *)position = (unsigned short)dataLength;
		position -= 2;
		*(unsigned short *)position = id;
		position -= dataLength;
		if (data)
			memcpy(position, data, dataLength);
		dataSize = (unsigned short)(dataSize + dataLength + 4);
		*sizeWord = dataSize;
		return position;
	}
	return 0;
}

// Three Ghidra-unlisted debug-allocator leaves near 0x006C1700, address-named
// with only the offsets they touch (no layout is claimed):
// 0x006C16D0 (26B, static): a chunk's usable size from its +4 header word,
// masked to 0x7FFFFFF8, plus 4 unless the mapped bit (2) is set.
unsigned GeneralAllocatorDebug::rva006C16D0(const void *chunk)
{
	unsigned header = ((const unsigned *)chunk)[1];
	if (!(header & 2))
		return (header & 0x7FFFFFF8) + 4;
	return header & 0x7FFFFFF8;
}

// 0x006C1710 (24B): stores three values at +0x14/+0x18/+0x1C.
void GeneralAllocatorDebug::rva006C1710(int allocationFunction, int freeFunction, int allocationContext)
{
	int *fields = (int *)((char *)this + 0x14);
	fields[0] = allocationFunction;
	fields[1] = freeFunction;
	fields[2] = allocationContext;
}

// 0x006C1770 (22B): option 11 reads as 0, any other as the +0x67C word.
int GeneralAllocatorDebug::rva006C1770(short option)
{
	if (option == 11)
		return 0;
	return *(int *)((char *)this + 0x67C);
}

// 0x006C1730 (17B): an address bucket, the pointer's 8-byte granule modulo
// the +8 bucket count. 0x006C1750 (19B, ecx unused; an unsigned non-zero test): the 4-byte-offset body
// of a non-null block, else null. 0x006C1A80 (26B): store the given owner at
// +0x678, or this object itself when none is given. Owners unrecovered; the
// spellings are address-derived.
class Rva006C1730
{
public:
	unsigned int rva006C1730(unsigned int address) const;
private:
	int m_00;
	int m_04;
	unsigned int m_bucketCount;
};

unsigned int Rva006C1730::rva006C1730(unsigned int address) const
{
	return (address >> 3) % m_bucketCount;
}

class Rva006C1750
{
public:
	void *rva006C1750(void *block);
};

void *Rva006C1750::rva006C1750(void *block)
{
	return (unsigned int)block > 0 ? (char *)block + 4 : 0;
}

class Rva006C1A80
{
public:
	void rva006C1A80(void *owner);
private:
	char m_pad000[0x678];
	void *m_owner;
};

void Rva006C1A80::rva006C1A80(void *owner)
{
	if (owner)
		m_owner = owner;
	else
		m_owner = this;
}

// 0x006C19F0 (94B): the debug allocator's setup: the rowed base setup
// 0x00033700 with the same six arguments, then, the first time only, the
// +0x570 table (0x100 bytes) and the +0x670/+0x674 words cleared under the
// +0x510 once flag. The base result is returned. The table is cleared by an
// element loop (cl turns it into the retail rep stosd; a memset call orders
// the edi/ecx setup the other way). Address-derived name.
class Rva00033B90Allocator
{
public:
	bool rva00033700(void *a, unsigned int size, bool b, void *c, void *d, void *e);
};

struct Rva006C19F0State
{
	char m_pad000[0x510];
	bool m_initialized;					// +0x510
	char m_pad511[0x570 - 0x511];
	unsigned int m_table[0x40];			// +0x570
	int m_670;
	int m_674;
};

bool GeneralAllocatorDebug::Init(void *coreMemory, unsigned int size, bool freeCore, void *trimCore, void *coreFreeFunction, void *coreFreeContext)
{
	bool result = ((Rva00033B90Allocator *)this)->rva00033700(coreMemory, size, freeCore, trimCore, coreFreeFunction, coreFreeContext);
	Rva006C19F0State *state = (Rva006C19F0State *)this;
	if (!state->m_initialized)
	{
		state->m_initialized = true;
		for (int i = 0; i < 0x40; ++i)
			state->m_table[i] = 0;
		state->m_670 = 0;
		state->m_674 = 0;
	}
	return result;
}
