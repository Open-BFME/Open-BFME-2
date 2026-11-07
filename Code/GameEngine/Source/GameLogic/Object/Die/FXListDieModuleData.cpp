// PC identity update: the registered FXListDie data factory 0x253AB4 calls
// this constructor and pushes its parser 0x253A92.
// cl: /GX /DNDEBUG /MD
// ??0FXListDieModuleData@@QAE@XZ @0x00253A78 26B derived ctor.
// Retail calls base ??0DestroyDieModuleData@@QAE@XZ, zeroes +0x38, stores
// vtable 0x00C4ED70, sets +0x3C to 1. The class derives from the canonical
// DestroyDieModuleData.h and adds no virtuals, so the compiler's table is
// ModuleData's 31 slots with the implicit destructor's deleting destructor
// in slot 0 (retail folds that table with the shared 0x00C4ED70, slot 0 the
// generic 0x004A10FD). Evidence: leaf lane; vtable store; base size 0x38
// from DestroyDieModuleDataCtor TU; flags from neighbours.
#include <new.h>

#include "../../../../Include/GameLogic/Module/DestroyDieModuleData.h"

class FXListDieModuleData : public DestroyDieModuleData
{
public:
	FXListDieModuleData();
private:
	int m_38;
	bool m_3C;
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline FXListDieModuleData::FXListDieModuleData()
	: DestroyDieModuleData()
{
	m_38 = 0;
	m_3C = true;
}

// ?bfmeAnchorFXListDieModuleDataCtor absent-from-retail
void *bfmeAnchorFXListDieModuleDataCtor(void *where)
{
	return ::new (where) FXListDieModuleData();
}
