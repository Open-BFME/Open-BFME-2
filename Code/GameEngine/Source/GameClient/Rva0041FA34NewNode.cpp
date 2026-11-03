// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ?rva0041FA34@Rva0041FA34@@QAEPAXPBX@Z @0x0041FA34 37B
// Eva hashtable _M_new_node-style allocator for 12-byte node (4 next + 8 pair).
// Evidence: caller at 0x0041FAD8 passes this in ecx plus one AsciiString-keyed
// arg; allocate 0x000307F0 with (0xc, 0) then dup pair<const AsciiString,
// NoCaseTreeValue4> at 0x0041FA07 (twin of rowed 0x000A7849 via rowed pair
// copy 0x00466EA7); unlocks 0x0041FA92. Shape follows Rva002230FFNewNode at
// 0x002230FF. Private minimal AsciiString keeps pair layout; shared header
// inlines the copy and fails the gate.
#define _STLP_NO_EXCEPTIONS 1
#include <memory>

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

#include "../../Include/Common/NoCaseTreeValue4.h"

void __cdecl Rva0041FA07Construct(void *dest, const void *source);

struct HashtableNode
{
	void *_M_next;
	_STL::pair<const AsciiString, NoCaseTreeValue4> _M_val;
};

class Rva0041FA34
{
public:
	void *rva0041FA34(const void *obj);
};

void *Rva0041FA34::rva0041FA34(const void *obj)
{
	HashtableNode *node = (HashtableNode *)_STL::allocator<char>().allocate(12, 0);
	node->_M_next = 0;
	Rva0041FA07Construct(&node->_M_val, (const _STL::pair<const AsciiString, NoCaseTreeValue4> *)obj);
	return node;
}
