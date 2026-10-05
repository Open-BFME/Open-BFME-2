// cl: /Ireference/shims/bfme2_ascii /O1 /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?Rva0002CEB5ApplyFields@@YA_NPAXPBUFieldParse@@PAURva0002CF86View@@@Z @0x0002CEB5 (169B)
// and ?Rva0002CF86MixerFieldEdit@@YAXXZ @0x0002CF86 (291B).
//
// Target evidence: 0x0002CF86 opens the 0x1C4-byte shared mapping
// "_mappedMixerFile" (CreateFileMappingA / MapViewOfFile imports 0x00BBA1AC /
// 0x00BBA1A8), names an object by the C string at view+4 and looks it up first
// in the vector at 0x00DDF580 (each entry carries an AsciiString at +4, compared
// via rowed 0x000069D6; the registry 0x00200D38 fills), then through rowed
// 0x001B4F8B on the list at 0x00DFD940 (TheSubsystemList). The match hands its
// instance (slot 0 or the subsystem itself) and field table (slot 2 or
// subsystem slot 6) to 0x0002CEB5, which builds a stack INI (rowed ctor
// 0x0002CDB0 / dtor 0x0002CE5B), pushes the view's tokens back in reverse
// through rowed 0x0002CBCC, finds the field named at view+0x24 with the
// TU-local copy of findFieldParse (retail calls 0x0002BC27 with its private
// register convention: eax table, ebx &offset, edi &userData) and runs the
// parser under catch(...). Unmap and CloseHandle follow (0x00BBA11C,
// 0x00BBA180). Structural inference: a development-time live tweak hook for
// INI fields ("mixer"); the original names are not recovered.

#include <string.h>
#include <vector>

#include "ascii_string.h"

typedef void *HANDLE;
typedef int BOOL;
typedef unsigned long DWORD;

#define WINAPI __stdcall

extern "C" __declspec(dllimport) HANDLE WINAPI CreateFileMappingA(HANDLE hFile, void *lpAttributes, DWORD flProtect,
	DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, const char *lpName);
extern "C" __declspec(dllimport) void *WINAPI MapViewOfFile(HANDLE hFileMappingObject, DWORD dwDesiredAccess,
	DWORD dwFileOffsetHigh, DWORD dwFileOffsetLow, DWORD dwNumberOfBytesToMap);
extern "C" __declspec(dllimport) BOOL WINAPI UnmapViewOfFile(const void *lpBaseAddress);
extern "C" __declspec(dllimport) BOOL WINAPI CloseHandle(HANDLE hObject);

class INI
{
public:
	INI();
	~INI();

	void rva0002CBCC(const AsciiString &text, char separator);

private:
	char m_body[0x87C]; // INI_ctor.cpp's layout, 0x87C bytes in all
};

typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);

struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

// ?findFieldParse present-unmatched
static INIFieldParseProc findFieldParse(const FieldParse *parseTable, const char *token, int &offset, const void *&userData)
{
	const FieldParse *parse = parseTable;
	for (; parse->token; ++parse)
	{
		if (strcmp(parse->token, token) == 0)
		{
			offset = parse->offset;
			userData = parse->userData;
			return parse->parse;
		}
	}

	if (!parse->token && parse->parse)
	{
		offset = parse->offset;
		userData = token;
		return parse->parse;
	}
	else
	{
		return NULL;
	}
}

struct Rva0002CF86View
{
	int count;             // +0x000
	char objectName[32];   // +0x004
	char fieldName[32];    // +0x024
	char tokens[12][32];   // +0x044
};

bool Rva0002CEB5ApplyFields(void *instance, const FieldParse *table, Rva0002CF86View *view)
{
	INI ini;

	for (int i = view->count - 1; i >= 0; --i)
		ini.rva0002CBCC(AsciiString(view->tokens[i]), ' ');

	int offset = 0;
	const void *userData = 0;
	INIFieldParseProc parse = findFieldParse(table, view->fieldName, offset, userData);
	if (parse)
	{
		try
		{
			parse(&ini, instance, (char *)instance + offset, userData);
		}
		catch (...)
		{
		}
		return true;
	}
	return false;
}

class ModuleData;
extern _STL::vector<const ModuleData *> g_vec00200D38; // Rva00200D38Ctor.cpp, VA 0x00DDF580

// The registry entries 0x00200D38 constructs: three-slot table at +0, name at +4.
class Rva00200D38
{
public:
	virtual void *slot0() = 0;
	virtual void slot1() = 0;
	virtual const FieldParse *slot2() = 0;

	AsciiString m_name;
};

// A SubsystemInterface found by name; table slot 6 (+0x18) yields its field table.
class Rva0002CF86Subsystem
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual const FieldParse *slot6();
};

class Rva001B4F8B
{
public:
	void *rva001B4F8B(const StringBase<char> &name);
};

class SubsystemInterfaceList;
extern SubsystemInterfaceList *TheSubsystemList;

// ?Rva0002CF86MixerFieldEdit present-unmatched
void Rva0002CF86MixerFieldEdit()
{
	HANDLE mapping = CreateFileMappingA((HANDLE)-1, 0, 4, 0, sizeof(Rva0002CF86View), "_mappedMixerFile");
	Rva0002CF86View *view = (Rva0002CF86View *)MapViewOfFile(mapping, 6, 0, 0, 0);
	if (!view)
		return;

	AsciiString name(view->objectName);

	for (const ModuleData **it = g_vec00200D38.begin(); it != g_vec00200D38.end(); ++it)
	{
		Rva00200D38 *entry = (Rva00200D38 *)*it;
		if (entry->m_name.compare(name) == 0)
		{
			Rva0002CEB5ApplyFields(entry->slot0(), entry->slot2(), view);
			entry->slot1();
			goto done;
		}
	}

	{
		Rva0002CF86Subsystem *subsystem = (Rva0002CF86Subsystem *)((Rva001B4F8B *)TheSubsystemList)
			->rva001B4F8B(*(const StringBase<char> *)&AsciiString(view->objectName));
		if (subsystem && subsystem->slot6())
			Rva0002CEB5ApplyFields(subsystem, subsystem->slot6(), view);
	}

done:
	UnmapViewOfFile(view);
	CloseHandle(mapping);
}
