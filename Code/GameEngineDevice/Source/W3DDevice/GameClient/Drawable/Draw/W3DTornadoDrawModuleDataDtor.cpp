// cl: /MD /EHsc /DNDEBUG /Ireference/shims/moduledata
//
// ??1W3DTornadoDrawModuleData@@UAE@XZ, retail 0x000D1713, 48 bytes.
// Target evidence: the audited scalar deleting dtor 0x000D16F7 calls this
// body (registration W3DTornadoDraw -> factory 0x00065171 -> ctor
// 0x000D16B4). It destroys the two-string record at +0x08 (0x000B6CF1), then
// the inlined trivial Snapshot base stores vtable 0x00BBB554. No derived vptr
// store (novtable). The +0x04 slot holds no destructible member.

#include "Common/Snapshot.h"

class BfmeStringRecord000B94D2
{
public:
	~BfmeStringRecord000B94D2();

private:
	void *m_strings[2];
};

class __declspec(novtable) W3DTornadoDrawModuleData : public Snapshot
{
public:
	virtual ~W3DTornadoDrawModuleData();

private:
	int m_04;
	BfmeStringRecord000B94D2 m_record;	// +0x08
};

W3DTornadoDrawModuleData::~W3DTornadoDrawModuleData()
{
}
