// cl: /O1 /DNDEBUG /MD
// Reconstruction of the 52B condenser at 0x0031B60D: when the +0x2A8
// pair is empty run the pinned filler on out, else copy the last 8B
// before +0x2AC into out; returns out. All names address-derived.
class Rva0031B60DOut
{
public:
	void rva0035AEC2();
	int m_00;
	int m_04;
};

class Rva0031B60DOwner
{
public:
	Rva0031B60DOut *rva0031B60D(Rva0031B60DOut *out);
private:
	unsigned char m_pad[0x2a8];
	void *m_2a8;
	void *m_2ac;
};

Rva0031B60DOut *Rva0031B60DOwner::rva0031B60D(Rva0031B60DOut *out)
{
	void **pp = &m_2a8;
	if (pp[0] == pp[1])
	{
		out->rva0035AEC2();
		return out;
	}
	void *end = m_2ac;
	out->m_00 = ((int *)end)[-2];
	out->m_04 = ((int *)end)[-1];
	return out;
}
