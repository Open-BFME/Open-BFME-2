// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ?Rva002CF9DCCreate@@YGPAXPBU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@Z @0x002CF9DC 37B.
// 12-byte node create: allocates 0xC via rowed byte allocator 0x000307F0,
// zeroes dword at +0, constructs the pair at +4 via rowed dup 0x002CF954
// (object-symbol _Construct<pair<AsciiString,NoCaseTreeValue4>>), returns
// the block, ret 4. Same dup as the NoCase _M_create_node 0x002CFA8E but
// 0xC node (4-byte header + 8-byte pair). Caller at 0x002CFB77 unblocks 0x002CFB4C.
#include <map>
#include <set>
#include <list>
#include <vector>
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}

#include "../../../../GameEngine/Include/Common/NoCaseTreeValue4.h"
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

void __cdecl Rva002CF954Construct(void *dest, const void *source);

void *__stdcall Rva002CF9DCCreate(const _STL::pair<const AsciiString, NoCaseTreeValue4> *src)
{
	char *block = _STL::allocator<char>::allocate(0xC, 0);
	*(int *)block = 0;
	Rva002CF954Construct((_STL::pair<const AsciiString, NoCaseTreeValue4> *)(block + 4), src);
	return block;
}

#include "../../../../GameEngine/Include/GameLogic/Rva000427195.h"

// ICF-folded twin of Rva002CF9DCCreate above (same 37 bytes at 0x002CF9DC):
// the member spelling ignores its receiver, so its stack frame matches the
// stdcall spelling exactly, including the callee-cleaned return.
void *Rva000427195::createNode(const _STL::pair<const AsciiString, NoCaseTreeValue4> *src)
{
	char *block = _STL::allocator<char>::allocate(0xC, 0);
	*(int *)block = 0;
	Rva002CF954Construct((_STL::pair<const AsciiString, NoCaseTreeValue4> *)(block + 4), src);
	return block;
}
