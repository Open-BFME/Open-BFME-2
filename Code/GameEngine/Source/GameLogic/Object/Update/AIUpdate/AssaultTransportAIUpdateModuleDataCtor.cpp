// cl: /MD /GX /DNDEBUG
//
// ??0AssaultTransportAIUpdateModuleData@@QAE@XZ, retail 0x0024D221 (39 bytes).
// Frameless ctor over the pinned Transport base (0x26E5D7): zeroes
// m_membersGetHealedAtLifeRatio at +0x64, loads the 50.0 clear-range default
// from 0x00BD5E50, sinks the folded vtable 0x00C4B6C8 (shared with the
// Worker and Wander vtables at the same address; TU-spelling alias of their
// ??_7 pins) between those stores through the virtual machinery (Wander
// precedent: virtual classes with declared-only virtual dtors and no source
// store), then stores m_clearRangeRequiredToContinueAttackMove at +0x68.
// Field identity is the base-call buildFieldParse table 0x00BEED74 (both
// fields match BFME1's AssaultTransportAIUpdateModuleData table verbatim at
// identical offsets, votes 2/2). Sole raw caller is the ModuleData factory
// 0x24D29E which news 0x6C.

extern "C" const void *const vtbl_00C4B6C8[];  // folded, 3 classes; via ??_7AnimalAIUpdateModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C4B6C8=??_7AnimalAIUpdateModuleData@@6B@")

class __declspec(novtable) TransportAIUpdateModuleData
{
public:
	TransportAIUpdateModuleData();
	virtual ~TransportAIUpdateModuleData();

private:
	unsigned char m_pad[0x64 - 4];
};

class __declspec(novtable) AssaultTransportAIUpdateModuleData : public TransportAIUpdateModuleData
{
public:
	AssaultTransportAIUpdateModuleData();

private:
	float m_membersGetHealedAtLifeRatio;		// +0x64
	float m_clearRangeRequiredToContinueAttackMove;	// +0x68
};

AssaultTransportAIUpdateModuleData::AssaultTransportAIUpdateModuleData()
{
	m_membersGetHealedAtLifeRatio = 0.0f;
	*(unsigned int *)this = ((unsigned int)vtbl_00C4B6C8);
	m_clearRangeRequiredToContinueAttackMove = 50.0f;
}
