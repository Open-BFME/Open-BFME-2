// cl: /O1 /EHsc /MD /arch:SSE
// Target evidence: Ghidra boundary 0x00261513, 34 bytes. Its address occurs
// at 0x008071A0, the third slot in one of several repeated three-entry tables
// (shared entries at 0x0036CC7A and 0x00395A19). It uses ECX as this, reads a
// helper pointer at +8, a byte at +0xC and a float at +0x10, then compares the
// low byte returned by address-derived helper 0x0028F326 with the stored byte.
// The method owner, argument type and operation names remain unresolved.

class Rva0028F326Owner
{
public:
	unsigned char rva0028F326(unsigned int value, float scalar);
};

class Rva00261513Owner
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual bool rva00261513(unsigned int value);

private:
	unsigned char m_pad04[4];
	Rva0028F326Owner *m_helper08;
	unsigned char m_expected0C;
	unsigned char m_pad0D[3];
	float m_scalar10;
};

// ?rva00261513@Rva00261513Owner@@UAE_NI@Z
bool Rva00261513Owner::rva00261513(unsigned int value)
{
	return m_helper08->rva0028F326(value, m_scalar10) == m_expected0C;
}
