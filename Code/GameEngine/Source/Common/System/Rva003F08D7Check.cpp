// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX-
// ?rva003F08D7@Rva003F08D7@@QAEHH@Z, retail 0x003F08D7, 23 bytes.
// Linkbody: caller 0x0020EF1E names it by this pin; 1 matched file waits on it.
// Callee pin ?rva003F083A@Rva003F1093@@QAEPAVCreateAHeroData@@PAX@Z; honest
// address names; CreateAHeroData m_20 at +0x20 per sibling Rva003F07E5Check.
class CreateAHeroData
{
public:
	char m_pad[0x20];
	int m_20;
};

class Rva003F1093
{
public:
	CreateAHeroData *rva003F083A(void *x);
};

class Rva003F08D7
{
public:
	int rva003F08D7(int x);
};

// ?rva003F08D7@Rva003F08D7@@QAEHH@Z
int Rva003F08D7::rva003F08D7(int x)
{
	CreateAHeroData *d = ((Rva003F1093 *)this)->rva003F083A((void *)x);
	if (d != 0)
		return d->m_20;
	return 0;
}
