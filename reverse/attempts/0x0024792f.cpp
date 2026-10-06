// ?rva0024792F@GameLogic@@QAEXABVAsciiString@@HH@Z
// partial score=0.95 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// ?rva0024792F@GameLogic@@QAEXABVAsciiString@@HH@Z @0x0024792F 79B: map insert setter under GameLogic+0x24. Evidence: prev 0x00247378 GameLogic ends at this start plus same +0x24 map as sibling 0x00246F8E plus rowed map subscript 0x00246FF6 plus pinned Rva0023FC23 plus rowed releaseBuffer 0x00036410.
#include "ascii_string.h"
#include <map>
struct TreeKey00242F5E { int m_id; AsciiString m_name; };
struct TreeOpaqueMapped242F5E { unsigned int m_bits; };
struct Out00524477 { int m_0; void *m_4; inline ~Out00524477() { ((AsciiString *)&m_4)->~AsciiString(); } };
int __cdecl Rva0023FC23(Out00524477 *out, int *a1, int a2) throw();
bool operator<(const TreeKey00242F5E &a, const TreeKey00242F5E &b);
class GameLogic
{
public:
	void rva0024792F(const AsciiString &setName, int slot, int value);
private:
	unsigned char m_pad00[0x24];
	_STL::map<TreeKey00242F5E, TreeOpaqueMapped242F5E, _STL::less<TreeKey00242F5E>, _STL::allocator<_STL::pair<const TreeKey00242F5E, TreeOpaqueMapped242F5E> > > m_map24;
};
void GameLogic::rva0024792F(const AsciiString &setName, int slot, int value)
{
	Out00524477 out;
	int r = Rva0023FC23(&out, &slot, (int)&setName);
	m_map24[*(const TreeKey00242F5E *)r].m_bits = (unsigned int)value;
}
