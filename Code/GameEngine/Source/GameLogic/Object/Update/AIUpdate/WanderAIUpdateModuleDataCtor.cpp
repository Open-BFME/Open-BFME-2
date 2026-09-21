// cl: /O1 /MD /GX /DNDEBUG
//
// ??0WanderAIUpdateModuleData@@QAE@XZ, retail 0x0024F1CD (37 bytes).
// Frameless ctor over the pinned Transport base (0x26E5D7): sets
// m_conditionForEntry at +0x68 through OR-minus-one first (the 05:00Z lever:
// |= -1 emits leading OR under /O1), then the compiler sinks the folded
// vtable 0x00C4B6C8 below that one store through the ??_7 pin (Devastate
// precedent: virtual classes with declared-only virtual dtors and no source
// store; Veterancy precedent for the sink), then zeroes m_wildBeast at +0x64,
// sets m_selectable true at +0x6C and stores m_wanderDistance 30 at +0x70.
// Field identity is the chained buildFieldParse table 0x00BEF580 (WildBeast
// plus ConditionForEntry plus Selectable plus WanderDistance). Sole raw
// caller is the ModuleData factory 0x24F248 which news 0x74.

class TransportAIUpdateModuleData
{
public:
	TransportAIUpdateModuleData();
	virtual ~TransportAIUpdateModuleData();

private:
	unsigned char m_pad[0x64 - 4];
};

class WanderAIUpdateModuleData : public TransportAIUpdateModuleData
{
public:
	WanderAIUpdateModuleData();
	virtual ~WanderAIUpdateModuleData();

private:
	bool m_wildBeast;		// +0x64
	int m_conditionForEntry;	// +0x68
	bool m_selectable;		// +0x6C
	int m_wanderDistance;		// +0x70
};

WanderAIUpdateModuleData::WanderAIUpdateModuleData()
{
	m_conditionForEntry |= -1;
	m_wildBeast = false;
	m_selectable = true;
	m_wanderDistance = 30;
}
