// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ?rva00180AB5@Rva00180B94_Prototype@@UAEXXZ @0x00180AB5 33B
// Slot 6 (offset 0x18) of vtable 0x007D5050 (class of ??0Rva00180B94_Prototype
// in Rva00180B94Ctor.cpp). Clears tree link at +0x14: if non-null calls its
// virtual slot 0 with 0, deletes the returned pointer via rowed
// ??3@YAXPAX@Z, then nulls +0x14 via and [m],0 (/O1). Class and flags from
// donor TU; m_tree stays void* there, cast here proves vtable from the
// slot-0 call. No callers rowed; vtable slot proves identity.
void __cdecl operator delete(void *p);

struct TreeLink
{
	virtual void *virt0(int x);
};

class StringClass
{
public:
	StringClass(const char *name, bool flag);
	~StringClass();
};

class GenBase009EB7D0
{
public:
	GenBase009EB7D0();
	virtual ~GenBase009EB7D0();
};

class Rva00180B94_Prototype : public GenBase009EB7D0
{
public:
	Rva00180B94_Prototype(const char *name, void *tree);

	char m_pad04[0x10];
	void *m_tree;
	StringClass m_name;
	int m_arg1C;
	int m_arg20;
	virtual void rva00180AB5();
};

void Rva00180B94_Prototype::rva00180AB5()
{
	void *p = m_tree;
	void *q;
	if (p != 0)
		q = ((TreeLink *)p)->virt0(0);
	else
		q = 0;
	operator delete(q);
	m_tree = 0;
}
