// cl: /DNDEBUG /MD /GX /Ireference/shims/moduledata
// ??1Rva003FD4DA@@UAE@XZ @0x003FD4DA 72B
// ModuleData dtor: vtable 0x007FE1B0, two releaseBuffer calls on the string at
// +0x0C (body clear plus implicit member destruction), then Snapshot base
// vtable 0x00BBB554. Same recipe as Rva003FD789Dtor, using the shared Snapshot
// base header; StringBase<char>::releaseBuffer is the row at 0x00036410.
// Unblocks ??_G at 0x002B5972.
#include "Common/Snapshot.h"

template <typename T> class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
	void clear() { releaseBuffer(); }
private:
	void releaseBuffer(); // declared only: ?releaseBuffer@?$StringBase@D@@AAEXXZ is rowed
	T *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


class Rva003FD4DA : public Snapshot
{
public:
	virtual ~Rva003FD4DA();
private:
	char m_pad04[8];
	StringBase<char> m_0c;
};

Rva003FD4DA::~Rva003FD4DA()
{
	m_0c.clear();
}
