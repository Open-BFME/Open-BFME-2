// cl: /O1 /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva0022DDF4@@QAE@XZ @0x0022DDF4 53B: opaque non-virtual dtor.
// Evidence: calls rowed MapMetaData dtor 0x0022DBC6 at +4 then pinned
// StringBase<char> dtor 0x00036410 at +0; no vtable store; EH states 0/-1.
// Prev 0x0022DBC6 (MapMetaData dtor) and next 0x00232920 share no TU; new file
// beside MapMetaDataCopy.cpp copies its // cl: line. MapMetaData size 0x100
// from its SizeCheck; owner identity unproven, honest Rva name.
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class MapMetaData
{
public:
	~MapMetaData();
private:
	char m_pad[0x100];
};

class Rva0022DDF4
{
public:
	~Rva0022DDF4();
private:
	AsciiString m_str;
	MapMetaData m_data;
};

Rva0022DDF4::~Rva0022DDF4()
{
}

// ?forceRva0022DDF4Delete@@YAXPAVRva0022DDF4@@@Z absent-from-retail
void forceRva0022DDF4Delete(Rva0022DDF4 *p) { delete p; }
