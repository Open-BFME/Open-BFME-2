// cl: /MD
// ?set@Rva005F3F41Outer@@QAEXE@Z @0x005F3F41 35B gap between
// ?get@Rva005F3F3AByteChaseField@@QBEEXZ and ?get@Rva005F3F64ByteChaseField@@QBEEXZ
// in Disp8ByteChaseGetters.cpp. Sets [m_sub+0x14] to the byte param and, when
// [m_sub+0x0C] is non-null, forwards the param to the rowed chase thunk
// ?rva005FC6F7@Rva005FC6F7@@QAEXE@Z (which reaches bit0 at +0x34). Callers are
// 0x005E4D74, 0x005E4DD0, 0x005E4DE5. Owner identity unproven so the address
// token is kept. Flags /O1: default /O2 duplicates the store (49B) while /O1
// keeps the single trailing store (35B exact).
class Rva005FC6F7
{
public:
	void rva005FC6F7(unsigned char value);
};
struct Sub005F3F41
{
	char m_pad0[0x0C];
	Rva005FC6F7 *m_thunk;
	char m_pad1[0x14 - 0x0C - 4];
	unsigned char m_byte14;
};
class Rva005F3F41Outer
{
public:
	void set(unsigned char value);
	char m_pad[8];
	Sub005F3F41 *m_sub;
};
void Rva005F3F41Outer::set(unsigned char value)
{
	if (m_sub->m_thunk) {
		m_sub->m_thunk->rva005FC6F7(value);
	}
	m_sub->m_byte14 = value;
}
