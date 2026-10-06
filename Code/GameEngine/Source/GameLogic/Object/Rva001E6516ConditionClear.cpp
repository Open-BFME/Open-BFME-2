// cl: /DNDEBUG /MD
//
// Rva001E6516::rva001E6516, retail 0x001E6516 (28 bytes, ret 4).
// Clears Object model condition 1*32+29 (byte +0x113 bit 5 of the +0x10C word
// array) and runs the pinned notifier 0x0028AE6D only on change. this is
// unused; the callers in the 0x001E7ECA switch pass it in ecx (mov ecx,ebx)
// with the object on the stack, and 0x001E679E tail-jumps here. The owning class
// is not established, so the placeholder is named by address.
enum ModelConditionFlagType
{
	MODELCONDITION_INVALID = -1
};
class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void clear(unsigned int bit)
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
	__forceinline void clearModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad000[0x10C];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
};
class Rva001E6516
{
public:
	void rva001E6516(Object *obj);
};
void Rva001E6516::rva001E6516(Object *obj)
{
	obj->clearModelConditionState((ModelConditionFlagType)(1 * 32 + 29));
}
