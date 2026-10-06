// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva00395F0B@Rva00395F0B@@QAEXPAVObject@@@Z RVA 0x00395F0B size 76 unlock via rowed setProducer setDisabled setStatus plus pinned notifier 0x0028AE6D flag word1 bit31 at Object+0x114 mask 0x80000000 producer at this+8 recipe HordeSiegeEngineContainCtor forceinline masked-word accessor.
enum DisabledType
{
	DISABLED_TYPE_0 = 0,
	DISABLED_TYPE_1 = 1,
	DISABLED_TYPE_2 = 2,
	DISABLED_TYPE_3 = 3
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_0 = 0,
	OBJECT_STATUS_1 = 1,
	OBJECT_STATUS_2 = 2,
	OBJECT_STATUS_3 = 3
};
class Rva00110ConditionBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
private:
	unsigned int m_words[8];
};
class Object
{
public:
	void setProducer(Object *producer);
	void setDisabled(DisabledType type);
	void setStatus(ObjectStatusTypes status, bool flag);
	void rva0028AE6D();
public:
	unsigned char m_pad000[0x110];
	Rva00110ConditionBits m_conditionBits;
};
static __forceinline void rva00395F0BSetCondition(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) == 0)
	{
		object->m_conditionBits.set(bit);
		object->rva0028AE6D();
	}
}
class Rva00395F0B
{
public:
	void rva00395F0B(Object *obj);
private:
	char m_pad00[8];
	Object *m_producer;
};
void Rva00395F0B::rva00395F0B(Object *obj)
{
	obj->setProducer(m_producer);
	obj->setDisabled((DisabledType)3);
	rva00395F0BSetCondition(obj, 63);
	obj->setStatus((ObjectStatusTypes)3, true);
	obj->setStatus((ObjectStatusTypes)0x4F, true);
}
