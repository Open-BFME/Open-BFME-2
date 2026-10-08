// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002B2C40@Rva002B2C40@@QAE_NPAUArg54@@0@Z @0x002B2C40 75B.
// Chain on 0x002B254F: early false on +0x54 mismatch, same pointer, +0xF4 set;
// if this->check==0 return true else delegate to global lookup virtual +0xC.
// Evidence: retail push esi/mov esi[esp+8]/mov eax[esi+54]/push edi/mov edi[esp+10]/cmp
// [edi+54]/jne false/cmp esi edi/je false/cmp [ecx+F4]/jne false/call 0x2B254F/
// test al je true/mov ecx[g_00E02D6C]/call 0x3B8BAA/mov edx[eax]/push edi/push esi/
// mov ecx eax/call [edx+C]/test jne true else false/ret 8. Callers at 0x2B6CAB etc.
class Rva00E02D6C; extern Rva00E02D6C *TheCampaignManager;

class Rva002B254F
{
public:
	int rva002B254F();
};

class Rva003B8BAA
{
public:
	void *rva003B8BAA();
};

struct Arg54
{
	char m_pad[0x54];
	int m_val54;
};

class LookupVirt
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual bool check(Arg54 *a, Arg54 *b);
};

class Rva002B2C40
{
	char m_pad[0xF4];
	int m_flagF4;
public:
	bool rva002B2C40(Arg54 *a, Arg54 *b);
};

bool Rva002B2C40::rva002B2C40(Arg54 *a, Arg54 *b)
{
	if (a->m_val54 != b->m_val54)
		return false;
	if (a == b)
		return false;
	if (m_flagF4 != 0)
		return false;
	if ((unsigned char)((Rva002B254F *)this)->rva002B254F() != 0)
	{
		void *p = ((Rva003B8BAA *)TheCampaignManager)->rva003B8BAA();
		if (!((LookupVirt *)p)->check(a, b))
			return false;
	}
	return true;
}
