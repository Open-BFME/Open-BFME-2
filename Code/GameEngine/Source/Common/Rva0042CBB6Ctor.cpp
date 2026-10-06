// cl: /EHsc /MD
// ??0Rva0042CBB6@@QAE@XZ @0x0042CBB6 101B via zeroing ctor with memset tail plus global store
// Evidence: thiscall returns this; vtable g_00C3C6F4 at +0 plus +0xC=2 plus +0x38=1; memset thunk 0x006291AE of +0x3A len 4; global g_00E03210 stores this; caller 0x0023A4C3
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")
void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);

extern const void *const g_00C3C6F4[];
extern void *g_00E03210;

class Rva0042CBB6
{
public:
	Rva0042CBB6();
private:
	const void *m_vtable;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	unsigned char m_38;
	unsigned char m_39;
	char m_3A[4];
	unsigned char m_3E;
	unsigned char m_3F;
	unsigned char m_40;
	unsigned char m_41;
	unsigned char m_42;
};

Rva0042CBB6::Rva0042CBB6()
	: m_vtable(reinterpret_cast<const void *>(g_00C3C6F4))
	, m_0C(2)
	, m_38(1)
{
	m_04 = 0;
	m_08 = 0;
	m_39 = 0;
	m_3E = 0;
	m_3F = 0;
	m_40 = 0;
	m_41 = 0;
	m_42 = 0;
	m_14 = 0;
	m_10 = 0;
	m_1C = 0;
	m_18 = 0;
	m_24 = 0;
	m_20 = 0;
	m_2C = 0;
	m_28 = 0;
	m_30 = 0;
	m_34 = 0;
	ji_006291ae(m_3A, 0, 4);
	g_00E03210 = this;
}
