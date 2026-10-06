// cl: /DNDEBUG /MD
// ??$__uninitialized_copy@PAURva003F1EA8Elem@@PAU1@@_STL@@YAPAURva003F1EA8Elem@@PAU1@00ABU__false_type@0@@Z @0x003F1EA8 38B:
// _STL::__uninitialized_copy stride 12 via dup _Construct 0x003F1A5F called
// through dup cast per TreeKey00242F5EUninitCopy precedent so the gate
// resolves to the dup address. Callers 0x003F3277 0x003F35E3.
// Dedicated TU so the call stays external.
struct Rva003F1EA8Elem
{
	char _m[12];
public:
	Rva003F1EA8Elem(const Rva003F1EA8Elem &that);
};
void __cdecl dup_003F1A5F(void);
typedef void (__cdecl *Rva003F1EA8ConstructFn)(Rva003F1EA8Elem *, const Rva003F1EA8Elem &);
namespace _STL
{
struct __false_type {};
template <class InputIter, class ForwardIter>
ForwardIter __uninitialized_copy(InputIter first, InputIter last, ForwardIter result, const __false_type &)
{
	ForwardIter cur = result;
	for (; first != last; ++first, ++cur)
		((Rva003F1EA8ConstructFn)&dup_003F1A5F)(cur, *first);
	return cur;
}
}
template Rva003F1EA8Elem *_STL::__uninitialized_copy(Rva003F1EA8Elem *, Rva003F1EA8Elem *, Rva003F1EA8Elem *, const _STL::__false_type &);
