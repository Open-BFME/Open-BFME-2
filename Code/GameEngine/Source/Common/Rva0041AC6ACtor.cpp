// cl: /MD
// ??0Rva0041AC6A@@QAE@XZ, retail 0x0041AC6A, 32 bytes.
// Evidence: leaf lane, caller at 0x0022FAC5, callee baseConstruct 0x001B4E63,
// vtable g_00C3ADD8 at +0, second vtable g_00C3ADC8 at +0xC overwriting g_00BBB554.
class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

extern const void *const g_00BBB554[];
extern const void *const g_00C3ADD8[];
extern const void *const g_00C3ADC8[];

class Rva0041AC6A
{
public:
	Rva0041AC6A();
	char m_pad[12];
	const void *volatile m_secondVptr;
};

Rva0041AC6A::Rva0041AC6A()
{
	((BFME2NativeNetwork *)this)->baseConstruct();
	m_secondVptr = (const void *)g_00BBB554;
	*(const void **)this = (const void *)g_00C3ADD8;
	m_secondVptr = (const void *)g_00C3ADC8;
}
