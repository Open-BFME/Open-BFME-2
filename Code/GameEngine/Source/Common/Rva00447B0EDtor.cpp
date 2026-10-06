// cl: /EHsc /MD
//
// ??1Rva00447B0E@@QAE@XZ @0x00447B0E 74B.
// Dtor: release StringBase<char> at +0x1C8 via rowed 0x00036410, destroy
// Gen_uwm_00447aca at +0x1AC via pinned 0x00447ACA, then base
// BfmeSaveElement002295D7 dtor rowed 0x002294FD. Evidence: unlock lane;
// same no-vptr QAE EH shape as landed Rva00448089 0x00448089; base size
// 0x1AC proven by SaveGameInfoCopyBFME2; unblocks 6 incl 0x0044818B.
template <typename T> class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	T *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


struct Gen_uwm_00447aca
{
	~Gen_uwm_00447aca();
	char m_pad[0x1C];
};

struct BfmeSaveElement002295D7
{
	virtual ~BfmeSaveElement002295D7();
	char m_pad[0x1AC - 4];
};

class Rva00447B0E
{
public:
	~Rva00447B0E();
private:
	BfmeSaveElement002295D7 m_base00;
	Gen_uwm_00447aca m_1AC;
	StringBase<char> m_1C8;
};

Rva00447B0E::~Rva00447B0E()
{
}
