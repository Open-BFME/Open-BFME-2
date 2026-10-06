// cl: /MD
//
// ?rva002785FB@Drawable@@QAEX_N@Z retail 0x002785FB 49B Drawable bool setter +0x448
// true: Host 0x002783F6 with 0 then rowed Drawable::rva002784EB
// false: rowed Drawable::rva002743D7 then rowed Rva002714CA::rva002714CA
// LINK BONUS names this mangling; callers 0x0029577E 0x002957CB 0x003BA967.

class Drawable
{
public:
	void rva002784EB();
	void rva002743D7();
	void rva002785FB(bool v);
private:
	unsigned char m_pad00[0x448];
	unsigned char m_448; // +0x448
};

class Rva002783F6Host
{
public:
	void rva002783F6(int v);
};

class Rva002714CA
{
public:
	void rva002714CA();
};

void Drawable::rva002785FB(bool v)
{
	m_448 = v;
	if (v)
	{
		((Rva002783F6Host *)this)->rva002783F6(0);
		rva002784EB();
	}
	else
	{
		rva002743D7();
		((Rva002714CA *)this)->rva002714CA();
	}
}
