// cl: /Ireference/shims/bfme2_ascii /GX /DNDEBUG /MD
//
// ?Rva000C2B23_ParseModelName@INI@@SAXPAV1@PAX1PBX@Z, retail 0x000C2B23
// (174B): the Model row (0x00BCAB20) of the W3DModelDraw condition-state table.
// Each Model line replaces the condition's model-name list at +0x4C (rowed
// vector<AsciiString> erase 0x0002CCFC) unless it is followed by
// "ExtraMesh <true>", then appends the name (rowed push_back 0x0002DBE6).
// Separators come from the INI's +0x420 field. Name address-derived.

#include "ascii_string.h"

#define NULL 0

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps = 0);
	bool scanBool(const char *token);
	static void Rva000C2B23_ParseModelName(INI *ini, void *instance, void *store, const void *userData);
	const char *separators() const { return m_separators; }
private:
	unsigned char m_unreconstructed_000[0x420];
	const char *m_separators;		// +0x420
};

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector;
template <> class vector<AsciiString, allocator<AsciiString> >
{
public:
	AsciiString *begin() { return m_start; }
	AsciiString *end() { return m_finish; }
	AsciiString *erase(AsciiString *first, AsciiString *last);
	void clear() { erase(begin(), end()); }
	void push_back(const AsciiString &x);
private:
	AsciiString *m_start;
	AsciiString *m_finish;
	AsciiString *m_endOfStorage;
};
}

struct Rva000C2B23Condition
{
	unsigned char m_unreconstructed_00[0x4C];
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_modelNames;	// +0x4C
};

void INI::Rva000C2B23_ParseModelName(INI *ini, void *instance, void *, const void *)
{
	Rva000C2B23Condition *self = (Rva000C2B23Condition *)instance;
	if (self == NULL)
		return;

	const char *name = ini->getNextTokenOrNull(ini->separators());
	if (name == NULL)
		return;

	const char *token = ini->getNextTokenOrNull(ini->separators());
	if (token == NULL || _strcmpi(token, "ExtraMesh") != 0 ||
		(token = ini->getNextTokenOrNull(NULL)) == NULL || !ini->scanBool(token))
	{
		self->m_modelNames.clear();
	}
	AsciiString tmp(name);
	self->m_modelNames.push_back(tmp);
}
