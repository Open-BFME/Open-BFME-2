// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva00421A57@Rva00421A57@@QAE_NH@Z @0x00421A57 45B
// Search pointer range [+0xC,+0x10) for element whose table has (v,0):
// for (p = m_begin; p != m_end; ++p) if ((*p)->bfmeHas1026(v, 0)) return true;
// return false. Evidence: unlock lane; caller at 0x00424FA1; callee pin
// ?bfmeHas1026@BfmeTab1026@@QAEDHH@Z; prev DistSquared shares flags.
class Object;
class Player;

struct Rva2225E0Filter
{
	bool accepts(Object *, Player *);
};

class Rva00421A57
{
public:
	bool rva00421A57(int v);
	char m_pad0[0x0c];
	Rva2225E0Filter **m_begin;
	Rva2225E0Filter **m_end;
};
bool Rva00421A57::rva00421A57(int v)
{
	for (Rva2225E0Filter **p = m_begin; p != m_end; ++p)
	{
		if ((*p)->accepts((Object *)v, (Player *)0))
			return true;
	}
	return false;
}
