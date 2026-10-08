// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?rva0038BD70@Rva0038BDEEReceiver@@QAEXPAX@Z @0x0038BD70 126B: formats port at +0x90 via AsciiString sets room to closedplaying and starts game with flag true. Evidence: neighbour Rva0038BDEEInvoke same class string at +0xC4 flag at +0x49C; strings "%d" plus closedplaying plus empty g_Rva0107301CEmptyString; callees row format 0x38150 basic_string assign 0x1B790 peerStartGameA 0x69A780 releaseBuffer 0x36410.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <string>
#include "ascii_string.h"

typedef void *PEER;

extern "C" void peerStartGameA(PEER peer, const char *msg, int opt);

class Rva0038BDEEReceiver
{
public:
	void rva0038BD70(void *peer);
private:
	char m_pad00[0x90];
	int m_90;
	char m_pad94[0xC4 - 0x90 - 4];
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > m_C4;
	char m_pad1[0x49C - 0xC4 - 12];
	bool m_49C;
};

void Rva0038BDEEReceiver::rva0038BD70(void *peer)
{
	AsciiString tmp;
	tmp.format("%d", m_90);
	m_C4 = "closedplaying";
	peerStartGameA(peer, tmp.str(), 2);
	m_49C = true;
}
