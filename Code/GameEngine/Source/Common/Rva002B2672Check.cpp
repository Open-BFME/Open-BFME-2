// cl: /MD
// ?rva002B2672@Rva002B2672@@QAE_NPAUArg54@@0@Z @0x002B2672 44B.
// Chain on 0x002B254F with two args: if this->check==0 return true else
// global lookup virtual +0x2C on the args.
// Evidence: retail call 0x2B254F/test al je true/mov ecx[g_00E02D6C]/call 0x3B8BAA/
// push [esp+8]/mov edx[eax]/push [esp+8]/mov ecx eax/call [edx+2C]/test al je end/mov al 1/ret 8.
// Caller at 0x004FA9EC. ecx passes through from thiscall. Sibling TU Rva002B2646Check.cpp.
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

class LookupVirt2C
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual bool check(Arg54 *a, Arg54 *b);
};

class Rva002B2672
{
public:
	bool rva002B2672(Arg54 *a, Arg54 *b);
};

bool Rva002B2672::rva002B2672(Arg54 *a, Arg54 *b)
{
	if ((unsigned char)((Rva002B254F *)this)->rva002B254F() != 0)
	{
		void *p = ((Rva003B8BAA *)TheCampaignManager)->rva003B8BAA();
		if (!((LookupVirt2C *)p)->check(a, b))
			return false;
	}
	return true;
}
