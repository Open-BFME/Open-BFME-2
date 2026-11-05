// cl: /DNDEBUG /MD /GX-
// The EventFX field parser of the life-event and terrain-collision module
// templates (retail 0x00563EA8, 23 bytes). Retail exports 1834 and 1835 name
// both static members at that one address: /OPT:ICF folds the two identical
// bodies. Each forwards to the rowed parseAsciiString at 0x002F11E with
// userData forced to 0. The FieldParse tables at 0x00C6CAC0 (LifeEvent) and
// 0x00C6CB68 (TerrainCollision) in FXParticleSystemModuleParsers.cpp name them.

#include "../../../Include/Common/INI/INI.h"

namespace FXParticleSystem
{

class LifeEventModuleTemplate
{
public:
	static void parseEventFXListName(INI *ini, void *instance, void *store, const void *userData);
};

class TerrainCollisionModuleTemplate
{
public:
	static void parseEventFXListName(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseEventFXListName@LifeEventModuleTemplate@FXParticleSystem@@SAXPAVINI@@PAX1PBX@Z
void LifeEventModuleTemplate::parseEventFXListName(INI *ini, void *instance, void *store, const void * /*userData*/)
{
	INI::parseAsciiString(ini, instance, store, 0);
}

// ?parseEventFXListName@TerrainCollisionModuleTemplate@FXParticleSystem@@SAXPAVINI@@PAX1PBX@Z
void TerrainCollisionModuleTemplate::parseEventFXListName(INI *ini, void *instance, void *store, const void * /*userData*/)
{
	INI::parseAsciiString(ini, instance, store, 0);
}

} // namespace FXParticleSystem
