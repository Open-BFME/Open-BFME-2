// cl: /DNDEBUG /MD /EHsc
// ?Rva00583015Destroy@@YAXXZ @0x00583015 31B
// Singleton destroy for global 0x00A06398 (created by 0x005836B5 via 0x00583359).
// Evidence: mov ecx [0x00A06398] test je mov eax [ecx] push 0 call [eax] push eax
// call operator delete 0x0002FD60 and [0x00A06398] 0 pop ecx ret; caller 0x0044D279;
// same virtual-slot-0 plus delete shape as Rva0023C420Delete 20B.

void __cdecl operator delete(void *p);
void *__cdecl operator new(unsigned int size);
void __cdecl Rva00437E9C(int value);

class Rva00583015Obj
{
public:
	Rva00583015Obj(void *argument);
	virtual void *s0(int x);

private:
	unsigned char m_pad04[0x54];
	void *m_argument; // +0x58, set by constructor 0x00583359
	unsigned char m_pad5C[0x20];
};

extern Rva00583015Obj *g_Va00A06398;

void __cdecl Rva00583015Destroy(void)
{
	Rva00583015Obj *p = g_Va00A06398;
	if (p != 0)
	{
		void *q = p->s0(0);
		::operator delete(q);
		g_Va00A06398 = 0;
	}
}
// ?g_Va00A06398@@3PAVRva00583015Obj@@A: the global at VA 0xe06398 is ?g_Va00E06398@@3HA.
#pragma comment(linker, "/alternatename:?g_Va00A06398@@3PAVRva00583015Obj@@A=?g_Va00E06398@@3HA")

// Target facts: this one-argument initializer returns 0 when the global is
// already set and otherwise stores the new 0x7C-byte object and returns 1.
// The type and field names remain address-derived; 0x00583359 sets vtable
// 0x00C6FA9C and copies the argument to +0x58.
// ?Rva005836B5Initialize@@YA_NPAX@Z
bool __cdecl Rva005836B5Initialize(void *argument)
{
	if (g_Va00A06398 == 0)
	{
		Rva00437E9C(0);
		g_Va00A06398 = new Rva00583015Obj(argument);
		return true;
	}
	return false;
}
