// cl: /MD
// ?rva000724D7@Rva000724AE@@QAEPAXPAH@Z @0x000724D7 72B Rva000724AE surface lock
// Evidence: same +0x00/+0x0c/+0x10 layout as Rva000724AEClear.cpp (cleanup@Rva00739C70 on +0x00, surface holder +0x0c, flags +0x10); rect args [esi]/[esi+4] as (right,bottom) to rowed rva001166E0; discard path via rowed rva00116680(pitchOut,true); sets flag bit0; ret 4 with pointer return; callers 0x72560/0x72617/0x72681.
class Rva00739C70
{
public:
	void cleanup();
	int m_00;
	int m_04;
};

class Rva001166E0
{
public:
	void *rva001166E0(int *pitchOut, int left, int top, int right, int bottom);
	void *m_surface;
};

class Rva00116680
{
public:
	void *rva00116680(int *pitchOut, bool discard);
};

class Rva000724AE
{
public:
	void *rva000724D7(int *pitchOut);
private:
	Rva00739C70 m_00;
	void *m_08;
	Rva001166E0 m_0c;
	unsigned int m_flags;
};

void *Rva000724AE::rva000724D7(int *pitchOut)
{
	void *ret = 0;
	if (m_flags & 1)
		m_00.cleanup();
	Rva001166E0 *surf = &m_0c;
	if (surf->m_surface != 0)
	{
		if ((m_flags & 0xc) == 0)
			ret = surf->rva001166E0(pitchOut, 0, 0, m_00.m_00, m_00.m_04);
		else
			ret = ((Rva00116680 *)surf)->rva00116680(pitchOut, true);
		m_flags |= 1;
	}
	return ret;
}
