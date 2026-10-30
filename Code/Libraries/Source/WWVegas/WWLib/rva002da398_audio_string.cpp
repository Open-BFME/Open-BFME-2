// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?Rva002DA398Get@@YA?AVAsciiString@@H@Z @0x002DA398 124B: audio-tagged
// string builder: local from TheEmptyString, if n==2 set g_00BBD3EC then
// concat TheAudio virtual-slot-77 result +0x14 string, copy-construct sret,
// return sret.
// Evidence: copy ctor 0x000365F0; set 0x000055F5; concat 0x00006987;
// releaseBuffer 0x00036410; TheEmptyString 0x009E0878; g_00BBD3EC;
// TheAudio 0x009FE6E8 with virtual at +0x134; callers 0x002DA7FA 0x002DA9D2.
#include "ascii_string.h"

extern const char g_00BBD3EC[];

struct AudioData
{
	char m_pad[4];
	AsciiString m_soundsFolder;
	AsciiString m_musicFolder;
	AsciiString m_C;
	AsciiString m_ambientStreamFolder;
	AsciiString m_str; // +0x14
};

struct AudioData;
struct Rva002D9D7CRef;
class Xfer;
class BfmePoolRef10;

class AudioManager
{
public:
	virtual void _pad00() = 0;
	virtual void _pad01() = 0;
	virtual void _pad02() = 0;
	virtual void _pad03() = 0;
	virtual void _pad04() = 0;
	virtual void _pad05() = 0;
	virtual void _pad06() = 0;
	virtual void _pad07() = 0;
	virtual void _pad08() = 0;
	virtual void _pad09() = 0;
	virtual void _pad10() = 0;
	virtual void _pad11() = 0;
	virtual void _pad12() = 0;
	virtual void _pad13() = 0;
	virtual void _pad14() = 0;
	virtual void _pad15() = 0;
	virtual void _pad16() = 0;
	virtual void _pad17() = 0;
	virtual void _pad18() = 0;
	virtual void _pad19() = 0;
	virtual void _pad20() = 0;
	virtual void _pad21() = 0;
	virtual void _pad22() = 0;
	virtual void _pad23() = 0;
	virtual void _pad24() = 0;
	virtual void _pad25() = 0;
	virtual void _pad26() = 0;
	virtual void _pad27() = 0;
	virtual void _pad28() = 0;
	virtual int a29(void *o, int x) = 0;
	virtual void _pad30() = 0;
	virtual void _pad31() = 0;
	virtual void _pad32() = 0;
	virtual void _pad33() = 0;
	virtual void _pad34() = 0;
	virtual void _pad35() = 0;
	virtual void _pad36() = 0;
	virtual void _pad37() = 0;
	virtual void _pad38() = 0;
	virtual void _pad39() = 0;
	virtual void _pad40() = 0;
	virtual void _pad41() = 0;
	virtual void _pad42() = 0;
	virtual void _pad43() = 0;
	virtual void _pad44() = 0;
	virtual void _pad45() = 0;
	virtual void _pad46() = 0;
	virtual void _pad47() = 0;
	virtual void _pad48() = 0;
	virtual void _pad49() = 0;
	virtual void _pad50() = 0;
	virtual void _pad51() = 0;
	virtual bool slotD0(int v) = 0;
	virtual void _pad53() = 0;
	virtual void _pad54() = 0;
	virtual void _pad55() = 0;
	virtual void _pad56() = 0;
	virtual void _pad57() = 0;
	virtual void _pad58() = 0;
	virtual void _pad59() = 0;
	virtual void _pad60() = 0;
	virtual void _pad61() = 0;
	virtual void _pad62() = 0;
	virtual void _pad63() = 0;
	virtual void _pad64() = 0;
	virtual void _pad65() = 0;
	virtual void _pad66() = 0;
	virtual void _pad67() = 0;
	virtual void _pad68() = 0;
	virtual void _pad69() = 0;
	virtual void _pad70() = 0;
	virtual void _pad71() = 0;
	virtual void _pad72() = 0;
	virtual void _pad73() = 0;
	virtual void _pad74() = 0;
	virtual Rva002D9D7CRef a75(const AsciiString *name) = 0;
	virtual void _pad76() = 0;
	virtual AudioData *slot134() = 0;
	virtual void _pad78() = 0;
	virtual void _pad79() = 0;
	virtual void _pad80() = 0;
	virtual void _pad81() = 0;
	virtual void _pad82() = 0;
	virtual void _pad83() = 0;
	virtual void _pad84() = 0;
	virtual void _pad85() = 0;
	virtual void _pad86() = 0;
	virtual void _pad87() = 0;
	virtual void _pad88() = 0;
	virtual void _pad89() = 0;
	virtual void _pad90() = 0;
	virtual void _pad91() = 0;
	virtual void _pad92() = 0;
	virtual void _pad93() = 0;
	virtual void _pad94() = 0;
	virtual void _pad95() = 0;
	virtual void _pad96() = 0;
	virtual void _pad97() = 0;
	virtual void _pad98() = 0;
	virtual void _pad99() = 0;
	virtual void _pad100() = 0;
	virtual void _pad101() = 0;
	virtual void _pad102() = 0;
	virtual void a103(Xfer *xfer, BfmePoolRef10 *ref) = 0;
};

extern AudioManager *TheAudio;

AsciiString Rva002DA398Get(int n)
{
	AsciiString tmp = AsciiString::TheEmptyString;
	if (n == 2) {
		((StringBase<char> *)&tmp)->set(g_00BBD3EC);
		((StringBase<char> *)&tmp)->concat(
			*(const StringBase<char> *)&TheAudio->slot134()->m_str);
	}
	return tmp;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_00BBD3EC@@3QBDB=??_C@_01LFCBOECM@?4?$AA@")
