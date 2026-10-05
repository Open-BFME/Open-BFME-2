// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?invoke@Rva0038BDEEReceiver@@QAEXPAX@Z @0x0038BDEE 41B
// Evidence: called by matched PeerThreadClass::stopHostingAlready 0x0038D53B plus 6 more; callees rowed _peerStopGame 0x00699410 plus basic_string assign 0x0001B790 plus string openstaging 0x00819890; prev PeerResponseAssign next OwnedRecordDeque.
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

extern "C" void peerStopGame(void *peer);

class Rva0038BDEEReceiver
{
public:
	void invoke(void *peer);
private:
	char m_pad00[0xC4];
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > m_C4;
	char m_pad1[0x49C - 0xC4 - sizeof(_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >)];
	bool m_49C;
};

void Rva0038BDEEReceiver::invoke(void *peer)
{
	peerStopGame(peer);
	m_C4 = "openstaging";
	m_49C = false;
}
