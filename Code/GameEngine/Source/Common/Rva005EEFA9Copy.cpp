// cl: /MD
// ?Rva005EEFA9Copy@@YAPAURva005EEFA9Dst@@PAU1@PBURva005EEFA9Src@@H@Z, retail 0x005EEFA9, 41 bytes.
// Copies 16-byte src plus int extra into 20-byte dst via 20-byte local.
// Callers pass AsciiStringCharPlusText-like 16B src and use return (dst).

struct Rva005EEFA9Src
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
};

struct Rva005EEFA9Dst
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
};

Rva005EEFA9Dst * __cdecl Rva005EEFA9Copy(Rva005EEFA9Dst *dst, const Rva005EEFA9Src *src, int extra)
{
	Rva005EEFA9Dst tmp;
	*(Rva005EEFA9Src *)&tmp = *src;
	tmp.m_10 = extra;
	*dst = tmp;
	return dst;
}
