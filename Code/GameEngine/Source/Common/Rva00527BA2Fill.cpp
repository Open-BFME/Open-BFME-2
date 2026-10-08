// cl: /MD
// Range-27 table-driven fill.
// ?Rva00527BA2@Holder00527BA2@@QAEXPADHH@Z @0x00527BA2 98B
// Thiscall (dst, n, m): when n < 1, takes k = m (or 1 - n when n + m
// exceeds 1); a positive k stores the m_0 byte to *dst, then m shrinks
// by k and bails at zero, advancing dst/n. Otherwise (or after) reads
// the table pointer through m_4 (defaulting to g_bfmeEmptyF9 0x00BBAC1C
// plus 8 when unset) and memcpys m bytes from table + (n - 1).
extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
#pragma function(memcpy)


struct Holder00527BA2
{
	char m_0;
	char m_pad[3];
	char **m_4;
	void Rva00527BA2(char *dst, int n, int m);
};

void Holder00527BA2::Rva00527BA2(char *dst, int n, int m)
{
	if (n < 1)
	{
		int k = m;
		if (n + m > 1)
			k = 1 - n;
		if (k > 0)
			*dst = m_0;
		m -= k;
		if (m <= 0)
			return;
		dst += k;
		n += k;
	}
	char *q = *m_4;
	n--;
	if (q != 0)
		q += 8;
	else
		q = "";
	memcpy(dst, q + n, m);
}

