// cl: /MD
// ??_GW3DBufferManager@@QAEPAXI@Z @0x000F0956 28B; calls rowed ??1W3DBufferManager@@QAE@XZ @0x001163E7 then operator delete 0x0002FD60.
// Evidence: retail push esi/mov esi,ecx/call/test [esp+8],1 pop-ecx shape; QAE non-virtual dtor so QAEPAXI; rowed dtor in W3DBufferManager.cpp.
// ??_GW3DBufferManager@@QAEPAXI@Z @0x000F0956
struct EmitVtableTag;

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DBufferManagerClass.h"
void famgenDelete(W3DBufferManager *w3DBufferManager) { delete w3DBufferManager; }

// ??_GSpecialPowerModuleData@@UAEPAXI@Z @0x00493333 28B; calls rowed ??1SpecialPowerModuleData@@UAE@XZ @0x0049334F then delete.
class SpecialPowerModuleData { public: SpecialPowerModuleData(EmitVtableTag *); virtual ~SpecialPowerModuleData(); };
// ?<SpecialPowerModuleData::SpecialPowerModuleData> absent-from-retail
SpecialPowerModuleData::SpecialPowerModuleData(EmitVtableTag *) {}
