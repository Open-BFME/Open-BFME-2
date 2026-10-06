// cl: /MD
// ??1Rva006FBDB0@@QAE@XZ @0x006FBDB0 12B.
// Non-virtual dtor: zeroes member at +4 then tail-jumps rowed EAStringC dtor at 0x006D3010.
// Evidence: callers at 0x006FE333 and 0x00706347 (Rva00706330Cluster.cpp element dtor, 12B store);
// LINK BONUS 1 file waits only for this body; base size 4B (m_pData) plus member plus pad is 0xC.
class EAStringC
{
public:
	~EAStringC();
	void *m_pData;
};

class Rva006FBDB0 : public EAStringC
{
public:
	~Rva006FBDB0();
private:
	int m_4;
	char m_pad[4];
};

Rva006FBDB0::~Rva006FBDB0()
{
	m_4 = 0;
}
