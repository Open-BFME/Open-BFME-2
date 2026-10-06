// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// ??0TunnelContainModuleData@@QAE@XZ, retail 0x0025797E, 107 bytes
// (pinned). Over the rowed HordeGarrisonContainModuleData ctor 0x0047A251
// (its dtor 0x00257A05 is state 0 of retail's unwind map): set the float at
// +0xD4 to 1.0, then reset the inherited +0x40 filter through 0x00362192
// with BitSet(0, 8) and a copy of the default storage at 0x00DFEFA4, as in
// GarrisonContainModuleDataCtor.cpp.
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);
private:
	unsigned char m_bytes[0x1C];
};

class Rva00045411BitSet
{
public:
	Rva00045411BitSet(int a, int b);
	Rva00045411BitSet(const Rva00045411BitSet &other);
private:
	unsigned char m_bytes[0x1C];
};

extern const BfmeFixedStorage0004543D g_defaultStorage009FEFA4;

class Rva003623E5Member
{
public:
	void rva00362192(Rva00045411BitSet bits, BfmeFixedStorage0004543D storage);
private:
	unsigned char m_bytes[0x58];
};

#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"

class OpenContainModuleData
{
public:
	OpenContainModuleData();
	virtual ~OpenContainModuleData();
protected:
	unsigned char m_pad04[0x3C];
	Rva003623E5Member m_filter40;
};

class HordeGarrisonContainModuleData : public OpenContainModuleData
{
public:
	HordeGarrisonContainModuleData();
	virtual ~HordeGarrisonContainModuleData();
private:
	unsigned char m_pad98[0xD4 - 0x98];
};

class TunnelContainModuleData : public HordeGarrisonContainModuleData
{
public:
	TunnelContainModuleData();
private:
	float m_D4;
};

inline TunnelContainModuleData::TunnelContainModuleData()
{
	m_D4 = 1.0f;
	m_filter40.rva00362192(Rva00045411BitSet(0, 8), g_defaultStorage009FEFA4);
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_defaultStorage009FEFA4@@3VBfmeFixedStorage0004543D@@B=?g_00DFEFA4StoragePrototype@@3PAEA")

// TunnelContainModuleData ctor is a header inline elsewhere: another unit emits
// a select-any copy, so a strong definition here was a duplicate in the linked
// build. This anchor only makes this unit emit its copy for the ledger row; it
// is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitTunnelContainModuleDataCtor@@YAXPAVTunnelContainModuleData@@@Z present-unmatched
void bfmeEmitTunnelContainModuleDataCtor(TunnelContainModuleData *p)
{
	p->TunnelContainModuleData::TunnelContainModuleData();
}
#pragma inline_depth()
