// cl: /MD
// ?rva00330B50@Rva00330B50@@QAEAAV1@ABV1@@Z retail 0x00330B50 27B: copy-assign via rowed base opassign plus dword 0x28 returns this.
// Evidence: call 0x0030B92C ??4Rva0030B92C@@QAEAAU0@ABU0@@Z then mov eax [edi+0x28] to [esi+0x28]; chain from 0x0030B92C.
struct Rva0030B92C
{
	Rva0030B92C &operator=(const Rva0030B92C &o);
	char m_pad[0x28];
};

class Rva00330B50 : public Rva0030B92C
{
public:
	Rva00330B50 &rva00330B50(const Rva00330B50 &o);
private:
	int m_28;
};

Rva00330B50 &Rva00330B50::rva00330B50(const Rva00330B50 &o)
{
	Rva0030B92C::operator=(o);
	m_28 = o.m_28;
	return *this;
}
