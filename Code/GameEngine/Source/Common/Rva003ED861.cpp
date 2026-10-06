// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Target 0x003ED861 is a 24-byte boundary. Its calls land at 0x003ED7A2 and
// 0x0031BD55; the latter is the matched STLport vector<void*>::erase body.
// The BFME1 Bfme5DestroyThenClear donor has the same 3-pointer clear shape, but
// does not establish the target owner's type. Keep the wrapper address-derived.
// The first call uses the existing bfmeClearMembers pin at 0x003ED7A2 only as
// its call-site spelling; this does not assert that it is the donor helper.

#include <vector>

class LGA_MemberObj;
void bfmeClearMembers(LGA_MemberObj *map);

struct Rva003ED861
{
	void **m_00;
	void **m_04;
	void **m_08;
	void method();
};

void Rva003ED861::method()
{
	bfmeClearMembers((LGA_MemberObj *)this);
	((_STL::vector<void *> *)this)->erase(m_00, m_04);
}
