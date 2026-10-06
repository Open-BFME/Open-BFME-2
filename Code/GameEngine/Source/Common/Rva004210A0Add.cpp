// cl: /MD
// ?rva004210A0@Rva004210A0@@QAEXH@Z @0x004210A0 16B
// Clamped add at +4: m_val += delta; if (m_val < 0) m_val = 0.
// Evidence: __thiscall via ecx plus one stack arg plus ret 4; add plus jns plus and 0.
// Caller 0x002AA773 lea ecx [esi+0x318] then call; honest address-derived name.
class Rva004210A0
{
public:
	void rva004210A0(int delta);
private:
	int m_unk0;
	int m_val;
};
void Rva004210A0::rva004210A0(int delta)
{
	m_val += delta;
	if (m_val < 0)
		m_val = 0;
}
