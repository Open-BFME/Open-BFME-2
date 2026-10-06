// cl: /O1 /G7 /arch:SSE /EHs-c- /MD /Oy /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva003AFFBE@@YAXHHHHH@Z @0x003AFFBE 50B: __push_heap_aux for 12B Rva003B02F4Entry calling rowed __push_heap 0x003AFE48; evidence rowed callees and REL32 from 0x003B015D via 0x003B016D, LINK BONUS 1 file 25B
struct Rva003B02F4Entry
{
	float key;
	unsigned int a;
	unsigned int b;
};

struct Rva003B02F4Greater
{
};

namespace _STL
{
template <class _RI, class _D, class _T, class _C>
void __push_heap(_RI __first, _D __hole, _D __top, _T __val, _C __comp) throw();
}

void __cdecl rva003AFFBE(int a1, int a2, int a3, int a4, int a5)
{
	_STL::__push_heap((Rva003B02F4Entry *)a1, int(((Rva003B02F4Entry *)a2 - (Rva003B02F4Entry *)a1) - 1), 0, *(((Rva003B02F4Entry *)a2) - 1), *(Rva003B02F4Greater *)&a3);
}
