// cl: /DNDEBUG /MD /EHsc
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Small03eComGuard.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?check@Rva00958730Box@@QAEHPAX@Z 0x00176C90 (31B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
//
// Retail 0x00958730 validates its argument through _com_issue_error and
// reports whether the held pointer is null: a null argument returns the
// null-test directly, otherwise the 0x80004003 failure is raised first and
// the same null-test follows. The callee is the real comutil.h declaration
// (void __stdcall _com_issue_error(HRESULT) at the 0x00AFD540 pin), so the
// reference carries its defining name and links.
// IDENTITY IS NOT RECOVERED: the owner keeps its address token.
// comutil.h declares `void __stdcall _com_issue_error(HRESULT)`; the sweep
// comutil.h shim does not, so the declaration is repeated here under its
// exact defining spelling (?_com_issue_error@@YGXJ@Z).
extern void __stdcall _com_issue_error(long);

class Rva00958730Box
{
public:
	int check(void *arg);
	void *m_ptr;
};

int Rva00958730Box::check(void *arg)
{
	if (arg == 0)
		return m_ptr == 0;
	_com_issue_error((long)0x80004003);
	return m_ptr == 0;
}
