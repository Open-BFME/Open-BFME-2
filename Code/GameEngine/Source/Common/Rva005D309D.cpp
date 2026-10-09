// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ??1Rva005D309D@@QAE@XZ @0x005D309D 81B
// Ctor5D3506 is called by wrapper5D3628 with level and string reference.
// Layout: level0/name4, six cached counters8..1C, three24B callback members
// at20/38/50 and visibility68. Original Impl name remains an address view.
// Dtor with AsciiString at +4 and three Rva005D2EA8 members at +0x20 +0x38 +0x50.
// Evidence: three calls to pinned ??1Rva005D2EA8@@UAE@XZ plus releaseBuffer
// 0x00036410 for AsciiString; callers at 0x005D3291 0x005D32B6 unblock
// 0x005D32AA; layout from idei offsets and Rva005D3731 AsciiString precedent.
#include "ascii_string.h"
#include "unicode_string.h"
namespace StrategicHUD {void SetString(unsigned int,const AsciiString &,const char *,const UnicodeString &);}
UnicodeString __cdecl Rva005D303AFormat(int,int);

class Rva005D2EA8
{
public:
	Rva005D2EA8(int,const AsciiString &,const char *);
	virtual ~Rva005D2EA8();
private:
	char m_pad[0x14];
};

class Rva005D309D
{
public:
	Rva005D309D(int,const AsciiString &);
	~Rva005D309D();
private:
	int m_00;
	AsciiString m_04;
	int m_08,m_0C,m_10,m_14,m_18,m_1C;
	Rva005D2EA8 m_20;
	Rva005D2EA8 m_38;
	Rva005D2EA8 m_50;
	bool m_visible;
};

Rva005D309D::~Rva005D309D()
{
}

Rva005D309D::Rva005D309D(int level,const AsciiString &name)
 :m_00(level),m_04(name),m_08(0),m_0C(0),m_10(0),m_14(0),m_18(0),m_1C(0),
 m_20(level,name,"BuildPlots"),m_38(level,name,"ArmoryPoints"),m_50(level,name,"CommandPoints"),m_visible(false)
{
 StrategicHUD::SetString(m_00,m_04,"BuildPlots",Rva005D303AFormat(m_08,m_0C));
 StrategicHUD::SetString(m_00,m_04,"ArmoryPoints",Rva005D303AFormat(m_10,m_14));
 StrategicHUD::SetString(m_00,m_04,"CommandPoints",Rva005D303AFormat(m_18,m_1C));
}
