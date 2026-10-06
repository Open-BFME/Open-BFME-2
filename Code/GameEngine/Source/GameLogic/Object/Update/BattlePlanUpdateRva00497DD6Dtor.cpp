// cl: /DNDEBUG /MD /EHsc /Ireference/shims/moduledata
#include "Common/Snapshot.h"
// ??1Rva00497DD6@@UAE@XZ retail 0x00497DD6 250B
// Evidence: unlock lane no initial vtable store final BBB554 Snapshot base; 4 StringBase releaseBuffer at +0xA4 +0x48 +0x38 +0x24 plus 10 ref holders Release_Ref at +0x4C +0x44 +0x40 +0x3C +0x34 +0x30 +0x2C +0x28 +0x20 +0x1C; callees rowed releaseBuffer 0x00036410 plus Release_Ref 0x00050ED3; caller deleting dtor 0x00497DBA
template <typename T>
class StringBase
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


class OpaqueRefCounted
{
public:
	void Release_Ref();
};

class Holder00497DD6
{
public:
	~Holder00497DD6()
	{
		if (m_ptr != 0)
			m_ptr->Release_Ref();
	}
private:
	OpaqueRefCounted *m_ptr;
};

class __declspec(novtable) Rva00497DD6 : public Snapshot
{
public:
	virtual ~Rva00497DD6();
private:
	char m_pad04[0x18]; // +0x04..+0x1B
	Holder00497DD6 m_1C; // +0x1C
	Holder00497DD6 m_20; // +0x20
	StringBase<char> m_24; // +0x24
	Holder00497DD6 m_28; // +0x28
	Holder00497DD6 m_2C; // +0x2C
	Holder00497DD6 m_30; // +0x30
	Holder00497DD6 m_34; // +0x34
	StringBase<char> m_38; // +0x38
	Holder00497DD6 m_3C; // +0x3C
	Holder00497DD6 m_40; // +0x40
	Holder00497DD6 m_44; // +0x44
	StringBase<char> m_48; // +0x48
	Holder00497DD6 m_4C; // +0x4C
	char m_pad50[0xA4 - 0x50]; // +0x50..+0xA3
	StringBase<char> m_A4; // +0xA4
};

Rva00497DD6::~Rva00497DD6()
{
}
