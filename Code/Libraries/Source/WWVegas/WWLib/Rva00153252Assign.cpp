// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// ??4Rva00153252@@QAEAAU0@ABU0@@Z, retail 0x00153252, 27 bytes.
// 8-byte entry assign TreeHintRef at +0 via rowed 0x2174A4 then int at +4 then return this.
// Evidence: push esi push edi mov edi [esp+0xC] push edi call 0x2174A4 plus mov eax [edi+4] mov [esi+4] eax; caller 0x153339 copy loop stride 8 sar 3; same layout as Rva0040D0A4Entry but TreeHintRef holder.
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
};
struct Rva00153252
{
	TreeHintRef00217D4C m_00;
	int m_04;
	Rva00153252 &operator=(const Rva00153252 &other);
};
Rva00153252 &Rva00153252::operator=(const Rva00153252 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	return *this;
}
