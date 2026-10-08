// ?rva0040A59B@Rva0040A59B@@QAEXXZ
// partial score=0.6 date=2026-10-08
// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?rva0040A59B@Rva0040A59B@@QAEXXZ @0x0040A59B 52B.
// Vector-shaped clear: when the flag byte at +0xC is set, the unrowed cdecl
// 0x0040A1AC (pinned by its REL32 at 0x0040A5AC) runs over (begin, end, false),
// then the whole range is erased through the matched range erase 0x0031BD55.
// Evidence: target only. The element type is a 4-byte proxy: the erase at
// 0x0031BD55 is the matched pointer-move row, so the names are address-derived
// and the element identity is unproven.
#include <vector>

struct Rva0040A59BFlag
{
	bool value;
};

class Rva0040A59B
{
public:
	void rva0040A59B();

private:
	float *m_begin;
	float *m_end;
	float *m_cap;
	unsigned char m_flag;
};

bool Rva0040A1ACFree(void **, void *, bool);

void Rva0040A59B::rva0040A59B()
{
	if (m_flag)
	{
		Rva0040A59BFlag done = {false};
		Rva0040A1ACFree((void **)m_begin, (void *)m_end, done.value);
	}
	((_STL::vector<float> *)this)->erase(m_begin, m_end);
}
