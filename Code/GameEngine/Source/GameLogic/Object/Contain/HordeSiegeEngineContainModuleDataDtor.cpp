// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
//
// ??1HordeSiegeEngineContainModuleData@@UAE@XZ, retail 0x0047DA99, 74 bytes.
// Target evidence: audited scalar deleting dtor 0x0047DA7D (vtable
// 0x00C47520) calls this body; SiegeEngineContainModuleDataDtor.cpp has the
// identical SiegeEngine twin (0x0047C9CB). This body
// destroys the +0x194 string (0x00036410) and the +0x18C filter member
// (0x00360D26), then calls ~TransportContainModuleData 0x004684F1 directly:
// SiegeEngine derives from TransportContainModuleData (ctor 0x0047C927 base
// call 0x00468301); HordeSiegeEngine derives from HordeTransport, whose empty
// dtor inlines away. Retail stores no vptr (novtable). Member layout from the
// matched ctors 0x0047C927 / 0x0047DA08.

#include "ascii_string.h"

class Rva003623E5Member
{
public:
	~Rva003623E5Member();

private:
	int m_x;
};

class TransportContainModuleData
{
public:
	virtual ~TransportContainModuleData();

private:
	unsigned char m_opaque[0x18C - 4];
};

class __declspec(novtable) HordeTransportContainModuleData : public TransportContainModuleData
{
public:
	virtual ~HordeTransportContainModuleData() {}
};

class __declspec(novtable) HordeSiegeEngineContainModuleData : public HordeTransportContainModuleData
{
public:
	virtual ~HordeSiegeEngineContainModuleData();

private:
	Rva003623E5Member m_member18C;	// +0x18C
	int m_int190;			// +0x190
	AsciiString m_string194;	// +0x194
};

HordeSiegeEngineContainModuleData::~HordeSiegeEngineContainModuleData()
{
}
