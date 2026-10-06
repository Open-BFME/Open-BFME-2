// cl: /DNDEBUG /MD /GX-
// ?rva003F1093@Rva003F1093@@QAE_NPAVCreateAHeroData@@PAH@Z @0x003F1093 61B:
// __thiscall bool check: hero+0x1c must equal this else *out=2 false;
// hero+0x20 must be nonzero else *out=1 false; else *out=0 true.
// Caller 0x003F1CB6 passes esi and null out. Sibling of Rva003F1C22Check.
class CreateAHeroData;
class CreateAHeroData
{
public:
	char m_pad1C[0x1c];
	void *m_1C;
	int m_20;
};
class Rva003F1093
{
public:
	bool rva003F1093(CreateAHeroData *hero, int *out);
};
bool Rva003F1093::rva003F1093(CreateAHeroData *hero, int *out)
{
	if (hero->m_1C != this)
	{
		if (out)
			*out = 2;
		return false;
	}
	if (hero->m_20 == 0)
	{
		if (out)
			*out = 1;
		return false;
	}
	if (out)
		*out = 0;
	return true;
}
