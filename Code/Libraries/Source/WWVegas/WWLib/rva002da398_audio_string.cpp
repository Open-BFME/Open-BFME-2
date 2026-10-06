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

struct AudioStringHolder
{
	char m_pad[0x14];
	AsciiString m_str;
};

class AudioManager
{
public:
	virtual void _u000();
	virtual void _u001();
	virtual void _u002();
	virtual void _u003();
	virtual void _u004();
	virtual void _u005();
	virtual void _u006();
	virtual void _u007();
	virtual void _u008();
	virtual void _u009();
	virtual void _u010();
	virtual void _u011();
	virtual void _u012();
	virtual void _u013();
	virtual void _u014();
	virtual void _u015();
	virtual void _u016();
	virtual void _u017();
	virtual void _u018();
	virtual void _u019();
	virtual void _u020();
	virtual void _u021();
	virtual void _u022();
	virtual void _u023();
	virtual void _u024();
	virtual void _u025();
	virtual void _u026();
	virtual void _u027();
	virtual void _u028();
	virtual void _u029();
	virtual void _u030();
	virtual void _u031();
	virtual void _u032();
	virtual void _u033();
	virtual void _u034();
	virtual void _u035();
	virtual void _u036();
	virtual void _u037();
	virtual void _u038();
	virtual void _u039();
	virtual void _u040();
	virtual void _u041();
	virtual void _u042();
	virtual void _u043();
	virtual void _u044();
	virtual void _u045();
	virtual void _u046();
	virtual void _u047();
	virtual void _u048();
	virtual void _u049();
	virtual void _u050();
	virtual void _u051();
	virtual void _u052();
	virtual void _u053();
	virtual void _u054();
	virtual void _u055();
	virtual void _u056();
	virtual void _u057();
	virtual void _u058();
	virtual void _u059();
	virtual void _u060();
	virtual void _u061();
	virtual void _u062();
	virtual void _u063();
	virtual void _u064();
	virtual void _u065();
	virtual void _u066();
	virtual void _u067();
	virtual void _u068();
	virtual void _u069();
	virtual void _u070();
	virtual void _u071();
	virtual void _u072();
	virtual void _u073();
	virtual void _u074();
	virtual void _u075();
	virtual void _u076();
	virtual AudioStringHolder *rva077();
};

extern AudioManager *TheAudio;

AsciiString Rva002DA398Get(int n)
{
	AsciiString tmp = AsciiString::TheEmptyString;
	if (n == 2) {
		((StringBase<char> *)&tmp)->set(g_00BBD3EC);
		((StringBase<char> *)&tmp)->concat(
			*(const StringBase<char> *)&TheAudio->rva077()->m_str);
	}
	return tmp;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_00BBD3EC@@3QBDB=??_C@_01LFCBOECM@?4?$AA@")
