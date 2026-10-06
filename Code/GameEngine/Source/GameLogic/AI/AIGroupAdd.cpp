// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?add@AIGroup@@QAEXPAVObject@@@Z @0x0036E5F1 103B: AIGroup group add with KindOf gate.
// Evidence: LINK BONUS caller Team::getTeamAsAIGroup 0x003A0FB9 passes AIGroup this plus Object arg;
// BFME1 AIGroup_add.cpp donor plus ZH AIGroup::add shape (null check, AIUpdate at +0x258 gate,
// KindOf mask memset 0x1C plus three ORs, list push_back, enterGroup, dirty at +0x0C);
// callees rowed memset thunk 0x6291AE plus Thing::isAnyKindOf 0x30ADC7 plus list<int>::push_back 0x5548F
// plus Object::rva0028E5CA 0x28E5CA; neighbours AIGroupRemove.cpp same flags and layout.
#include <list>

extern "C" void *memset(void *dst, int val, unsigned size);

template<int N>
class BitFlags
{
public:
	unsigned int m_words[7];
};

struct ThingTemplate
{
	char m_pad[0x108];
	int m_kindOf;
};

class Thing
{
public:
	bool isAnyKindOf(const BitFlags<69> &mask) const;

private:
	char m_pad00[4];
	ThingTemplate *m_template;
};

class AIGroup;

class Object : public Thing
{
public:
	void *getAI() const { return m_ai; }
	void rva0028E5CA(AIGroup *group);

private:
	unsigned char m_pad[0x258 - 8];
	void *m_ai;
};

class AIGroup
{
public:
	void add(Object *member);

private:
	virtual void *deleteInstance(int flags);
	_STL::list<int> m_memberList;
	char m_pad[4];
	bool m_dirty;
};

void AIGroup::add(Object *member)
{
	if (member == 0)
		return;
	void *ai = member->getAI();
	BitFlags<69> mask;
	memset(&mask, 0, 0x1C);
	((unsigned char *)&mask)[0] |= 0x80;
	((unsigned char *)&mask)[15] |= 8;
	((unsigned char *)&mask)[7] |= 4;
	if (ai == 0 && !member->isAnyKindOf(mask))
		return;
	m_memberList.push_back(*(int *)&member);
	member->rva0028E5CA(this);
	m_dirty = true;
}
