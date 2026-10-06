// ?rva004C4430@Rva004C4430@@QAEX_N@Z
// partial score=0.97 date=2026-10-03
// ?rva004C4430@Rva004C4430@@QAEX_N@Z
// partial score=0.97 date=2026-10-03
// cl: /DNDEBUG /MD
// ?rva004C4430@Rva004C4430@@QAEX_N@Z @0x004C4430 77B: chain from 0x00492FC2
// Evidence: thiscall bool (cmp byte [ebp+8] ret 4); +0x24 gate then float from [this-0xC]+0x7C
// zeroed when arg!=0 via movss/xorps; Object at [this-8] -> getControllingPlayer (row 0x0028AFA9)
// -> Rva002A9E25FloatField::set(float) (row 0x002A9E25) with early push/fstp reuse; tail
// mov ecx,esi -> Rva00492FC2::rva00492FC2(bool) (row 0x00492FC2). Negative offsets via explicit
// byte casts (same bytes as MI second-base); ScavengerSpecialPower neighbours give TU/flags.

class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Rva002A9E25FloatField
{
public:
	void set(float value);
};

struct FloatHolder004C4430
{
	char m_pad[0x7C];
	float m_7C;
};

class Rva00492FC2
{
public:
	void rva00492FC2(bool flag);
};

class Rva004C4430
{
public:
	void rva004C4430(bool flag);

private:
	char m_pad[0x24];
	unsigned char m_24;
};

void Rva004C4430::rva004C4430(bool flag)
{
	if (m_24 != 0) {
		float f = (*(FloatHolder004C4430 **)((char *)this - 12))->m_7C;
		if (flag != 0)
			f = 0.0f;
		Object *obj = *(Object **)((char *)this - 8);
		((Rva002A9E25FloatField *)obj->getControllingPlayer())->set(f);
	}
	((Rva00492FC2 *)this)->rva00492FC2(flag);
}
