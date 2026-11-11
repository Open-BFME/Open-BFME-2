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
#include "../../../Include/GameClient/ModelConditionFlags.h"
class Object
{
public:
	void rva0028AE6D();
	__forceinline void clearModelConditionState(unsigned int mc)
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
#include "../../../Include/GameLogic/Module/Rva001E6516.h"
void Rva001E6516::rva001E6516(Object *obj)
{
	obj->clearModelConditionState((ModelConditionFlagType)(1 * 32 + 29));
}
