// ??0QueueProductionExitUpdateModuleData@@QAE@XZ
// partial score=0.97 date=2026-09-29
// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// Identity: retail ModuleFactory registers "QueueProductionExitUpdate" with a
// data factory that calls this ctor (tools/check_module_registry.py).
// ??0QueueProductionExitUpdateModuleData@@QAE@XZ @ 0x002541FA (68B). Ctor stores vtable 0x00BF1D58,
// six floats at +0x08..+0x1C via movss, ints/bytes at +0x20..+0x32, byte +0x32=1.
// Caller at 0x0025425E. Finish from banked 0.97 stash: xor ecx early vs late
// only diff; try literals for ints so xor lands late like retail.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class QueueProductionExitUpdateModuleData
{
public:
	QueueProductionExitUpdateModuleData();
private:
	const void *m_vtable;
	int m_unk04;
	float m_f08;
	float m_f0C;
	float m_f10;
	float m_f14;
	float m_f18;
	float m_f1C;
	int m_20;
	unsigned char m_24;
	unsigned char m_pad25[3];
	int m_28;
	float m_f2C;
	unsigned char m_30;
	unsigned char m_31;
	unsigned char m_32;
};
QueueProductionExitUpdateModuleData::QueueProductionExitUpdateModuleData()
{
	float fzero = 0.0f;
	m_vtable = (const void *)0x00BF1D58;
	m_f08 = fzero;
	m_f0C = fzero;
	m_f10 = fzero;
	m_f14 = fzero;
	m_f18 = fzero;
	m_f1C = fzero;
	_ReadWriteBarrier();
	m_20 = 0;
	m_24 = 0;
	m_28 = 0;
	m_f2C = fzero;
	m_30 = 0;
	m_31 = 0;
	m_32 = 1;
}
