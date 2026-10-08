// cl: /O1 /DNDEBUG /MD
//
// ?rva004B05F5@SpecialDisguiseUpdate@@QAEX_N@Z, retail 0x004B05F5, 94 bytes.
// Original name unknown. Caller: SpecialPowerModule 0x0049402B passes false
// on the module it found under NAMEKEY "SpecialDisguiseUpdate", so the class
// is target evidence. Shape from the WorldBuilder debug body (0x01105FA0,
// unnamed; callgraph lead): when the owner (+0x08) has model condition 300
// set it clears it inline (Object.h clearModelConditionState: words at
// Object+0x10C, rowed notifier 0x0028AE6D); unless the argument is true it
// then calls the pinned 0x004B04B2 with true and plays the module data's
// +0xD8 FXList at the owner position (+0x38) through the rowed static
// FXList::doFXPos 0x00094C29, which carries the null guard. The +0xD8 member
// is an FXList pointer by that call; the bool argument meaning is inferred.

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Matrix3D;

class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *primary, const Matrix3D *mtx, float speed, const Coord3D *secondary);
};

class ModelConditionFlags
{
public:
	__forceinline bool test(unsigned int bit) const
	{
		return ((m_words[bit >> 5] >> (bit & 0x1f)) & 1) != 0;
	}
	__forceinline unsigned int testMask(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	__forceinline void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};

class Object
{
public:
	__forceinline bool testModelConditionState(unsigned int mc) const
	{
		return m_modelConditionFlags.test(mc);
	}
	__forceinline void clearModelConditionState(unsigned int mc)
	{
		if (m_modelConditionFlags.testMask(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}
	__forceinline const Coord3D *getPosition() const { return &m_pos; }
	void rva0028AE6D();
private:
	unsigned char m_pad00[0x38];
	Coord3D m_pos;
	unsigned char m_pad44[0x10C - 0x44];
	ModelConditionFlags m_modelConditionFlags;
};

class SpecialDisguiseUpdateModuleData
{
public:
	unsigned char m_pad00[0xD8];
	const FXList *m_fx;
};

class SpecialDisguiseUpdate
{
public:
	void rva004B05F5(bool keep);
	void rva004B04B2(bool value);
private:
	void *m_vptr;
	const SpecialDisguiseUpdateModuleData *m_moduleData;
	Object *m_object;
};

// ?rva004B05F5@SpecialDisguiseUpdate@@QAEX_N@Z @0x004B05F5
void SpecialDisguiseUpdate::rva004B05F5(bool keep)
{
	Object *obj = m_object;
	if (obj->testModelConditionState(300))
	{
		obj->clearModelConditionState(300);
		if (!keep)
		{
			rva004B04B2(true);
			FXList::doFXPos(m_moduleData->m_fx, obj->getPosition(), 0, 0.0f, 0);
		}
	}
}
