// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva004E364F@@QAE@XZ @ 0x004E364F (31B).
// Vector ctor plus clear: constructs the BfmePod8 vector at +0 via base
// then erases begin to end via rowed erase @0x003FA4DB. Frameless push
// ecx plus esi shape returns this. Caller at 0x004E3859 builds the
// ebp-0x20 EyeTower temp then initFromINI. Honest-address name.
#include <vector>
struct BfmePod8 { int a[2]; };
class Rva004E364F
{
public:
	Rva004E364F();
private:
	_STL::vector<BfmePod8> m_vec;
};

Rva004E364F::Rva004E364F()
{
	m_vec.erase(m_vec.begin(), m_vec.end());
}
