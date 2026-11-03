// cl: /DNDEBUG /MD /EHsc
// Target registration pairs both HordeAIUpdate and HordeWorkerAIUpdate with
// RVA 0x2541A3. This is their folded data factory, not DamageModule.
// Retail allocates 0x64 bytes, calls the rowed TransportAIUpdateModuleData
// constructor (0x26E5D7), stores vptr VA 0xC4B6C8, then optionally invokes
// INI::initFromINIMultiProc with the rowed Transport parse proc (0x2638FF).
// The donor ModuleFactory.cpp (BFME1 1281192f68) supplies the factory pattern.
// The Horde spelling is supported by registration; unaccessed layout is opaque.
class ModuleData;
class MultiIniFieldParse;
#include "../../../../../Include/Common/INI/INI.h"
#include "../../../../../Include/GameLogic/Module/TransportAIUpdateModuleData.h"
// Implicit ctor and destructor, as ZH's module data declare them: the
// compiler installs the class's own vtable (retail's folded 0x0084B6C8).
class HordeAIUpdateModuleData : public TransportAIUpdateModuleData {
};
#include "../../../../../Include/GameLogic/Module/HordeAIUpdate.h"
ModuleData *HordeAIUpdate::friend_newModuleData(INI *ini) {
    HordeAIUpdateModuleData *data = new HordeAIUpdateModuleData;
    if (ini) ini->initFromINIMultiProc(data, TransportAIUpdateModuleData::buildFieldParse);
    return reinterpret_cast<ModuleData *>(data);
}
