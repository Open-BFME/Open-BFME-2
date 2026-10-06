// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??0Rva0022300F@@QAE@ABV0@@Z @0x00223226 61B
// Copy ctor over vector<unsigned> at +0 via rowed 0x002CFAB9 and wide string at +0xC via rowed StringBase<ushort> 0x00037050.
// Evidence: dtor 0x0022300F releases wide at +0xC then frees ptr at +0; caller 0x002233F0 builds AsciiString at +0 plus this at +4 like Rva0022304A; EH prolog with and [ebp-4] 0 matches two-member copy.
// ?rva00223226 via Rva0022300F copy; retail order vector then wide.
#include <vector>
#include "unicode_string.h"

class Rva0022300F
{
public:
	Rva0022300F(const Rva0022300F &o);
private:
	_STL::vector<unsigned int> m_vec;
	UnicodeString m_str;
};

Rva0022300F::Rva0022300F(const Rva0022300F &o) : m_vec(o.m_vec), m_str(o.m_str)
{
}
