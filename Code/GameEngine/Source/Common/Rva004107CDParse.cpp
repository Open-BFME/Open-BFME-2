// cl: /Ireference/shims/bfme2_ascii /O1 /EHs /MD
// ?Rva004107CDParse@@YAXPAXPBD@Z @0x004107CD 321B: free cdecl parsing _light and _frame= tokens via GetParam plus sscanf plus virtuals at +0x10 +0x14 plus AsciiString at +8.
// Evidence: callers at 0x004120E4 with void-star plus char-star plus caller-cleaned 8B; strings _light _frame= _AnimMode plus "%d=%f,%f,%f" plus IAT _strnicmp sscanf atoi isdigit; rowed StringBase compare set releaseBuffer plus pin Rva004128F0GetParam; vtable offsets +0x10 int-float-float-float plus +0x14 int-AsciiString.
#include "ascii_string.h"

class Rva004107CDObj
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void SetLight(int n, float x, float y, float z);
	virtual void SetFrame(int f, AsciiString &mode);
};

bool __cdecl Rva004128F0GetParam(const char *params, const char *key, AsciiString &value);
extern "C" __declspec(dllimport) int __cdecl _strnicmp(const char *a, const char *b, unsigned int n);
extern "C" __declspec(dllimport) int __cdecl sscanf(const char *buf, const char *fmt, ...);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *s);
extern "C" __declspec(dllimport) int __cdecl isdigit(int c);

void __cdecl Rva004107CDParse(void *obj_, const char *params)
{
	Rva004107CDObj *obj = (Rva004107CDObj *)obj_;
	if (obj == 0)
		return;
	if (params == 0)
		return;
	if (*params == 0)
		return;
	AsciiString &stored = *(AsciiString *)((char *)obj + 8);
	if (((StringBase<char> &)stored).compare(params) == 0)
		return;
	((StringBase<char> &)stored).set(params);
	const char *s = params;
	for (;;) {
		if (_strnicmp(s, "_light", 6) == 0 && isdigit(s[6])) {
			const char *p = s + 6;
			s = p;
			int n = 0;
			float x = 1.0f;
			float y = 1.0f;
			float z = 1.0f;
			sscanf(s, "%d=%f,%f,%f", &n, &x, &y, &z);
			obj->SetLight(n, x, y, z);
		} else if (_strnicmp(s, "_frame=", 7) == 0) {
			AsciiString mode;
			Rva004128F0GetParam(params, "_AnimMode", mode);
			int f = atoi(s + 7);
			obj->SetFrame(f, mode);
		}
		while (*s) {
			char c = *s++;
			if (c == '&')
				break;
		}
		if (*s == 0)
			return;
	}
}
