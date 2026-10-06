// cl: /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva0020E8DB@Rva0020E8DB@@QAEPAURva0020E8DBEntry@@H@Z, retail 0x0020E8DB, 52 bytes.
// Scan of pointer vector at +0x5C/+0x60 returning element whose dword at +0
// matches int arg else NULL. Caller at 0x002E2016 pushes [esi+0x10].
#include <vector>

struct Rva0020E8DBEntry
{
	int m_id;
};

class Rva0020E8DB
{
public:
	Rva0020E8DBEntry *rva0020E8DB(int key);

private:
	unsigned char m_pad[0x5C];
	_STL::vector<Rva0020E8DBEntry *> m_vec;
};

Rva0020E8DBEntry *Rva0020E8DB::rva0020E8DB(int key)
{
	for (unsigned i = 0; i < m_vec.size(); ++i) {
		Rva0020E8DBEntry *elem = m_vec[i];
		if (*(int *)elem == key)
			return elem;
	}
	return 0;
}
