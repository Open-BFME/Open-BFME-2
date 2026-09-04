// cl: /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport

// The retail loop advances a deque iterator by a 20-byte value over 0x78-byte
// nodes and performs no destructor call; this is the trivial-payload overload
// of STLport's range __destroy.

#include <deque>

struct PodPayload20 { char m_body[20]; };

namespace _STL
{
template void __destroy<
	_Deque_iterator<PodPayload20,
		_Nonconst_traits<PodPayload20> >,
	PodPayload20>(
	_Deque_iterator<PodPayload20,
		_Nonconst_traits<PodPayload20> >,
	_Deque_iterator<PodPayload20,
		_Nonconst_traits<PodPayload20> >,
	PodPayload20 *);
}
