// cl: /MD /DNDEBUG
//
// Three PathfinderPosGoalManager members, retail 0x004DDD6E / 0x004DDD80 / 0x004DDD92
// (18 bytes each), pinned from the Object forwarders through Object+0xA4:
// each hands its 0x18-byte slot (+0x1C / +0x34 / +0x04) to the member
// 0x004DD8FA unless the slot's first word holds the -666666 "unset"
// sentinel. The class and slot meanings are not recovered.

typedef int Int;

enum
{
	RVA004DD843_UNSET = -666666
};

struct Rva004DD843Slot
{
public:
	int m_value;
	char m_pad04[4];
	int m_x24;
	char m_pad0C[4];
	int state;
	int auxiliary;
};

class Object;

class PathfinderPosGoalManager
{
public:
	float rva004DD843();
	void SetGoal(int first, float value, int last);
	void rva004DE511(int first, int last);
	void rva004DE4E2(int arg);
	void rva004DDD6E();
	void rva004DDD80();
	void rva004DDD92();
	void RemoveObjPtr(Rva004DD843Slot *slot);
	void LoadPostProcess();
	void AddObjPtr(Rva004DD843Slot *slot);

private:
	Object *m_object;
	Rva004DD843Slot m_slot04;
	Rva004DD843Slot m_slot1C;
	Rva004DD843Slot m_slot34;
};

void PathfinderPosGoalManager::rva004DDD6E()
{
	if (m_slot1C.m_value != RVA004DD843_UNSET)
		RemoveObjPtr(&m_slot1C);
}

void PathfinderPosGoalManager::rva004DDD80()
{
	if (m_slot34.m_value != RVA004DD843_UNSET)
		RemoveObjPtr(&m_slot34);
}

void PathfinderPosGoalManager::rva004DDD92()
{
	if (m_slot04.m_value != RVA004DD843_UNSET)
		RemoveObjPtr(&m_slot04);
}
