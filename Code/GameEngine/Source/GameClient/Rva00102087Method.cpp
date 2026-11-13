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
// Suppress this TU's non-retail copy of ??$__copy@PBUBfmeStringRecord00111ACF@@PAU1@H@_STL@@YAPAUBfmeStringRecord00111ACF@@PBU1@0P:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeStringRecord00111ACF;
namespace _STL { template <> BfmeStringRecord00111ACF * __copy<BfmeStringRecord00111ACF const *,BfmeStringRecord00111ACF *,int>(BfmeStringRecord00111ACF const *,BfmeStringRecord00111ACF const *,BfmeStringRecord00111ACF *,random_access_iterator_tag const &,int *); }

struct BfmeStringRecord00111ACF
{
	char m_unported[28];
};

// Suppress this TU's non-retail copy of ??$_Destroy@PAUEvaMessageInfo@@@_STL@@YAXPAUEvaMessageInfo@@0@Z
// (it called the undefined ??1EvaMessageInfo): EvaMessageVectorDtor.cpp emits
// retail's 0x000AFF52 copy. Plain declaration-only form (no __imp_).
struct EvaMessageInfo;
namespace _STL { template <> void _Destroy<EvaMessageInfo *>(EvaMessageInfo *, EvaMessageInfo *); }

struct EvaMessageInfo
{
	char m_unported[28];
	EvaMessageInfo();
	EvaMessageInfo(const EvaMessageInfo &);
	~EvaMessageInfo();
	EvaMessageInfo &operator=(const EvaMessageInfo &);
};

#include "../../Include/Common/Rva00102087.h"

EvaMessageInfo *Rva00102087::rva00102087(EvaMessageInfo *evaMessageInfo, EvaMessageInfo *b)
{
	_STL::__false_type f;
	EvaMessageInfo *res = (EvaMessageInfo *)_STL::__copy_ptrs(
		(const BfmeStringRecord00111ACF *)b,
		(const BfmeStringRecord00111ACF *)m_04,
		(BfmeStringRecord00111ACF *)evaMessageInfo,
		f);
	_STL::_Destroy(res, m_04);
	m_04 = res;
	return evaMessageInfo;
}
