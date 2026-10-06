// cl: /DNDEBUG /MD
//
// ?rva0052DAC4@Rva0052DAC4 (retail 0x0052DAC4, 14 bytes): nested one-field
// setter that copies *source into m_inner->m_first (+8). Shape mirrors
// Rva003F69C0Object::set in the neighbouring TU, which sets two fields;
// this body sets only the first. Evidence: 8 callers pass a pointer from
// [ebp+8] with ecx=esi (e.g. 0x002F4603 pushes [ebp+8] after loading the
// inner word at +0x12); /O1 reproduces retail's ecx reuse where /O2 uses edx.

class Rva0052DAC4Inner
{
public:
	char m_pad[8];
	int m_first;
};

class Rva0052DAC4
{
public:
	void rva0052DAC4(int *source);

private:
	Rva0052DAC4Inner *m_inner;
};

void Rva0052DAC4::rva0052DAC4(int *source)
{
	m_inner->m_first = *source;
}
