// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Native79FBC..7A225 RET8; WB918370 names ProcessGroup in W3DHordeModelDraw.cpp.
// Ported from the complete617B bank; native supplies every branch and accessed
// offset. Local render-object, draw-module and animation names denote ABI
// views; original record types remain unknown. Existing STL provider names
// are declaration views, not new claims about their historical element types.
// Handle prefix agrees with the rowed manager grouping caller7A54B.
// Source Add_Ref/Release_Ref pair remains observable to the compiler across a
// nonemitting barrier, preserving native INC/DEC without assembly.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
namespace _STL
{
template <class T> class allocator
{
};

template <class T, class A = allocator<T> > class vector
{
public:
	void resize(unsigned int count, T value);
	void push_back(const T &value);
	T *begin() const { return m_start; }

private:
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};

template <class T, class A = allocator<T> > class list
{
public:
	void push_back();
	void *backData() const { return (char *)((void **)m_node)[1] + 8; }

private:
	void *m_node;
};
}

class Drawable;
class ModuleData;

class RefCountClass
{
public:
	virtual void Delete_This();
	void Add_Ref() { ++m_numRefs; }
	void Release_Ref()
	{
		if (--m_numRefs == 0)
			Delete_This();
	}

protected:
	int m_numRefs; // +0x04
};

// A model sub-object (vslot 3 kind test, slot pointer at +0x310).
class HordeSubObject : public RefCountClass
{
public:
	virtual void slot01();
	virtual void slot02();
	virtual int getKind(); // +0x0C

	char m_pad08[0x310 - 0x08];
	Drawable **m_slot; // +0x310
};

class HordeModel : public RefCountClass
{
public:
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28();
	virtual int getSubObjectCount(); // +0x74
	virtual HordeSubObject *getSubObject(int index); // +0x78
	virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34();
	virtual void slot35(); virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40(); virtual void slot41(); virtual void slot42();
	virtual void slot43(); virtual void slot44(); virtual void slot45(); virtual void slot46();
	virtual void slot47(); virtual void slot48(); virtual void slot49(); virtual void slot50();
	virtual void slot51(); virtual void slot52(); virtual void slot53(); virtual void slot54();
	virtual void slot55(); virtual void slot56(); virtual void slot57(); virtual void slot58();
	virtual void setLeader(HordeModel *leader); // +0xEC
};

struct HordeAnimState
{
	int m_00;
	int m_04;
	int m_08;
	char m_pad0C[0x1C - 0x0C];
};

class HordeDrawModule
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48();
	virtual HordeModel *getModel(); // +0xC4

	char m_pad04[0x18 - 0x04];
	int m_current; // +0x18
	char m_pad1C[0x110 - 0x1C];
	HordeAnimState m_anim[2]; // +0x110
	char m_pad148[0x2EC - 0x148];
	int m_frameStamp; // +0x2EC
	int m_processed; // +0x2F0
};

struct W3DHordeModelDrawHandle
{
	HordeDrawModule *m_draw;
 int m_nameKey; // caller7A54B proves complete8B handle
};

class Rva0014A0B0
{
public:
	int rva0014A0B0() const;
};

class Rva0007894EOuter;

class GameClient
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual int getFrame(); // +0x7C
};

extern GameClient *TheGameClient;

class W3DHordeModelDrawManager
{
public:
	void ProcessGroup(W3DHordeModelDrawHandle **begin, W3DHordeModelDrawHandle **end);
	bool rva0007894E(Rva0007894EOuter *draw);

private:
	char m_pad00[0x0C];
	_STL::list<int> m_groups; // +0x0C
	_STL::vector<const ModuleData *> m_subObjects; // +0x10
	_STL::vector<const ModuleData *> m_models; // +0x1C
};

static inline bool PassesSubObjectTest(HordeSubObject *sub)
{
	return (unsigned char)((Rva0014A0B0 *)sub)->rva0014A0B0() != 0;
}

