// cl: /MD
// ?rva006E34A0@Rva006E34A0@@QAEPAXI@Z, retail 0x006E34A0 (42B).
// Array-owner release plus sized self-free: frees the array at +0 through
// rowed Rva006CD460Free, then when the low flag bit is set frees this
// through the rowed freeBlock with size 0x14 and returns this.
// Evidence: own immediates call 0x006CD460 plus freeBlock 0x006DB270 size
// 0x14 via pool 0x00E176E8; ret 4 plus flag test proves thiscall taking
// unsigned int and returning the pointer; neighbours share /O2 /MD.
class Rva006DB270
{
public:
	void freeBlock(void *block, int blockSize);
};
extern Rva006DB270 *g_pChainBlockAllocator;
void __cdecl Rva006CD460Free(void *p);

struct Rva006E34A0
{
	void *m_arr;
	void *rva006E34A0(unsigned int flag);
};

void *Rva006E34A0::rva006E34A0(unsigned int flag)
{
	Rva006CD460Free(m_arr);
	if (flag & 1)
		g_pChainBlockAllocator->freeBlock(this, 0x14);
	return this;
}
