// cl: /MD
// ?clear@Rva00053D89@@QAEXXZ, retail 0x00053D89, 26 bytes.
// Same shape as ?clear@Rva000A8879@@QAEXXZ at 0x000A8879. Holder at +0xB90 of
// MilesAudioManager (owned device, see MilesAudioManagerOpenDevice) whose
// assign pin at 0x00053D66 uses the same dtor; clears single Rva00A897D
// pointer at +0 via qualified virtual dtor plus rowed operator delete
// 0x0002FD60. Callers at 0x00060491 0x000611A8. Honest Rva class and clear
// name; no donor.
void __cdecl operator delete(void *p);

class Rva00A897D
{
public:
	virtual ~Rva00A897D();
};

class Rva00053D89
{
public:
	Rva00A897D *m_ptr;
	void clear();
};

void Rva00053D89::clear()
{
	Rva00A897D *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva00A897D::~Rva00A897D();
		::operator delete(p);
	}
}
