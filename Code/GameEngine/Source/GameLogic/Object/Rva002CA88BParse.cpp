// cl: /DNDEBUG /MD /EHsc
// ?Rva002CA88BParse@@YAXPAX0@Z @0x002CA88B 93B
// Lazy-init Rva00235A21 (0x210) at parent +0xE0 via new plus ctor 0x00235A21
// then parseWeaponBonusSet 0x002C971E. Evidence: chain lane calls just-landed
// ctor; unblocks 0x002CA88B? actually self; callers none; EH_prolog.
class INI;

struct Rva00235A0EElem002CA
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
};

class Rva00235A21
{
public:
	Rva00235A21();
private:
	Rva00235A0EElem002CA m_arr[22];
};

struct Parent002CA88B
{
	char m_pad[0xE0];
	Rva00235A21 *m_E0;
};

class WeaponBonusSet
{
public:
	void parseWeaponBonusSet(INI *ini);
};

void *__cdecl operator new(unsigned int size);

void __cdecl Rva002CA88BParse(void *iniArg, void *parentArg)
{
	INI *ini = (INI *)iniArg;
	Parent002CA88B *parent = (Parent002CA88B *)parentArg;
	if (parent->m_E0 == 0)
	{
		Rva00235A21 *p = new Rva00235A21();
		parent->m_E0 = p;
	}
	((WeaponBonusSet *)parent->m_E0)->parseWeaponBonusSet(ini);
}
