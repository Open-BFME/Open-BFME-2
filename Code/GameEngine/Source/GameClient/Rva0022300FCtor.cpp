// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0022300F@@QAE@XZ @0x002231E7 63B
// Default ctor over vector at +0 via rowed _Vector_base E16 0x00211E58 and wide string at +0xC zeroed then rowed reserve ModuleData 0x002B712E with 1.
// Evidence: caller 0x00224BDB builds at -0x20 then passes to 0x002233F0 and destroys via ??1Rva0022300F; dtor layout vector +0 wide +0xC; copy 0x00223226 same layout.
#include <vector>
#include "unicode_string.h"

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

class ModuleData;

class Rva0022300F
{
public:
	Rva0022300F();
private:
	_STL::vector<BfmeE16> m_vec;
	UnicodeString m_str;
};

Rva0022300F::Rva0022300F() : m_vec(_STL::allocator<BfmeE16>()), m_str()
{
	((_STL::vector<const ModuleData *> &)m_vec).reserve(1);
}
