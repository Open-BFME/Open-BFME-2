// PC identity update: the registered FXListDie data factory 0x253AB4 calls
// this constructor and pushes its parser 0x253A92.
// cl: /GX /DNDEBUG /MD
// ??0FXListDieModuleData@@QAE@XZ @0x00253A78 26B derived ctor.
// Retail calls base ??0DestroyDieModuleData@@QAE@XZ, zeroes +0x38, stores vtable
// 0x0084ED70, sets +0x3C to 1. Evidence: leaf lane; vtable store;
// base size 0x38 from DestroyDieModuleDataCtor TU; flags from neighbours;
// explicit-vtable pattern from ToggleHiddenSpecialAbilityUpdateCtor TU.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

static int s_vtable;

class __declspec(novtable) DestroyDieModuleData
{
public:
	DestroyDieModuleData();
protected:
	const void *m_vtable;
	unsigned char m_pad[0x38 - 4];
};

class FXListDieModuleData : public DestroyDieModuleData
{
public:
	FXListDieModuleData();
private:
	int m_38;
	bool m_3C;
};

FXListDieModuleData::FXListDieModuleData()
	: DestroyDieModuleData()
{
	m_38 = 0;
	_ReadWriteBarrier();
	m_vtable = &s_vtable;
	m_3C = true;
}
