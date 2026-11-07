// cl: /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfmelist
// ?rva004F597F@Rva004F599E@@QAEXXZ, retail 0x004F597F, 31 bytes.
// Zeroes two int[21] blocks at +4 and +0x58; called from ctor 0x004F599E after vtable store.
// ??0Rva004F599E@@QAE@XZ, retail 0x004F599E, 14 bytes.
// Ctor stores vtable 0x00863254 then calls rva004F597F; evidence chain lane caller 0x002B0FF8.
//
// The class is a Snapshot (LINK-617). Retail's table VA 0x00C63254, which the
// constructor installs, has Snapshot's four slots: slot 0 the deleting
// destructor (retail 0x004A10FD, the ICF-shared body that calls ~Snapshot
// 0x0049B47C), slot 1 an empty loadPostProcess (retail 0x004B3FD0, a shared
// `ret`), slot 2 the class-name getter 0x004F59AC (returns "MissionStats") and
// slot 3 the rowed xfer 0x004F59B2. Declaring them over the canonical Snapshot
// lets the compiler emit and relocate the table; the constructor-only surface
// keeps Snapshot's own vptr store out of the constructor, as retail has none.
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_CONSTRUCTOR_ONLY
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

class Rva004F599E : public Snapshot
{
public:
	Rva004F599E();
	virtual ~Rva004F599E() {}
	void rva004F597F();
protected:
	virtual void loadPostProcess() {}
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
private:
	int m_a[21];
	int m_b[21];
};
void Rva004F599E::rva004F597F()
{
	for (int i = 0; i < 20; ++i) {
		m_a[i] = 0;
		m_b[i] = 0;
	}
	m_a[20] = 0;
	m_b[20] = 0;
}
Rva004F599E::Rva004F599E()
{
	rva004F597F();
}
