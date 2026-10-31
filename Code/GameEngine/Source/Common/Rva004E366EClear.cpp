// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmecamera /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/GameEngine/Source/Common /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/LivingWorld
//
// ?rva004E366E@Rva004E366E@@QAEXXZ @ 0x004E366E (28B).
// Vector clear plus free: erases the BfmePod8 vector at +0 via rowed erase
// @0x003FA4DB then frees the start via rowed _free @0x00030830 when present.
// Frameless push esi shape. Callers at 0x004E3886 0x0052BBDA 0x0052CEFF.
// Honest-address name: owner unproven.

struct BfmePod8 { int a[2]; };

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>

// stlport
#include <vector>
namespace _STL { template <> __declspec(nothrow) BfmePod8 *vector<BfmePod8, allocator<BfmePod8> >::erase(BfmePod8 *, BfmePod8 *); }

#undef _CRTIMP

class Rva004E366E
{
public:
	void rva004E366E();

private:
	_STL::vector<BfmePod8> m_vec;
};

void Rva004E366E::rva004E366E()
{
	m_vec.erase(m_vec.begin(), m_vec.end());
	if (m_vec.begin())
		free(m_vec.begin());
}
