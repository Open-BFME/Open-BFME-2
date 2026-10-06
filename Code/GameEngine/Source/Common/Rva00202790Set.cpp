// cl: /DNDEBUG /MD
//
// ?rva00202790@Rva00202790@@QAEXH@Z @0x00202790 33B. Range-checked setter at
// +0x1770 for values 0..1 with change detection then rowed audio refresh.
// Evidence: retail mov edx,[esp+4] plus test edx edx jl plus cmp edx 2 jge
// plus lea eax [ecx+0x1770] plus cmp [eax] edx je plus mov [eax] edx plus
// call 0x002026B4 ?Rva002026B4Audio@@YAXXZ; callers 0x002027EA and 0x005194F6.
class Rva00202790
{
public:
	void rva00202790(int v);
	char m_pad[0x1770];
	int m_1770;
};

void __cdecl Rva002026B4Audio();

void Rva00202790::rva00202790(int v)
{
	if (v < 0 || v >= 2)
		return;
	if (m_1770 == v)
		return;
	m_1770 = v;
	Rva002026B4Audio();
}
