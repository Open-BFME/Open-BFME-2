// ?Rva002B3E7ECheck@@YIEPAX@Z
// partial score=0.95 date=2026-10-04
// cl: /O1 /MD
// ?Rva002B3E7ECheck@@YIEPAX@Z 88B @0x002B3E7E: global Rva002B254F guard via g_009FEF10 then virtual slot 8 check then +0xC4 flag then Rva002D06CA lookup via g_009FF000 and bit 26 test.
// Evidence: retail mov ecx,[0xDFEF10] call 0x2B254F test je then mov ecx,[0xE02D6C] call 0x3B8BAA virtual [edx+8] with esi arg then cmp [esi+0xC4] then Rva002D06CA with esi+4 then [eax+0x110] shr 26 not and 1. Callers at 0x002B3EEA 0x002B3F1A 0x002B3F62 pass pointer in eax.
// ?Rva002B3E7ECheck@@YIEPAX@Z present-unmatched
class Rva002B254F
{
public:
	int rva002B254F();
};

class Rva002BA8F1Logic;
extern Rva002BA8F1Logic *g_009FEF10;

class Rva003B8BAA
{
public:
	void *rva003B8BAA();
};

extern Rva003B8BAA *g_00E02D6C;

class AsciiString;

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

extern Rva002D06CA *g_009FF000;

class LookupVirt08
{
public:
	virtual void s00();
	virtual void s01();
	virtual bool check(void *a);
};

struct Rva002B3E7ETarget
{
	char m_pad[0xC4];
	unsigned char m_flagC4;
};

__declspec(noinline) static unsigned char __fastcall Rva002B3E7ECheck(void *p)
{
	void *obj;
	if ((unsigned char)((Rva002B254F *)g_009FEF10)->rva002B254F() == 0)
		goto check_flag;
	obj = g_00E02D6C->rva003B8BAA();
	if (((LookupVirt08 *)obj)->check(p) == 0)
		return 0;
check_flag:
	Rva002B3E7ETarget *t = (Rva002B3E7ETarget *)p;
	if (t->m_flagC4 != 0)
		return 0;
	void *found = g_009FF000->rva002D06CA((const AsciiString *)((char *)p + 4));
	if (found == 0)
		return 0;
	unsigned int v = *(unsigned int *)((char *)found + 0x110);
	unsigned char c = (unsigned char)(v >> 26);
	c = (unsigned char)~c;
	c &= 1;
	return c;
}

// ?Rva002B3E7EDummy@@YIEPAX@Z present-unmatched
unsigned char __fastcall Rva002B3E7EDummy(void *p)
{
	return Rva002B3E7ECheck(p);
}
