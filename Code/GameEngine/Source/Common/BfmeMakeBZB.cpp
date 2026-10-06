// Target 0x001B6400 forwards bytes to bfmeAllocBlock at 0x001B63C0.
// Its allocator and native14B body differ from NameKeyGenerator::Bucket's
// donor operator new. Address-derived identity; original class is unknown.
// cl: /DNDEBUG /MD

extern "C" void *__cdecl memset(void *block, int value, unsigned int bytes);
#pragma intrinsic(memset)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class Rva001B6400Allocation
{
public:
	enum AllocationTag { Bucket_GLUE_NOT_IMPLEMENTED = 0 };
	static void *__cdecl operator new(unsigned int bytes, AllocationTag tag);
};

void __cdecl bfmeInitD70(void *self, void *src);

struct BfmeHolderE20
{
	unsigned char m_lead[0xC4];
	int m_flag;
};

// ?bfmeMakeBZB@@YAPAXPAX@Z
void *__cdecl bfmeMakeBZB(void *src)
{
	BfmeHolderE20 *self = (BfmeHolderE20 *)Rva001B6400Allocation::operator new(0xC8, Rva001B6400Allocation::Bucket_GLUE_NOT_IMPLEMENTED);
	void *result = 0;

	if (self)
	{
		memset(self, 0, 0xC8);
		bfmeInitD70(self, src);
		self->m_flag = 1;
		result = self;
	}

	return result;
}
