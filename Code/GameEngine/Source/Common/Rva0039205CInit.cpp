// cl: /O1 /MD
// ?rva00392CAC@Rva0039205C@@QAEXXZ 25B @0x00392CAC: init-style setter zeroing +0 +4 +0C +0D plus -1 at +0x10 plus 0 at +0x14 then tail-jmp to array init. Layout +0 count +8 array from dtor at 0x0039205C. Evidence: shared init pin at 0x00392092 plus callers at 0x003935FC 0x00393E6D.
class Rva00392092Target
{
public:
	void rva00392092();
};

class Rva0039205C
{
public:
	void rva00392CAC();
private:
	int m_count00;
	int m_unk04;
	void *m_array08;
	unsigned char m_b0C;
	unsigned char m_b0D;
	char m_pad0E[0x02];
	int m_cached10;
	void *m_unk14;
};

void Rva0039205C::rva00392CAC()
{
	m_count00 = 0;
	m_cached10 = -1;
	m_b0C = 0;
	m_b0D = 0;
	m_unk04 = 0;
	m_unk14 = 0;
	((Rva00392092Target *)this)->rva00392092();
}
