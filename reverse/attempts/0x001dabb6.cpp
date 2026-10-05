// ?Rva001DABB6Parse@@YAXPAVINI@@PAXPAH1@Z
// partial score=0.97 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva001DABB6Parse@@YAXPAVINI@@PAXPAH1@Z @0x001DABB6 391B. INI sounds-list parse
// adapted from BFME1 AudioEventRTSParseSoundsList.cpp: file[:weight] tokens
// default weight 1000 appended as owning string/int entry with optional total
// accumulation; both INIException messages are retail literals. Evidence: rowed
// 0x0002DEED 0x00037B80 0x000366F0 0x00036410 0x000365F0 0x001DAAF2 0x0002F681
// plus pin 0x00629094 plus IAT isdigit atoi plus literals plus empty-string
// global g_Rva0107301CEmptyString plus TI1?AVINIException@@.
#include "ascii_string.h"
#include <new>
#define _OPERATOR_NEW_DEFINED_
#include <string.h>
extern "C" __declspec(dllimport) int __cdecl atoi(const char *text);
extern "C" __declspec(dllimport) int __cdecl isdigit(int c);
class INI
{
public:
	const char *getNextTokenOrNull(const char *s);
};
class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int m_argCount;
	INIException(const INIException &that);
	~INIException();
};
struct Rva001DAAF2Element {
	AsciiString name;
	int weight;
	Rva001DAAF2Element(const AsciiString &text, int value) : name(text), weight(value) {}
};
namespace _STL {
template <class T, class A> class vector
{
public:
	void push_back(const T &x);
};
template <class T> class allocator
{
};
}
typedef _STL::vector<Rva001DAAF2Element, _STL::allocator<Rva001DAAF2Element> > Rva001DAAF2Vec;
extern const char g_Rva0107301CEmptyString[];
// ?Rva001DABB6Parse@@YAXPAVINI@@PAXPAH1@Z present-unmatched
void __cdecl Rva001DABB6Parse(INI *ini, void *store, int *totalWeight, void *instance)
{
	const char *token = ini->getNextTokenOrNull(0);
	while (token) {
		int tokenLength = strlen(token);
		if (tokenLength) {
			const char *end = token + tokenLength - 1;
			while (end > token && isdigit(*end))
				--end;
			int weight;
			AsciiString name;
			if (*end == ':') {
				weight = atoi(++end);
				if (weight < 1)
					throw INIException(3, "Weight of sound files must be >= 1. Sound '%s' for audio event '%s'", token, *(const char **)instance ? *(const char **)instance + 8 : g_Rva0107301CEmptyString);
				name = AsciiString(token, end - token - 1);
			} else {
				weight = 1000;
				name = AsciiString(token, tokenLength);
			}
			if (name.isEmpty())
				throw INIException(3, "Sound file has no file name. Sound '%s' for audio event '%s'", token, *(const char **)instance ? *(const char **)instance + 8 : g_Rva0107301CEmptyString);
			((Rva001DAAF2Vec *)store)->push_back(Rva001DAAF2Element(name, weight));
			if (totalWeight)
				*totalWeight += weight;
		}
		token = ini->getNextTokenOrNull(0);
	}
}
