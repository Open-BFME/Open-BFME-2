// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Two methods of the placeholder class Rva004076EE (its matched getter
// 0x004076EE returns the Object for the ObjectID at +4; same TU flags), retail
// 0x00407BC3 and 0x00407C17 (84 bytes each), adjacent to it in retail. On that
// Object: 0x00407BC3 sets condition bit 17*32+7 and clears 17*32+6 and 17*32+4;
// 0x00407C17 clears all three. Callers 0x005B4D05 / 0x005B57C1 (tail jump).
// Names by address. Condition word array at Object+0x10C with masked-word
// accessors in free __forceinline helpers around the pinned notifier 0x0028AE6D.

class Rva0010CBits
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
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};
class Object
{
public:
	void rva0028AE6D();
	unsigned char m_pad000[0x10C];
	Rva0010CBits m_conditionBits; // +0x10C
};
static __forceinline void setModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) == 0)
	{
		object->m_conditionBits.set(bit);
		object->rva0028AE6D();
	}
}
static __forceinline void clearModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) != 0)
	{
		object->m_conditionBits.clear(bit);
		object->rva0028AE6D();
	}
}
class Rva004076EE
{
public:
	Object *rva004076EE();
	void rva00407BC3();
	void rva00407C17();
};
void Rva004076EE::rva00407BC3()
{
	Object *object = rva004076EE();
	if (object)
	{
		setModelConditionBit(object, 17 * 32 + 7);
		clearModelConditionBit(object, 17 * 32 + 6);
		clearModelConditionBit(object, 17 * 32 + 4);
	}
}
void Rva004076EE::rva00407C17()
{
	Object *object = rva004076EE();
	if (object)
	{
		clearModelConditionBit(object, 17 * 32 + 7);
		clearModelConditionBit(object, 17 * 32 + 6);
		clearModelConditionBit(object, 17 * 32 + 4);
	}
}
