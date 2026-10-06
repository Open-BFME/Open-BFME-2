// cl: /Oy-
// ?rva0015068C@Rva0015068C@@QAEPAVRva0014F699@@PAV2@0@Z @0x0015068C 51B.
// Vector-like reassign: copies [first, m_04) into result through the rowed
// 3-arg ?Rva00150265Copy (0x00150265), destroys [newEnd, m_04) through the
// rowed ?Rva0014F8AEDestroy (0x0014F8AE), stores the new end and returns
// result. Evidence: chain lane, caller at 0x00150BBB. Owning class unproven,
// hence honest Rva names.
//
// The 4th argument retail pushes is a 1-byte tag address the 3-arg callee
// ignores, and the call is made through a 4-arg function-pointer type so the
// extra push and the batched `add esp,0x18` come out. Retail materialises that
// address as `lea eax,[ebp+0xb]`. The proven recipe is the one the matched
// stlport erase 0x002157DB and 0x002983DA use: address-OF a parameter and add a
// constant, not a value cast. `&result` is the constant stack address [ebp+8],
// so `&result + 3` folds straight to [ebp+0xb] with no register load. Writing
// `(char *)result + 3` (the value) instead makes cl copy result into a register
// and emits `lea reg,[reg+3]`, which is wrong. /Oy- keeps the ebp frame this
// addressing needs; without it cl uses a flat esp frame and the tag lands at
// [esp+0xf].

class Rva0014F699;
class Rva0014F3E7;
void __cdecl Rva00150265Copy(Rva0014F699 *first, Rva0014F699 *last, Rva0014F699 *result);
void __cdecl Rva0014F8AEDestroy(Rva0014F3E7 *first, Rva0014F3E7 *last);
class Rva0015068C
{
public:
	Rva0014F699 *rva0015068C(Rva0014F699 *result, Rva0014F699 *first);
private:
	int m_00;
	Rva0014F3E7 *m_04;
};
typedef Rva0014F699 *(__cdecl *Copy4Fn)(Rva0014F699 *first, Rva0014F699 *last, Rva0014F699 *result, void *tag);
Rva0014F699 *Rva0015068C::rva0015068C(Rva0014F699 *result, Rva0014F699 *first)
{
	Rva0014F3E7 *newEnd = (Rva0014F3E7 *)((Copy4Fn)Rva00150265Copy)(first, (Rva0014F699 *)m_04, result, (void *)(int)((char *)&result + 3));
	Rva0014F8AEDestroy(newEnd, m_04);
	m_04 = newEnd;
	return result;
}
