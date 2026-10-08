// cl: /MD /Ireference/shims/bfme2_ascii
// ?rva004214C3@Rva004214C3@@QAEXPBVModuleData@@@Z @0x004214C3 93B
// Add-if-absent with duplicate throw: Find via rowed 0x00421263 then INIException
// 0x0002F681 on dup else push_back via rowed 0x004DFCB0. Evidence: chain lane;
// vec at +c and key at arg+0x10; callers 0x0042167C; neighbours share /O1.
#include "ascii_string.h"

class ModuleData
{
public:
	char m_pad[16];
	StringBase<char> m_name;
};

struct Rva00421263Vec
{
	const ModuleData **m_begin;
	const ModuleData **m_end;
};

const ModuleData *__stdcall Rva00421263Find(const Rva00421263Vec *vec, const StringBase<char> &key);

namespace _STL
{
template <class T> class allocator
{
};
template <class T, typename A = allocator<T> > class vector
{
public:
	void push_back(const T &value);
};
}

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *format, ...);
};

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
struct Rva004214C3ThrowInfoAnchor { int a; int b; int c; int d; };
static const Rva004214C3ThrowInfoAnchor rva004214C3ThrowInfoAnchor = { 0, 0, 0, 0 };


class Rva004214C3
{
public:
	void rva004214C3(const ModuleData *data);
private:
	char m_pad[12];
	_STL::vector<const ModuleData *> m_vec;
};

void Rva004214C3::rva004214C3(const ModuleData *data)
{
	const ModuleData *found = Rva00421263Find((const Rva00421263Vec *)&m_vec, data->m_name);
	if (found) {
		char *t = *(char **)&found->m_name;
		const char *s = t ? t + 8 : "";
		INIException exc(3, "A light point level %s already exists.", s);
		_CxxThrowException(&exc, (const _s__ThrowInfo *)&rva004214C3ThrowInfoAnchor); __assume(0);
	}
	m_vec.push_back(data);
}
