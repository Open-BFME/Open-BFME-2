// cl: /O1 /EHsc /Ireference/shims/bfme2_ascii /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?Rva002FEE2CParse@@YAXPAVINI@@PAX1PBX@Z, retail 0x002FEE2C (129B). INI field callback for the
// "Target" entry of the AI named-list table at VA 0x00C07414 (see AIRva002FFD03Parse.cpp): reads a
// thing template reference (rowed 0x0033940F, the same callback the "DefaultPreviewObject" family
// uses) and an int (rowed INI::parseInt); when the template exists and its name (AsciiString at
// +0x64) is not empty, a record {name, int} is pushed at the front of the list the table's offset
// 0xC selects (the callback's store argument). Evidence: target bytes and WB debug body 00D73D40
// (unnamed): the same flow; the rowed push_front 0x002FED53 takes the record by address.
// The element is spelled through the rowed list's pointer element type (the record is passed by
// address). The record layout and the callback's role are inferred from this body alone.
#include <list>
#include "ascii_string.h"

#include "../../../Include/Common/INI/INI.h"

struct Rva002FED53PointerTarget;

struct Rva002FEE2CRecord
{
	Rva002FEE2CRecord() : value(0) {}
	AsciiString name;
	int value;
};

struct Rva002FEE2CThing
{
	char m_pad[0x64];
	AsciiString name;
};

void Rva002FEE2CParse(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	Rva002FEE2CThing *thing;
	int value;
	INI::parseThingTemplate(ini, 0, &thing, 0);
	INI::parseInt(ini, 0, &value, 0);
	Rva002FEE2CRecord record;
	if (thing && !thing->name.isEmpty())
	{
		record.name = thing->name;
		record.value = value;
		((_STL::list<Rva002FED53PointerTarget *> *)store)->push_front(*(Rva002FED53PointerTarget **)&record);
	}
}
