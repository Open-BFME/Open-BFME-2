// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// ?rva001531E6@Rva001531E6@@QAEXXZ, RVA 0x001531E6, 12 bytes.
// Holder at +0x10 releases 4 from pointee at +8 if non-null via named local single load.
// Evidence: mov eax [ecx+0x10] test je add [eax+8] -4 ret; callers at 0x1501BE 0x150F0D 0x15109A 0x1536DE 0x153B63.
struct Rva001531E6Target { char m_pad[8]; int m_08; };
struct Rva001531E6 { void rva001531E6(); char m_pad[0x10]; Rva001531E6Target *m_10; };
void Rva001531E6::rva001531E6()
{
	Rva001531E6Target *p = m_10;
	if (p)
		p->m_08 -= 4;
}
