// ?rva00104956@Rva001040D5@@QAEXI@Z
// partial score=0.96 date=2026-10-06
// cl: /O1 /MD /EHsc /DNDEBUG /arch:SSE
// ?rva00104956@Rva001040D5@@QAEXI@Z retail 0x00104956 113B.
// Evidence: vslot 23 (offset 0x5C) of vtable 0x007CF6F0 installed by ??0Rva001040D5; calls DX8Wrapper::Apply_Render_State_Changes 0x0011D930 and 7-arg Clear 0x0011D330 then walks intrusive list at +0x60/+0x64 calling slot 12 (0x30) with the argument then rva001173f0.
struct Vector3
{
	float X;
	float Y;
	float Z;
};
class DX8Wrapper
{
public:
	static void Apply_Render_State_Changes();
	static void Clear(bool clear_color, bool clear_z_stencil, bool clear_stencil, const Vector3 &color, float dest_alpha, float z, unsigned int stencil);
};
void __cdecl rva001173f0();

class Rva00142960Base
{
public:
	Rva00142960Base();
	virtual ~Rva00142960Base();
};

class Slot12Target
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
	virtual void s11();
	virtual void slot12(unsigned int arg);
};

struct ListNode
{
	void *m_prev;
	ListNode *m_next;
	void *m_unk08;
	void *m_ptrPlus8;
};

class Rva001040D5 : public Rva00142960Base
{
public:
	void rva00104956(unsigned int arg);
private:
	char m_pad04[0x60 - 0x04];
	ListNode m_list;
};

void Rva001040D5::rva00104956(unsigned int arg)
{
	DX8Wrapper::Apply_Render_State_Changes();
	Vector3 black = { 0.0f, 0.0f, 0.0f };
	DX8Wrapper::Clear(false, true, true, black, 0.0f, 1.0f, 0);
	ListNode *n = m_list.m_next;
	while (n != &m_list)
	{
		void *p = n->m_ptrPlus8;
		Slot12Target *o = p ? (Slot12Target *)((char *)p - 8) : 0;
		o->slot12(arg);
		n = n->m_next;
	}
	rva001173f0();
}
