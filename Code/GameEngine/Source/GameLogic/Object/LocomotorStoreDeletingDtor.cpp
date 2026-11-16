// cl: /O1 /MD
// ??_GLocomotorStore@@QAEPAXI@Z, retail 0x00220903 28B.
// Scalar deleting dtor: calls rowed ??1LocomotorStore@@QAE@XZ at 0x002207C4
// then rowed operator delete at 0x0002FD60. Chain from dtor landing.
// Ghidra 28B vs 37B bytes-to-next: trust ret + int3, gate is authority.
#include "../../../Include/GameLogic/LocomotorStore.h"

// ?forceLocomotorStoreDelete@@YAXPAVLocomotorStore@@@Z absent-from-retail
void forceLocomotorStoreDelete(LocomotorStore *locomotorStore) { delete locomotorStore; }
