// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva00102188@@UAE@XZ retail 0x00102188 54B
// Evidence: chain calls vector dtor 0x000B0254 at +0x14 then +0x04; caller deleting dtor 0x001021BE
#include <vector>
// Suppress this TU's non-retail copy of ??1?$_Vector_base@UEvaMessageInfo@@V?$allocator@UEvaMessageInfo@@@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct EvaMessageInfo;
namespace _STL { template <> _Vector_base<EvaMessageInfo,allocator<EvaMessageInfo> >::~_Vector_base(); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAUEvaMessageInfo@@@_STL@@YAXPAUEvaMessageInfo@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void _Destroy<EvaMessageInfo *>(EvaMessageInfo *, EvaMessageInfo *); }

class BfmeStringRecord00111ACF { public: ~BfmeStringRecord00111ACF(); };
struct EvaMessageInfo
{
	// Destruction is the rowed ??1BfmeStringRecord00111ACF, reached by a qualified call.
	__declspec(dllimport) __forceinline ~EvaMessageInfo() { ((BfmeStringRecord00111ACF *)this)->BfmeStringRecord00111ACF::~BfmeStringRecord00111ACF(); }
};

class __declspec(novtable) Rva00102188
{
public:
	virtual ~Rva00102188();
private:
	_STL::vector<EvaMessageInfo> m_04;
	char m_pad10[0x14 - (4 + 12)];
	_STL::vector<EvaMessageInfo> m_14;
};

Rva00102188::~Rva00102188()
{
}
