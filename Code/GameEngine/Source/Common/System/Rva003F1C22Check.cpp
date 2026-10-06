// cl: /DNDEBUG /MD /GX-
// ?rva003F1C22@Rva003F1C22@@QAE_NPAVCreateAHeroData@@PAH@Z, retail 0x003F1C22, 52 bytes.
class CreateAHeroData;

class Rva003F11EC
{
public:
	int rva003F11EC(CreateAHeroData *val);
};

struct Rva003F1C22Vec4
{
	int *begin;
	int *end;
};

class Rva003F1C22
{
public:
	bool rva003F1C22(CreateAHeroData *hero, int *out);
private:
	char m_pad14[0x14];
	Rva003F11EC m_14;
	char m_padVec[0x170 - 0x14 - 1];
	Rva003F1C22Vec4 m_vec170;
};

bool Rva003F1C22::rva003F1C22(CreateAHeroData *hero, int *out)
{
	int result = ((Rva003F11EC *)((char *)this + 0x14))->rva003F11EC(hero);
	if (out)
		*out = result;
	Rva003F1C22Vec4 *v = &m_vec170;
	return result != (v->end - v->begin);
}
