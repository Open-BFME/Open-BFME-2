// cl: /MD
// ?rva00531E14@Rva00531E14@@QAEEG@Z @ 0x00531E14 (71B): __thiscall table-walk predicate over two word chains.
// Words at +2/+4 start each chain, +6 limit, +8 word table; returns 0 when val hits either chain else 1.
// Caller at 0x00534397. Owner unknown so honest address name. /G7 drops the redundant movzx.
// ?rva00531D52@Rva00531E14@@QAEGXZ @ 0x00531D52 (75B): same class pop/alloc helper; callers at 0x00532AFB 0x00533C4B.
// ?rva00531D08@Rva00531E14@@QAEAAV1@G@Z @ 0x00531D08 (46B): __thiscall init; stores count at +0/+4 clears +2/+6 new[] ushort table at +8 sized count*2 via rowed ??_U@YAPAXI@Z; caller 0x0053237A pushes 0x5DC0; returns *this.
// ?rva00531DAE@Rva00531E14@@QAEEG@Z @ 0x00531DAE (51B): __thiscall dec table[idx]; if nonzero return 0 else link idx onto +4 chain; caller at 0x00533167.
void *__cdecl operator new[](unsigned int size);
class Rva00531E14
{
public:
	Rva00531E14 &rva00531D08(unsigned short count);
	unsigned char rva00531E14(unsigned short val);
	unsigned short rva00531D52();
	unsigned short rva00531DE1();
	unsigned char rva00531DAE(unsigned short idx);
unsigned short m_pad0;
	unsigned short m_start1;
	unsigned short m_start2;
	unsigned short m_end;
	unsigned short *m_table;
};
unsigned char Rva00531E14::rva00531E14(unsigned short val)
{
	unsigned short cur = m_start1;
	while (cur < m_end)
	{
		if (cur == val)
			return 0;
		cur = m_table[cur];
	}
	cur = m_start2;
	while (cur < m_end)
	{
		if (cur == val)
			return 0;
		cur = m_table[cur];
	}
	return 1;
}
unsigned short Rva00531E14::rva00531D52()
{
	unsigned short cur = m_start1;
	if (cur < m_end)
	{
		unsigned short *p = &m_table[cur];
		unsigned short nxt = *p;
		m_start1 = nxt;
		*p = 1;
		return cur;
	}
	if (m_end >= m_pad0)
		return (unsigned short)(m_pad0 - 1);
	m_table[m_end] = 1;
	unsigned short old = m_start1;
	++m_end;
	m_start1 = (unsigned short)(old + 1);
	return old;
}
Rva00531E14 &Rva00531E14::rva00531D08(unsigned short count)
{
	m_start1 = 0;
	m_end = 0;
	m_pad0 = count;
	m_start2 = count;
	m_table = new unsigned short[count];
	return *this;
}
unsigned short Rva00531E14::rva00531DE1()
{
	unsigned short cur = m_start2;
	if (cur == m_pad0)
		return m_pad0;
	unsigned short nxt = m_table[cur];
	m_start2 = nxt;
	m_table[cur] = m_start1;
	m_start1 = cur;
	return cur;
}
unsigned char Rva00531E14::rva00531DAE(unsigned short idx)
{
	--m_table[idx];
	if (m_table[idx] > 0)
		return 0;
	m_table[idx] = m_start2;
	m_start2 = idx;
	return 1;
}
