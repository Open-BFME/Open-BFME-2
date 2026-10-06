// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Rva00339A8DCopy@@YAPAV?$vector@HV?$allocator@H@_STL@@@_STL@@PAV12@00PAXH@Z @0x00339A8D 50B forward copy via rowed 0x0021C21B stride 0xC with dummy trailing args.
// Retail: push ebp / mov ebp esp / mov eax [ebp+c] / sub eax [ebp+8] / push 0xc / cdq / pop ecx / idiv ecx / test eax eax / jle / push esi / mov esi eax / push [ebp+8] / mov ecx [ebp+0x10] / call 0x21C21B / add [ebp+8] 0xc / add [ebp+0x10] 0xc / dec esi / jne / pop esi / mov eax [ebp+0x10] / pop ebp / ret.
// Target facts: __cdecl (first last dest tag extra) -> dest; count=(last-first)/12 via idiv 0xC; loop *dest=*first via rowed vector assign ++first ++dest; tag/extra dead for 5-arg callers with add esp 0x14; caller 0x001FFC38 pushes 5.
// Callers: 0x001FFC38 wrapper pushes 5; callees: 0x0021C21B vector<int> assign (int pin; ScienceType and int are both 4B PODs with identical codegen per rowed dup_0021c21b).
// Precedent: Rva0014FA90Copy 50B same shape stride 0x4C with dummy-tag 5-arg form; Rva0039BAA0Copy 50B stride 0x14; PlayerScienceAssign uses int spelling of folded assign.
// Not established: owning class identity; honest Rva address-derived free-function name.

namespace _STL
{

template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
public:
	typedef Type *pointer;

	vector &operator=(const vector &x);

private:
	pointer m_start;
	pointer m_finish;
	pointer m_endOfStorage;
};

}

typedef _STL::vector<int, _STL::allocator<int> > SciVec;

SciVec *__cdecl Rva00339A8DCopy(SciVec *first, SciVec *last, SciVec *dest, void *tag, int extra)
{
	int n = last - first;
	if (n <= 0)
		return dest;
	for (int i = n; i != 0; --i) {
		*dest = *first;
		++first;
		++dest;
	}
	return dest;
}

// ?Rva00339ABFCopy@@YAPAV?$vector@HV?$allocator@H@_STL@@@_STL@@PAV12@00PAXH@Z @0x00339ABF 50B copy-backward via rowed 0x0021C21B stride 0xC with dummy trailing args.
// Retail: push ebp / mov ebp esp / mov eax [ebp+c] / sub eax [ebp+8] / push 0xc / cdq / pop ecx / idiv ecx / test eax eax / jle / push esi / mov esi eax / sub [ebp+c] 0xc / sub [ebp+0x10] 0xc / push [ebp+c] / mov ecx [ebp+0x10] / call 0x21C21B / dec esi / jne / pop esi / mov eax [ebp+0x10] / pop ebp / ret.
// Target facts: __cdecl (first last destEnd tag extra) -> destStart; count=(last-first)/12 via idiv 0xC; loop *--dest=*--last via rowed vector assign --last --dest; tag/extra dead for 5-arg callers with add esp 0x14; caller 0x00339D57 pushes 5.
// Callers: 0x00339D57 wrapper pushes 5; callees: 0x0021C21B vector<int> assign (int spelling of folded ScienceType assign).
// Precedent: Rva00339A8DCopy 50B forward same stride/callex in this TU; honest Rva address-derived free-function name.

SciVec *__cdecl Rva00339ABFCopy(SciVec *first, SciVec *last, SciVec *dest, void *tag, int extra)
{
	int n = last - first;
	if (n <= 0)
		return dest;
	for (int i = n; i != 0; --i) {
		--last;
		--dest;
		*dest = *last;
	}
	return dest;
}

// ?Rva00339D57Copy@@YAPAV?$vector@HV?$allocator@H@_STL@@@_STL@@PAV12@00PAX@Z @0x00339D57 29B copy-backward wrapper via rowed 0x00339ABF stride 0xC with dummy trailing args.
// Retail: push ebp / mov ebp esp / push ecx / push 0 / lea eax [ebp-1] / push eax / push [ebp+0x10] / push [ebp+0xc] / push [ebp+0x8] / call 0x339ABF / add esp 0x14 / leave / ret.
// Target facts: __cdecl (first last dest tag) -> dest; forwards first three to rowed Rva00339ABFCopy with fresh 1-byte tag at [ebp-1] and extra 0; outer tag at [ebp+0x14] unused; caller 0x0033A05E pushes 4.
// Callers: 0x0033A0D8 in 0x0033A05E pushes 4; callees: rowed 0x00339ABF backward copy.
// Precedent: twin 0x001FFC38 same 29B shape calling forward 0x00339A8D; honest Rva address-derived free-function name.

SciVec *__cdecl Rva00339D57Copy(SciVec *first, SciVec *last, SciVec *dest, void *tag)
{
	char tmp;
	return Rva00339ABFCopy(first, last, dest, &tmp, 0);
}
