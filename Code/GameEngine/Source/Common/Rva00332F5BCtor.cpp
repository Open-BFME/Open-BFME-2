// cl: /O1 /DNDEBUG /MD
// ??0Rva00332F5B@@QAE@ABVWeaponTemplateSetHead@@0@Z @0x00332F5B 38B
// retail 0x00332F5B 38 bytes unlock ctor UnicodeString at +0 plus two WeaponTemplateSetHead at +4 and +0x50
// via rowed UnicodeString default 0x00326BE6 and rowed WeaponTemplateSetHead copy 0x00045455 caller 0x00336D9B
// neighbours prev 0x00332F29 stlport vector and next 0x00333027 Disp8 getters

class UnicodeString
{
public:
	UnicodeString();
	void *m_text;
};

class WeaponTemplateSetHead
{
public:
	WeaponTemplateSetHead(const WeaponTemplateSetHead &that);
private:
	char m_data[76];
};

class Rva00332F5B
{
public:
	Rva00332F5B(const WeaponTemplateSetHead &a, const WeaponTemplateSetHead &b);
	int rva00332F81(const Rva00332F5B &other) const;
private:
	UnicodeString m_uni;
	WeaponTemplateSetHead m_a;
	WeaponTemplateSetHead m_b;
};

Rva00332F5B::Rva00332F5B(const WeaponTemplateSetHead &a, const WeaponTemplateSetHead &b) : m_uni(), m_a(a), m_b(b)
{
}

bool __cdecl Rva00045473Equal(const void *a, const void *b);

int Rva00332F5B::rva00332F81(const Rva00332F5B &other) const
{
	if (m_uni.m_text == other.m_uni.m_text)
	{
		if (Rva00045473Equal(&m_a, &other.m_a))
		{
			if (Rva00045473Equal(&m_b, &other.m_b))
				return true;
		}
	}
	return false;
}
