// cl: /O1 /DNDEBUG /MD /arch:SSE
// Reconstruction of the 39B dirty check at 0x00319E7C: when either
// +0x3C float differs from its +0x44 shadow (NaN counts as different
// via the ucomiss/lahf shape), run the rowed 0x319AA0 handoff on the
// +0x3C pair. Reuses the rowed handoff name so it resolves via its row.
class Rva003195C9Owner
{
public:
	void rva00319E7C();
	void rva00319AA0(const int *arg);
private:
	unsigned char m_pad[0x3c];
	int m_3c;
	int m_40;
	int m_44;
	int m_48;
};

void Rva003195C9Owner::rva00319E7C()
{
	float *p = (float *)&m_3c;
	if (p[0] != *(float *)&m_44 || p[1] != *(float *)&m_48)
		rva00319AA0((const int *)p);
}
