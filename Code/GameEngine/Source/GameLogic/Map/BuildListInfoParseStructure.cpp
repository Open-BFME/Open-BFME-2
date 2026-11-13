// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?parseStructure@BuildListInfo@@SAXPAVINI@@PAX1PBX@Z, retail 0x0032A942
// (145 bytes, EH): the INI "Structure" block parser of a side's build list.
// Zero Hour's SidesList.cpp BuildListInfo::parseStructure verbatim: read the
// template name token, allocate a BuildListInfo (0x80 bytes, ctor 0x0032A0CE),
// set its template name, fill it through the static field table, and append it
// to the AISideBuildList the block's instance names (addInfo 0x006FD766).
// Target evidence: the retail field table at 0x00C0D9A0 lists Name +0x04,
// Location +0x0C, Rebuilds +0x28, Angle +0x20, InitiallyBuilt +0x24,
// RallyPointOffset +0x18 and AutomaticallyBuild +0x3B with the same parse
// procedures as Zero Hour, over the BuildListInfo layout of
// BuildListInfoCtor.cpp. The template name setter is called through its
// address-derived row 0x002AAE81 (the setTemplateName name sits on another
// address).
#include <stddef.h>
#include "ascii_string.h"

class INI;
#include "../../../Include/Common/INI/FieldParse.h"

#include "../../../Include/Common/INI/INI.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Libraries/Include/Lib/Coord2D.h"

#include "../../../Include/GameLogic/Bfme2BuildListInfo.h"

// The template-name setter's address-derived row.
#include "../../../Include/Common/Rva002AAE81.h"

class AISideBuildList
{
public:
	void addInfo(BuildListInfo *info);
};

void BuildListInfo::parseStructure(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	const char *c = ini->getNextToken();
	AsciiString tTemplateName(c);

	static const FieldParse myFieldParse[] =
	{
		{ "Name",			INI::parseAsciiString,	0, offsetof(BuildListInfo, m_buildingName) },
		{ "Location",			INI::parseCoord2D,	0, offsetof(BuildListInfo, m_location) },
		{ "Rebuilds",			INI::parseInt,		0, offsetof(BuildListInfo, m_numRebuilds) },
		{ "Angle",			INI::parseAngleReal,	0, offsetof(BuildListInfo, m_angle) },
		{ "InitiallyBuilt",		INI::parseBool,		0, offsetof(BuildListInfo, m_isInitiallyBuilt) },
		{ "RallyPointOffset",		INI::parseCoord2D,	0, offsetof(BuildListInfo, m_rallyPointOffset) },
		{ "AutomaticallyBuild",		INI::parseBool,		0, offsetof(BuildListInfo, m_automaticallyBuild) },
		{ 0, 0, 0, 0 }
	};

	BuildListInfo *buildInfo = new BuildListInfo;
	((Rva002AAE81 *)buildInfo)->rva002AAE81(tTemplateName);
	ini->initFromINI(buildInfo, myFieldParse);
	((AISideBuildList *)instance)->addInfo(buildInfo);
}
