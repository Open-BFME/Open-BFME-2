// ?Rva00572C95Get@@YGHPAVThing@@PAX@Z
// partial score=0.98 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /MD
// ?Rva00572C95Get@@YGHPAVThing@@PAX@Z @0x00572C95 149B
// Tests the candidate object's two inhibit bits and two kind-of masks; the
// ignored second stdcall argument is retained from the direct caller.
template <int N>
struct BitFlags
{
	union
	{
		unsigned int words[7];
		unsigned char bytes[0x1c];
	} m_bits;
};

class Thing
{
public:
	bool isAnyKindOf(const BitFlags<239> &mask) const;

	char m_pad000[0x94];
	unsigned char m_flag94;
	char m_pad095[0x438 - 0x95];
	unsigned char m_flag438;
};

extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

int __stdcall Rva00572C95Get(Thing *thing, void *unused)
{
	BitFlags<239> mask1;
	BitFlags<239> mask2;
	unsigned int firstGroup = 0x10000000;
	unsigned int secondGroup = 0x20000000;
	memset(&mask1, 0, sizeof(mask1));
	memset(&mask2, 0, sizeof(mask2));
	mask2.m_bits.bytes[18] |= 0x40;
	mask2.m_bits.bytes[25] |= 8;
	mask2.m_bits.bytes[13] |= 1;
	mask1.m_bits.words[6] |= 4;
	mask2.m_bits.words[4] |= firstGroup;
	mask2.m_bits.words[1] |= firstGroup;
	mask2.m_bits.bytes[18] |= 0x10;
	mask2.m_bits.words[1] |= secondGroup;
	mask2.m_bits.words[5] |= secondGroup;
	mask2.m_bits.bytes[6] |= 4;
	if (thing == 0 || (thing->m_flag94 & 1) != 0 || (thing->m_flag438 & 1) != 0)
		return 0;
	if (thing->isAnyKindOf(mask1))
		return 0;
	int result;
	if (thing->isAnyKindOf(mask2))
		result = 0;
	else
		result = 1;
	return result;
}
