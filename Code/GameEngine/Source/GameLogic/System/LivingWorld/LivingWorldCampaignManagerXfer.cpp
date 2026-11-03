// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
//
// ?rva003B8F76@Rva003B8F76@@QAEXPAVXfer@@@Z, retail 0x003B8F76..0x003B9051 (213
// bytes, EH, thiscall RET 4): the Xfer method of the secondary interface that the
// LivingWorldCampaignManager carries at +0xC (its primary receiver is this - 0xC;
// the primary lookup 0x003B8E2B is rowed in LivingWorldCampaignManager.cpp). Unless
// the stream is a light CRC: transfer a version 1, then the name of the current
// campaign entry (loading: read the name, resolve it through the rowed lookup and
// store the index; saving: copy the entry's name from +4) and let the entry
// transfer itself (its virtual slot +0xC), then transfer the flag at +0x20.
// Evidence (target): native bytes, Xfer slots +0x04 IsLoading / +0x10 IsLightCRC /
// +0x28 xferVersion / +0x6C xferAsciiString / +0x90 xferBool (the views of
// LivingWorldBattleResultsXfer.cpp and LivingWorldLogicXferStateRva002BB2B7.cpp);
// the member names are address-derived. No WorldBuilder twin matches this build
// (WB 0x010325A0 only supports the shape).
#include "ascii_string.h"
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
struct XferVersionFields
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};
union XferVersion
{
	XferVersionFields m_fields;
	UnsignedInt m_value;
};
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"

class Rva003B8F76;
#include "../../../../Include/Common/LivingWorldCampaignManager.h"

class Rva003B8F76Entry
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void xfer(Xfer *xfer);
	AsciiString m_name;
};

class Rva003B8F76
{
public:
	virtual void slot00();
	void rva003B8F76(Xfer *xfer);
private:
	int m_index;
	Rva003B8F76Entry **m_entries;
	char m_pad0c[0x14];
	Bool m_flag20;
};

void Rva003B8F76::rva003B8F76(Xfer *xfer)
{
	if (!xfer->IsLightCRC()) {
		XferVersion version;
		version.m_fields.m_version = 1;
		version.m_fields.m_currentVersion = 1;
		(*xfer == reinterpret_cast<Xfer::Version &>(version));
		if (xfer->IsLoading()) {
			AsciiString name;
			(*xfer == name);
			m_index = ((LivingWorldCampaignManager *)((char *)this - 0xC))->rva003B8E2B(name);
			m_entries[m_index]->xfer(xfer);
		} else {
			Rva003B8F76Entry **entries = m_entries;
			int i = m_index;
			AsciiString name(entries[i]->m_name);
			(*xfer == name);
			{ Rva003B8F76Entry **v = m_entries; v[m_index]->xfer(xfer); }
		}
		(*xfer == m_flag20);
	}
}
