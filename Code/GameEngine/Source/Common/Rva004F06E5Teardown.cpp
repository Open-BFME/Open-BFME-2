// cl: /O1
//
// ?rva004F06E5@Rva004F06E5@@QAEXXZ @0x004F06E5 49B.
// Holder teardown: when the +0x1C chain's +0x30 target carries flag bit 1 at
// +0x18, run the pinned 0x0039E9E0 fallback on the holder; otherwise free
// the slot-0 virtual result on the holder (or null) through rowed operator
// delete. Always clears +0x1C.
class Rva004F06E5Inner30
{
public:
	char m_pad[0x18];
	unsigned char m_18;
};

class Rva004F06E5Holder
{
public:
	virtual void *vf0(int v);
	char m_pad04[0x30 - 0x04];
	Rva004F06E5Inner30 *m_30;
};

class Rva005059A1Unit
{
public:
	void rva0039E9E0();
};

class Rva004F06E5
{
public:
	void rva004F06E5();
private:
	char m_pad[0x1C];
	Rva004F06E5Holder *m_1C;
};

void Rva004F06E5::rva004F06E5()
{
	if (!(m_1C->m_30->m_18 & 1))
		::operator delete(m_1C ? m_1C->vf0(0) : 0);
	else
		((Rva005059A1Unit *)m_1C)->rva0039E9E0();
	m_1C = 0;
}
