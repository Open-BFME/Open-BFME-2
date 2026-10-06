// ?rva00567F3D@Rva00567F3D@@QAEPAPAVRva00567960@@PAPAV2@H@Z
// partial score=0.95 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /EHs /MD
// ?rva00567F3D@Rva00567F3D@@QAEPAPAVRva00567960@@PAPAV2@H@Z @0x00567F3D 84B
// Chain body: new Rva00567960(val, &this+8 Info) then store with AddRef.
// Evidence: ret 8 two args; push 0x1c new; rowed ctor 0x00567CCD (int, Info);
// inc [eax+4] refcount zeroed by ctor; returns first arg.
struct Rva00567CCDInfo
{
	int m_00;
	int m_04;
};

class Rva00567960
{
public:
	Rva00567960(int a1, const Rva00567CCDInfo *a2);
	void *m_vtbl;
	int m_ref;
	char m_pad[20];
};

class Rva00567F3D
{
	int m_00;
	int m_04;
	Rva00567CCDInfo m_info;
public:
	Rva00567960 **rva00567F3D(Rva00567960 **out, int val);
};

// ?rva00567F3D@Rva00567F3D@@QAEPAPAVRva00567960@@PAPAV2@H@Z present-unmatched
Rva00567960 **Rva00567F3D::rva00567F3D(Rva00567960 **out, int val)
{
	Rva00567960 *tmp = new Rva00567960(val, &m_info);
	*out = tmp;
	if (tmp)
		++tmp->m_ref;
	return out;
}
