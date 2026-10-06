// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /Oi-
// stlport
// ?Rva00464574Parse@@YAXPAVINI@@PAX1PBX@Z @0x00464574 280B: OpenContain passenger-bone entry parser (PassengerBone KindOf pair into list at instance+0x48).
// Evidence: BFME1 donor Rva002274A0ParsePassengerBone.cpp same shape (getNextToken sepsColon +0x420 vs +0x41C, parseAsciiString boneName, KindOf worker, rep-movsd entry assign, push_back list at +0x48 vs +0x11C); retail callees getNextToken 0x2DF97 parseAsciiString 0x2F11E rva00256499 0x256499 StringBase set 0x366F0 push_back 0x4643CE releaseBuffer 0x36410 INIException 0x2F681; Rva00463235Finish proves list at +0x48 holds 28B KindOf + AsciiString bone records.
#include "ascii_string.h"

extern "C" int __cdecl strcmp(const char *, const char *);
extern "C" void *__cdecl memset(void *, int, unsigned int);

class INI
{
public:
	char m_pad[0x420];
	const char *sepsColon;
	const char *getNextToken(const char *seps);
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
};

class INIException
{
public:
	INIException(int argumentCount, const char *format, ...);
	char *mFailureMessage;
	int m_argumentCount;
	INIException(const INIException &that);
	~INIException();
};

class Rva00256499
{
public:
	void rva00256499(INI *ini, void *extra);
	unsigned int m_bits[7];
	Rva00256499() { memset(m_bits, 0, sizeof(m_bits)); }
};

struct BfmeContainerRecord00462D62
{
	Rva00256499 storage;
	AsciiString text;
};

namespace _STL
{
	template <class T> class allocator;
	template <class T, class Alloc> class list
	{
	public:
		void push_back(const T &value);
	};
}

void Rva00464574Parse(INI *ini, void *instance, void *, const void *)
{
	Rva00256499 kindOf;
	AsciiString boneName;
	BfmeContainerRecord00462D62 entry;

	const char *token = ini->getNextToken(ini->sepsColon);
	if (token == 0 || strcmp(token, "PassengerBone") != 0)
		throw INIException(3, "PassengerBone expected");

	INI::parseAsciiString(ini, instance, &boneName, 0);

	token = ini->getNextToken(ini->sepsColon);
	if (token == 0 || strcmp(token, "KindOf") != 0)
		throw INIException(3, "KindOf expected");

	kindOf.rva00256499(ini, 0);
	entry.storage = kindOf;
	entry.text = boneName;
	((_STL::list<BfmeContainerRecord00462D62, _STL::allocator<BfmeContainerRecord00462D62> > *)((char *)instance + 0x48))->push_back(entry);
}
