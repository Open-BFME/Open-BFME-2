// cl: /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?rva00102087@Rva00102087@@QAEPAUEvaMessageInfo@@PAU2@0@Z @0x00102087 51B.
// Unlock helper copying pointer range via rowed __copy_ptrs then destroying
// old range via pinned _Destroy and storing result to +4 returning first arg.
// Evidence: packet disassembly pushes match __copy_ptrs(b m_04 a false_type)
// returning res then _Destroy(res m_04); callees __copy_ptrs 0x00101F89
// _Destroy 0x000AFF52; callers 0x001021F1 0x00102258; unblocks 0x0010223B;
// prev Rva00102026Method next EvaMessageVectorAssign.
#include <vector>

struct BfmeStringRecord00111ACF
{
	char m_unported[28];
};

struct EvaMessageInfo
{
	char m_unported[28];
	EvaMessageInfo();
	EvaMessageInfo(const EvaMessageInfo &);
	~EvaMessageInfo();
	EvaMessageInfo &operator=(const EvaMessageInfo &);
};

class Rva00102087
{
public:
	EvaMessageInfo *rva00102087(EvaMessageInfo *a, EvaMessageInfo *b);
private:
	void *m_00;
	EvaMessageInfo *m_04;
};

EvaMessageInfo *Rva00102087::rva00102087(EvaMessageInfo *a, EvaMessageInfo *b)
{
	_STL::__false_type f;
	EvaMessageInfo *res = (EvaMessageInfo *)_STL::__copy_ptrs(
		(const BfmeStringRecord00111ACF *)b,
		(const BfmeStringRecord00111ACF *)m_04,
		(BfmeStringRecord00111ACF *)a,
		f);
	_STL::_Destroy(res, m_04);
	m_04 = res;
	return a;
}
