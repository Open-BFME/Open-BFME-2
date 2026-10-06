// cl: /DNDEBUG /MD /GX /Ireference/shims/moduledata
//
// ??1Rva0044ECCE@@UAE@XZ, retail 0x0044ECCE, 199 bytes.
// ModuleData base dtor (size 0xC8) over Snapshot BBB554: and-zeroes +0x38
// and +0x3C, tears down five StringBase<char> at +0x40 +0x44 +0x48 +0xBC
// +0xC0 via rowed releaseBuffer 0x36410, and five opaque refs at +0x08
// +0x0C +0x10 +0x14 +0x34 via rowed Release_Ref 0x50ED3, then restores
// BBB554. Evidence: 14 matched caller dtors call this base; derived
// WeaponFire TU proves base size 0xC8; vtable 0x0083F2A8.

#include "Common/Snapshot.h"

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


typedef StringBase<char> AsciiString;

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

class OpaqueRefPtr
{
public:
	~OpaqueRefPtr() { if (m_p) m_p->Release_Ref(); }
private:
	OpaqueRefCounted *m_p;
};

class Rva0044ECCE : public Snapshot
{
public:
	virtual ~Rva0044ECCE();
private:
	int m_04; // +0x04
	OpaqueRefPtr m_08; // +0x08
	OpaqueRefPtr m_0C; // +0x0C
	OpaqueRefPtr m_10; // +0x10
	OpaqueRefPtr m_14; // +0x14
	unsigned char m_pad18[0x34 - 0x18];
	OpaqueRefPtr m_34; // +0x34
	int m_38; // +0x38 and-zeroed
	int m_3C; // +0x3C and-zeroed
	AsciiString m_40; // +0x40
	AsciiString m_44; // +0x44
	AsciiString m_48; // +0x48
	unsigned char m_pad4C[0xBC - 0x4C];
	AsciiString m_BC; // +0xBC
	AsciiString m_C0; // +0xC0
	unsigned char m_padC4[0xC8 - 0xC4];
};

Rva0044ECCE::~Rva0044ECCE()
{
	m_38 = 0;
	m_3C = 0;
}
