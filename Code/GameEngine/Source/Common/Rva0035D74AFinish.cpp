// ??0Rva0035D74A@@QAE@XZ
// cl: /O1 /MD /arch:SSE
//
// ??0Rva0035D74A@@QAE@XZ @0x0035D789 (72B):
// Ctor calls rowed base 0x001DBAA4 then stores derived vtable, zeroes six
// ints at +0x10..+0x24, sets +0x30 to -1 via or, +0x34 to 0, re-zeroes base
// +0x0C, two floats at +0x28/+0x2C to 0.0f via xorps/movss, base +9 to 1 and
// base +4 to 0x16. Caller 0x0035D80F. Evidence: unlock lane, all callees
// rowed, prev/next dtors prove class, vtable store implicit.
//
// Two levers place the vtable store, which /O1 otherwise sinks into the
// constant-store group at +0x1F:
//   __declspec(novtable) stops the compiler emitting its own vptr store, so
//     the explicit one is the only one; its alias names the existing vtable
//     proven at retail VA 0x00C16530, so it also follows the linked table;
//   writing the FIRST member (+0x10) through a pointer pins the whole store
//     run behind that one node and the vtable store lands at slot 3, right
//     after xor eax,eax exactly as retail does.
extern "C" const void *const vtbl_00C16530[];  // ??_7Rva0035D74A@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C16530=??_7Rva0035D74A@@6B@")

class Rva001DBAA4
{
public:
	virtual ~Rva001DBAA4();
	Rva001DBAA4();
	int m_4;
	bool m_8;
	bool m_9;
	bool m_A;
	int m_C;
};
class __declspec(novtable) Rva0035D74A : public Rva001DBAA4
{
public:
	Rva0035D74A();
	virtual ~Rva0035D74A();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
private:
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	float m_28;
	float m_2c;
	int m_30;
	int m_34;
};
Rva0035D74A::Rva0035D74A()
{
	*(unsigned int *)this = ((unsigned int)vtbl_00C16530);
	int *p30 = &m_30;
	int *p10 = &m_10;
	*p10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1c = 0;
	m_20 = 0;
	m_24 = 0;
	*p30 = -1;
	m_34 = 0;
	m_C = 0;
	m_28 = 0.0f;
	m_2c = 0.0f;
	m_9 = true;
	m_4 = 0x16;
}
