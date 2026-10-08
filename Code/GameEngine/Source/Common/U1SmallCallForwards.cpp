// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// A guarded call on an indexed element, 37 bytes at retail 0x001F8883:
//
//     push ebp / mov ebp,esp
//     mov eax,[ebp+0x14] / cmp eax,[ebp+0x18] / je out
//     mov ecx,[ebp+0x1c] / lea eax,[ecx+eax*4]
//     push eax / push [ebp+0x10] / push [ebp+0xC] / push [ebp+8]
//     call <REL32> / add esp,0x10
//     out: pop ebp / ret
//
// A bare `ret` with ecx dead on entry and reads out to [ebp+0x1C]: __cdecl
// with six parameters.  The FOURTH and FIFTH are compared to each other and
// nothing else is done with them, so they are the same scalar type; the SIXTH
// is scaled by the fourth times FOUR, which fixes the element width at four
// bytes and makes the sixth a pointer to them.  What the callee receives is
// the first three parameters unchanged plus that computed ADDRESS -- not a
// value loaded from it -- so the source hands over `array + index`.  The
// callee cleans sixteen bytes, so it is __cdecl with four parameters.
//
// IDENTITY IS NOT RECOVERED.  The name is derived from the row's address.
//
// This TU holds the one row the BFME 1 donor sweep placed; the donor's other
// two definitions are omitted.

// The callee is retail's already-matched free ostream write at 0x001F82AB,
// ?Rva001F82ABWrite@@YAXAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@IPBDPAPBD@Z
// (Code/Libraries/Source/WWVegas/WWLib/Rva001F82ABWrite.cpp).  Retail pushes
// this body's first three parameters unchanged and the computed element
// address fourth, so the callee's four parameters ARE this body's four pushed
// dwords; only the last is reinterpreted, from `void **` to the
// `char const **` the rowed body declares for its INI value.
namespace _STL
{
template <class C> class char_traits;
template <class C, class T> class basic_ostream;
}
extern void __cdecl Rva001F82ABWrite( _STL::basic_ostream<char, _STL::char_traits<char> > &out, unsigned int b, const char *c, const char **element );

void u1Range_005C8320( void *a, void *b, void *c, int index, int end, void **array )
{
	if ( index != end )
		Rva001F82ABWrite( *(_STL::basic_ostream<char, _STL::char_traits<char> > *)a, (unsigned int)b, (const char *)c, (const char **)(array + index) );
}