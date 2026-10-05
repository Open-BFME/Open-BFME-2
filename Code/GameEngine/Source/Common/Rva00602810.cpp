// ?rva00602810@Rva00602810@@QAEHXZ @0x00602810 19B: honest-address thiscall near Rva006026E0 cluster.
// Evidence: retail reads ecx+0xc as pointer, returns 0 when [p]==0 else [p]-[p+8]; callers at 0x00428075 0x00428099 unclaimed.
class Rva00602810
{
public:
	char m_pad00[0xc];
	int *m_p0c;
	int rva00602810();
};

int Rva00602810::rva00602810()
{
	if (m_p0c[0] != 0)
		return m_p0c[0] - m_p0c[2];
	return 0;
}
