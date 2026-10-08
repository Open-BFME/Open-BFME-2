// ?Rva004118B4@@YAPAXPBD0@Z
// partial score=0.995 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc /Ireference/open-bfme-1/inputs/reference/shims/stringinline /O1 /arch:SSE /G7
// ?Rva004118B4@@YAPAXPBD0@Z @0x004118B4 319B
// Apt asset creator called by Rva004120B3 with path and parameters: resolves
// the leaf, reads _RenderObj _KeepAspectRatio _AnimMode via pinned GetParam,
// creates the Rva00789900Init via rowed Create with KeepAspect as uchar,
// stores the level and dot-path position via virtual slot 0xC, then indexes
// the Rva000427195 table at 0xA02FF8. Evidence: caller 0x004120D3 passes
// path+params; strings _RenderObj _KeepAspectRatio _AnimMode; callees
// bfmePathLeafAfterMarker GetParam find Create GetLevel SlashPath2DotPath
// rva004112A0 releaseBuffer StringBase ctor; global g_00E02FF8;
// sbb-inc is unsigned char per shape guide.
#include "ascii_string.h"

const char *__cdecl bfmePathLeafAfterMarker(const char *path);
bool __cdecl Rva004128F0GetParam(const char *params, const char *key, AsciiString &value);
int __cdecl Rva004128BBGetLevel(const char *path);

class Rva00789900Init
{
public:
	virtual void f0();
	virtual void f1();
	virtual void gap08();
	virtual void f2(const AsciiString &dotPath, const AsciiString &renderObj, const AsciiString &animMode);
	int m_04;
};

Rva00789900Init *__cdecl Rva00740A45Create(unsigned char keep);

namespace AptUtils
{
	AsciiString SlashPath2DotPath(const char *path);
}

class Rva000427195
{
public:
	void *rva004112A0(const AsciiString *key);
};
extern unsigned int g_00E02FF8;

void *Rva004118B4(const char *path, const char *params)
{
	const char *leaf = bfmePathLeafAfterMarker(path);
	AsciiString renderObj;
	if (Rva004128F0GetParam(params, "_RenderObj", renderObj) == false)
		return 0;
	if (renderObj.isEmpty())
		return 0;
	AsciiString keepStr;
	Rva004128F0GetParam(params, "_KeepAspectRatio", keepStr);
	unsigned char keep = (unsigned char)(keepStr.find('f') == 0);
	AsciiString animMode;
	Rva004128F0GetParam(params, "_AnimMode", animMode);
	Rva00789900Init *obj = Rva00740A45Create(keep);
	obj->f1();
	obj->m_04 = Rva004128BBGetLevel(path);
	obj->f2(AptUtils::SlashPath2DotPath(path), renderObj, animMode);
	AsciiString leafStr(leaf);
	void **slot = (void **)((Rva000427195 *)&g_00E02FF8)->rva004112A0(&leafStr);
	*slot = obj;
	return obj;
}
