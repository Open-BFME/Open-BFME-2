// cl: /EHsc /MD /Ireference/shims/moduledata
// ??1Rva002E0F1E@@UAE@XZ @0x002E0F1E 99B Snapshot-derived dtor with five StringBase members.
// Wide at +4 via 0x00036E70 then four narrow at +8 +0xC +0x10 +0x14 via 0x00036410 in reverse with EH states 4 to 0 then base vtable 0x00BBB554.
// Evidence: caller 0x002E18A7 is 28B deleting dtor plus sibling ??1Rva00B6971@@UAE@XZ same Snapshot base plus prev 0x002E0E7C next 0x002E1001 same dir.
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

#include "Common/Snapshot.h"
class __declspec(novtable) Rva002E0F1E : public Snapshot
{
public:
	virtual ~Rva002E0F1E();
private:
	StringBase<unsigned short> m_04;
	StringBase<char> m_08;
	StringBase<char> m_0c;
	StringBase<char> m_10;
	StringBase<char> m_14;
};
Rva002E0F1E::~Rva002E0F1E()
{
}
