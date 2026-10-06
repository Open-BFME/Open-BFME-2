// cl: /DNDEBUG /MD /GX /Ireference/shims/moduledata
// ??1Rva002560E3@@UAE@XZ @0x002560E3 84B
// ModuleData dtor: releases StringBase<char> at +0x1D8 (state 2) and +0x1D4
// (state 1) through rowed releaseBuffer 0x00036410, runs the member dtor at
// +0x1C8 (state 0) through rowed Rva00360D26Member 0x00360D26, then restores
// the Snapshot base vtable 0x00BBB554. Shape follows PillageModuleDataDtor
// (shared Snapshot base dtor, novtable derived to suppress own store, empty
// virtual body). Owner unproven so honest address
// name; caller is the 28B 0x002560C7.
template <typename T> class StringBase {
public: ~StringBase() { releaseBuffer(); }
private: void releaseBuffer(); void *m_data; };

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

class Rva00360D26Member
{
public: ~Rva00360D26Member();
};
#include "Common/Snapshot.h"

class __declspec(novtable) Rva002560E3 : public Snapshot
{
public:
	virtual ~Rva002560E3();
private:
	unsigned char m_pad00[0x1C8 - 4];
	Rva00360D26Member m_filter1C8;
	unsigned char m_pad1CC[0x1D4 - 0x1CC];
	StringBase<char> m_str1D4;
	StringBase<char> m_str1D8;
};
// ??1Rva002560E3@@UAE@XZ
Rva002560E3::~Rva002560E3()
{
}
