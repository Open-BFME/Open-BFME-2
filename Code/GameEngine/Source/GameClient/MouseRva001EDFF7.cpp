// cl: /MD
// ?rva001EDFF7@Mouse@@QBEXPAM@Z @0x001EDFF7 62B
// Copies four ints at +0x4f84..+0x4f90 to floats; sole caller at 0x0042EDD5.
class Mouse {
	char _pad0[0x4f84];
	int m_4f84;
	int m_4f88;
	int m_4f8c;
	int m_4f90;
public:
	void rva001EDFF7(float *out) const;
};
void Mouse::rva001EDFF7(float *out) const
{
	if (!out)
		return;
	out[0] = (float)m_4f84;
	out[2] = (float)m_4f88;
	out[1] = (float)m_4f8c;
	out[3] = (float)m_4f90;
}
