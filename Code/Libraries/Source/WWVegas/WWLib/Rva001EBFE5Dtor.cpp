// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
//
// ??1Rva001EBFE5@@UAE@XZ, retail 0x001EBFE5, 87 bytes.
// Virtual dtor: destroys two vector<BfmeAssignRecord172> members at +0xA4
// and +0xB4 via rowed 0x001EB945, frees pointer at +0x14 via rowed _free
// 0x00030830, then restores Snapshot base vtable 0x00BBB554. Evidence:
// retail vptr store, twin vector-dtor calls, free-if-nonnull, EH states
// 2/1/0 with __EH_prolog; caller 0x001EBFC9 is the ??_G deleting wrapper.
#include <vector>
#include "Common/Snapshot.h"

extern "C" void __cdecl free(void *ptr);

struct AsciiStringLike
{
	char *m_str;
	~AsciiStringLike()
	{
		if (m_str)
			free(m_str);
	}
};

struct BfmeAssignRecord172
{
	~BfmeAssignRecord172();
};

class __declspec(novtable) Rva001EBFE5 : public Snapshot
{
public:
	virtual ~Rva001EBFE5();

private:
	unsigned char m_pad04[0x14 - 0x4];
	AsciiStringLike m_holder14;
	unsigned char m_pad18[0xA4 - (0x14 + 4)];
	_STL::vector<BfmeAssignRecord172> m_vecA4;
	unsigned char m_gapB0[0xB4 - (0xA4 + 12)];
	_STL::vector<BfmeAssignRecord172> m_vecB4;
};

Rva001EBFE5::~Rva001EBFE5()
{
}
