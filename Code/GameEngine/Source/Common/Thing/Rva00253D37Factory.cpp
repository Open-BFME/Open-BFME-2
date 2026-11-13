// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?ModuleFactoryDataAt00253D37@@YAPAVModuleData@@PAVINI@@@Z, retail
// 0x00253D37, 81 bytes.
//
// Evidence (retail body only; names are address-derived):
//  253d37: mov eax, FuncInfo / call __EH_prolog
//          new Rva00253E32 (operator new 0x18, then the rowed ctor at
//          0x00253E32), and when the INI argument is non-null run
//          INI::initFromINIMultiProc 0x0002DEB5 on it with the rowed
//          buildFieldParse at 0x004CEE09; return the new object.
// ModuleFactory::init registers this factory for both
// NotifyTargetsOfImminentProbableCrushingUpdate and its Horde variant; which
// one owns the data class is not settled by these bytes, so the factory and
// its classes keep address-derived names.
//
// ?buildFieldParse@Rva00253E32@@SAXAAVMultiIniFieldParse@@@Z, retail
// 0x004CEE09, 17 bytes: the parse proc above, registering the record table
// at the record member's offset 8.
// ?getFieldParse@Rva004CE6BA@@SAPBUFieldParse@@XZ, retail 0x004CEA8E,
// 6 bytes: the record's out-of-line table getter (mov eax, table / ret).
// The table at retail VA 0x00C60010 (.rdata) holds the four fields the
// rowed record ctor 0x004CE6BA initialises (+0x00/+0x04 two durations,
// +0x08/+0x0C two -1.0f reals).

class ModuleData;
class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
#include "../../../Include/Common/INI/FieldParse.h"


#include "../../../Include/Common/INI/INI.h"

// Tokens, callbacks and offsets read from the retail table; the global name
// is descriptive, its original spelling unknown.
extern const FieldParse BfmeProbableCrushingScanFields[] =
{
	{ "TimeBetweenUpdatesMS", &INI::parseDurationUnsignedInt, 0, 0x0 },
	{ "ScanAheadTimeMS", &INI::parseDurationUnsignedInt, 0, 0x4 },
	{ "ScanHeight", &INI::parseReal, 0, 0x8 },
	{ "ScanWidth", &INI::parseReal, 0, 0xC },
	{ 0, 0, 0, 0 }
};

#include "../../../Include/Common/Rva004CE6BA.h"

class Rva00253E32Base
{
public:
	Rva00253E32Base() {}
	virtual ~Rva00253E32Base();

private:
	void *m_base4;
};

class Rva00253E32 : public Rva00253E32Base
{
public:
	Rva00253E32();
	virtual ~Rva00253E32();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	Rva004CE6BA m_8;
};

const FieldParse *Rva004CE6BA::getFieldParse()
{
	return BfmeProbableCrushingScanFields;
}

void Rva00253E32::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(BfmeProbableCrushingScanFields, 8);
}

ModuleData *ModuleFactoryDataAt00253D37(INI *ini)
{
	Rva00253E32 *obj = new Rva00253E32;
	if (ini)
		ini->initFromINIMultiProc(obj, &Rva00253E32::buildFieldParse);
	return (ModuleData *)obj;
}
