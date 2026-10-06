// cl: /MD /EHsc /DNDEBUG
// ?Rva002B359DSet@@YGXPAURva002B359DOuter@@_N@Z @0x002B359D 66B: __stdcall void(Outer*,bool) looping [+0x1B8,+0x1BC) calling rowed Rva00318C05::rva00318C05. Evidence: retail push esi mov esi,[esp+8] outer array sar je plus push [esp+0x10] mov ecx,[eax+edi*4] call rowed 0x00318C05 ret 8; caller at 0x002B3923; callee row Rva00318C05Set.cpp.
class Rva00318C05
{
public:
	void rva00318C05(bool v);
};

struct Rva002B359DInner
{
	char m_pad[0x1];
};

struct Rva002B359DOuter
{
	char m_pad[0x1B8];
	Rva00318C05 **m_begin;
	Rva00318C05 **m_end;
};

void __stdcall Rva002B359DSet(Rva002B359DOuter *o, bool v);

void __stdcall Rva002B359DSet(Rva002B359DOuter *o, bool v)
{
	for (unsigned i = 0; i < (unsigned)(o->m_end - o->m_begin); ++i) {
		Rva00318C05 *cur = o->m_begin[i];
		cur->rva00318C05(v);
	}
}
