// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva000C3B6EParse@INI@@SAXPAV1@PAX1PBX@Z @0x000C3B6E 235B.
// INI parse filling a stack BfmeStringRecord000B950F (frame int at +0,
// AsciiString data at +4, state at +8) by looping getNextTokenOrNull with
// m_sepsColon at ini+0x420: "Frame" via rowed parseInt 0x2EF56 then state 0,
// "Data" via rowed parseAsciiString 0x2F11E, "OnStateEnter"/"OnStateLeave"
// via strcmp to 1/2, then push_back through rowed vector push 0xC33DA at
// instance+0x90 and tear down through releaseBuffer 0x36410. Neighbours
// 0xC3824 and 0xC3C59 give the TU, flags and SAXPAV1@PAX1PBX@Z shape.
#include "ascii_string.h"

struct BfmeStringRecord000B950F
{
	BfmeStringRecord000B950F() : word0(0), word1(0) {}
	BfmeStringRecord000B950F(const BfmeStringRecord000B950F &o);
	unsigned int word0;
	AsciiString text;
	unsigned int word1;
};

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

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps);
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000C3B6EParse(INI *ini, void *instance, void *store, const void *userData);

private:
	char _pad[0x420];
	const char *m_sepsColon;
};

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);
extern "C" int __cdecl strcmp(const char *a, const char *b);

void INI::Rva000C3B6EParse(INI *ini, void *instance, void *store, const void *userData)
{
	if (!instance)
		return;
	BfmeStringRecord000B950F record;
	const char *token;
	for (token = ini->getNextTokenOrNull(ini->m_sepsColon); token != 0; token = ini->getNextTokenOrNull(ini->m_sepsColon)) {
		if (_strcmpi(token, "Frame") == 0) {
			INI::parseInt(ini, 0, &record.word0, 0);
			record.word1 = 0;
		} else if (_strcmpi(token, "Data") == 0) {
			INI::parseAsciiString(ini, 0, &record.text, 0);
		} else if (strcmp(token, "OnStateEnter") == 0) {
			record.word1 = 1;
		} else if (strcmp(token, "OnStateLeave") == 0) {
			record.word1 = 2;
		}
	}
	((_STL::vector<BfmeStringRecord000B950F> *)((char *)instance + 0x90))->push_back(record);
}
