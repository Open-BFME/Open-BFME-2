// cl: /Oy- /MD
// ?rva005E8044@Rva005E8044@@QAEPAXPAX0@Z @0x005E8044 51B
// Vector range erase: copy [last finish) to pos via rowed 0x005E748D
// then destroy [newFinish finish) via rowed 0x005E7FB0, update m_finish, return pos.
// Same 51B shape as CameraMarker erase 0x0048D042: the 1-byte dummy tag
// would home at ebp+0xf, retail wants ebp+0xb (last byte of first arg),
// so pass (char*)&first+3 as the dummy (Rva004BA399EraseRange precedent)
// with /Oy- to keep the EBP frame frameless otherwise.
// m_finish at +4. Evidence: 4-push Forward then 2-push destroy, ret 8,
// callers 0x005E8188 0x005E84F5.
class Rva005E7198;
Rva005E7198 *__cdecl Rva005E748DForward(Rva005E7198 *first, Rva005E7198 *last, Rva005E7198 *dest, void *ignored);
struct Rva005E74AA;
void __cdecl Rva005E7FB0Forward(Rva005E74AA *first, Rva005E74AA *last);
struct Rva005E8044
{
	char m_pad[4];
	Rva005E7198 *m_finish;
	void *rva005E8044(void *first, void *last);
};

void *Rva005E8044::rva005E8044(void *first, void *last)
{
	Rva005E7198 *newFinish = Rva005E748DForward((Rva005E7198 *)last, m_finish, (Rva005E7198 *)first, (void *)((char *)&first + 3));
	Rva005E7FB0Forward((Rva005E74AA *)newFinish, (Rva005E74AA *)m_finish);
	m_finish = newFinish;
	return first;
}
