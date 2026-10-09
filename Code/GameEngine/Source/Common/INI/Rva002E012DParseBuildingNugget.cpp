// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?Rva002E012DParse@@YAXPAVINI@@PAX1PBX@Z, retail 0x002E012D 153B (EH).
// The "BuildingNugget" field parser of the Living World building template
// table (entry 0x00804310 beside "AvailableTo" Rva002E2612Parse; WorldBuilder
// twin 0x00DA2A10 by its duplicate-tag literal). Takes the nugget the rowed
// factory parse Rva0052B8ED_ParseNugget (0x0052B8ED) hands out as an
// auto_ptr; throws an INIException (rowed ctor 0x0002F681) when the rowed
// linear search Rva002DFBECFind (0x002DFBEC) finds the nugget's +0x04 tag in
// the store already; otherwise appends the released pointer to the store's
// pointer vector (ICF-folded push_back 0x004DFCB0 under its row spelling).
// Identities of the nugget and the store stay address-derived.
#include <memory>
#include <vector>
#include "ascii_string.h"

class INI;
class ModuleData;

class INIException
{
public:
	INIException(int argCount, const char *format, ...);	// 0x0002F681
	INIException(const INIException &that);
	~INIException();
private:
	char *m_failureMessage;
	int m_argCount;
};

class Rva0052B685Pointee
{
public:
	virtual ~Rva0052B685Pointee();
	AsciiString m_tag;	// +0x04
};

_STL::auto_ptr<Rva0052B685Pointee> Rva0052B8ED_ParseNugget(INI *ini);

struct Rva002DFBECRange;
void *Rva002DFBECFind(const Rva002DFBECRange *range, const AsciiString &key);

typedef _STL::vector<const ModuleData *> Rva002E012DNuggets;

void Rva002E012DParse(INI *ini, void *, void *store, const void *)
{
	_STL::auto_ptr<Rva0052B685Pointee> nugget = Rva0052B8ED_ParseNugget(ini);
	if (Rva002DFBECFind((const Rva002DFBECRange *)store, nugget->m_tag))
		throw INIException(1, "Duplicate nugget tags '%s' in Living World Building Template. Tags must be unique for a building type", nugget->m_tag.str());
	((Rva002E012DNuggets *)store)->push_back((const ModuleData *)nugget.release());
}