void W3DHordeModelDrawManager::ProcessGroup(W3DHordeModelDrawHandle **begin, W3DHordeModelDrawHandle **end)
{
	W3DHordeModelDrawHandle *leader = 0;
	HordeModel *leaderModel = 0;
	W3DHordeModelDrawHandle *candidate = 0;
	HordeModel *candidateModel = 0;
	W3DHordeModelDrawHandle *current = 0;
	HordeModel *currentModel = 0;
	for (W3DHordeModelDrawHandle **it = begin; it != end; ++it)
	{
		HordeDrawModule *draw = (*it)->m_draw;
		if (!rva0007894E((Rva0007894EOuter *)draw))
			continue;
		HordeModel *model = draw->getModel();
		if (leader == 0)
		{
			leader = *it;
			leaderModel = model;
		}
		if (draw->m_processed == draw->m_current)
		{
			int frame = TheGameClient->getFrame();
			bool positive = true;
			int stamp = draw->m_frameStamp;
			if (stamp < 0)
			{
				positive = false;
				stamp = -stamp;
			}
			if (stamp >= frame - 1)
			{
				if (positive)
				{
					current = *it;
					currentModel = model;
					break;
				}
				if (candidate == 0)
				{
					candidate = *it;
					candidateModel = model;
				}
			}
		}
	}
	if (current)
	{
		leader = current;
		leaderModel = currentModel;
	}
	else if (candidate)
	{
		leader = candidate;
		leaderModel = candidateModel;
	}
	if (leader == 0)
		return;

	int count = 0;
	int n = leaderModel->getSubObjectCount();
	while (n-- > 0)
	{
		HordeSubObject *sub = leaderModel->getSubObject(n);
		if (sub == 0)
			continue;
		if (sub->getKind() != 0)
		{
			sub->Release_Ref();
			continue;
		}
		HordeSubObject *test = sub;
		if (!PassesSubObjectTest(test))
		{
			sub->Release_Ref();
			continue;
		}
		++count;
		sub->Release_Ref();
	}

	m_groups.push_back();
	_STL::vector<Drawable *> *slots = (_STL::vector<Drawable *> *)m_groups.backData();
	slots->resize(count, 0);
	Drawable **firstSlot = slots->begin();

	for (W3DHordeModelDrawHandle **next = begin; next != end; ++next)
	{
		HordeDrawModule *draw = (*next)->m_draw;
		if (!rva0007894E((Rva0007894EOuter *)draw))
			continue;
		HordeModel *model = draw->getModel();
		{
			const ModuleData *modelEntry = (const ModuleData *)model;
			draw->m_processed = draw->m_current;
			if (model != leaderModel)
			{
				model->Add_Ref();
				m_models.push_back(modelEntry);
				model->setLeader(leaderModel);
				draw->m_frameStamp = -TheGameClient->getFrame();
			}
			else
			{
				draw->m_frameStamp = TheGameClient->getFrame();
			}
		}
		Drawable **slot = firstSlot;
		int m = model->getSubObjectCount();
		while (m-- > 0)
		{
			HordeSubObject *sub = model->getSubObject(m);
			if (sub == 0)
				continue;
			if (sub->getKind() != 0)
			{
				sub->Release_Ref();
				continue;
			}
			const ModuleData *entry = (const ModuleData *)sub;
			if (!PassesSubObjectTest(sub))
			{
				sub->Release_Ref();
				continue;
			}
			sub->Add_Ref();
			_ReadWriteBarrier();
			sub->Release_Ref();
			m_subObjects.push_back(entry);
			sub->m_slot = slot;
			*slot = 0;
			++slot;
		}
		for (int k = 0; k < 2; ++k)
		{
			HordeAnimState *src = &leader->m_draw->m_anim[k];
			HordeAnimState *dst = &draw->m_anim[k];
			dst->m_04 = src->m_04;
			dst->m_08 = src->m_08;
		}
	}
}
