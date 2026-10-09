// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// BFME2 DockUpdate crippled-flag setter v2, transferred from the exact BFME1
// reconstruction (Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/DockUpdate.cpp).
// Retail BFME2 keeps the flag at the same offset (+0x65): crippling means
// approach requests are accepted but enter clearance is never granted.

struct Rva0028F59A
{
	unsigned int m_bits[19];
	Rva0028F59A(int unused, int bit);
};

class Rva001E4912
{
public:
	Rva001E4912() {}
	Rva001E4912 *rva001E4912(int unused, unsigned int first, unsigned int second);
	unsigned int m_bits[19];
};

extern "C" void *memset(void *dst, int value, unsigned int size);
class RvaDockClearMask
{
public:
	RvaDockClearMask() { memset(this, 0, sizeof(*this)); }
	void set(int bit) { m_words[bit >> 5] |= 1U << (bit & 31); }
	unsigned int m_words[19];
};
class Rva001E42F2
{
public:
	void rva001E42F2(const int *mask);
};

class Object
{
public:
	void rva0028CFB2(const int *clear, const int *set);
	int m_pad74[0x74 / 4];	// vptr at +0x0, id at +0x74
	int m_id;	// +0x74
};

class ObjectIDVector
{
public:
	int *m_start;
	int *m_finish;
	int *m_endOfStorage;

	unsigned int size() const
	{
		return (unsigned int)(m_finish - m_start);
	}

	int &operator[](unsigned int index)
	{
		return m_start[index];
	}

	const int &operator[](unsigned int index) const
	{
		return m_start[index];
	}
};

#include "../../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class DockUpdate
{
public:
	virtual bool isClearToApproach(const Object *docker) const;
	virtual void dockSlot01();
	virtual void dockSlot02();
	virtual bool isClearToEnter(const Object *docker) const;
	virtual void dockSlot04();
	virtual void dockSlot05();
	virtual void dockSlot06();
	virtual void dockSlot07();
	virtual void dockSlot08();
	virtual void onEnterReached(Object *docker);
	virtual void onDockReached(Object *docker);
	virtual void onExitReached(Object *docker);
	virtual void dockSlot12();
	virtual void cancelDock(Object *docker);
	virtual bool isDockOpen();
	virtual void dockSlot15();
	virtual void dockSlot16();
	virtual void setDockCrippled(bool setting);
	void rva00589AFF(int index);

private:
	unsigned char m_pre04[0x24];	// interface vptr at +0x0, count at +0x28
	int m_numberApproachPositions;	// +0x28
	unsigned char m_pre2C[0x14];	// +0x2C..+0x3F
	ObjectIDVector m_approachPositionOwners;	// +0x40
	unsigned char m_pre4C[0x14];	// +0x4C..+0x5F
	int m_activeDocker;	// +0x60
	bool m_dockerInside;	// +0x64
	bool m_dockCrippled;	// +0x65
};

bool DockUpdate::isClearToApproach(const Object *docker) const
{
	if (m_numberApproachPositions == -1)
		return true;

	int dockerID = docker->m_id;
	for (unsigned int positionIndex = 0;
		positionIndex < m_approachPositionOwners.size(); ++positionIndex)
	{
		if (m_approachPositionOwners[positionIndex] == 0)
			return true;
		if (m_approachPositionOwners[positionIndex] == dockerID)
			return true;
	}

	return false;
}

// ?setDockCrippled@DockUpdate@@UAEX_N@Z
void DockUpdate::setDockCrippled(bool setting)
{
	m_dockCrippled = setting;
}

// ?isClearToEnter@DockUpdate@@UBE_NPBVObject@@@Z
bool DockUpdate::isClearToEnter(const Object *docker) const
{
	return docker->m_id == m_activeDocker;
}

// ?onExitReached@DockUpdate@@UAEXPAVObject@@@Z
// Zero Hour's DockUpdate::onExitReached supplies the callback semantics;
// donor revision f98983a7d3bb405f1a4ba94bb6a2a168062a819d. Native
// 0x0058977F..0x005897FB independently proves the interface receiver,
// owner at this-0x18, 76-byte condition masks, bits 0x53/0x51/0x54,
// docker ID +0x74, inside byte +0x64 and active ID +0x60. The native
// mismatch arm still calls isDockOpen at interface slot 14. This class
// is a view of the secondary DockUpdateInterface, as in the existing rows.
void DockUpdate::onExitReached(Object *docker)
{
	Object *me = *(Object **)((char *)this - 0x18);
	me->rva0028CFB2(
		(const int *)Rva001E4912().rva001E4912(0, 0x53, 0x51),
		(const int *)&Rva0028F59A(0, 0x54));
	docker->rva0028CFB2(
		(const int *)Rva001E4912().rva001E4912(0, 0x53, 0x51),
		(const int *)&Rva0028F59A(0, 0x54));
	m_dockerInside = false;
	if (docker->m_id == m_activeDocker)
		m_activeDocker = 0;
	else
		isDockOpen();
}

// ?onEnterReached@DockUpdate@@UAEXPAVObject@@@Z
// Zero Hour donor at f98983a7 supplies entering-state semantics. Native
// 0x00589DDD..0x00589E77 proves 0x54 cleared and 0x52/0x51 set on both
// objects and removes the matching approach owner through full this-0x20.
void DockUpdate::onEnterReached(Object *docker)
{
	Object *me = *(Object **)((char *)this - 0x18);
	me->rva0028CFB2((const int *)&Rva0028F59A(0, 0x54),
		(const int *)Rva001E4912().rva001E4912(0, 0x52, 0x51));
	docker->rva0028CFB2((const int *)&Rva0028F59A(0, 0x54),
		(const int *)Rva001E4912().rva001E4912(0, 0x52, 0x51));
	m_dockerInside = true;
	int dockerID = docker->m_id;
	for (int i = 0; i < m_approachPositionOwners.size(); ++i)
	{
		if (m_approachPositionOwners[i] == dockerID)
		{
			((DockUpdate *)((char *)this - 0x20))->rva00589AFF(i);
			return;
		}
	}
}

// ?cancelDock@DockUpdate@@UAEXPAVObject@@@Z
// Zero Hour donor at f98983a7 supplies cancellation semantics. Native
// 0x00589E77..0x00589F09 independently proves approach-owner removal
// and active-ID lookup before clearing this state and condition bits
// 0x54/0x52/0x53/0x51. The canonical GameLogic ObjectID call is retained.
void DockUpdate::cancelDock(Object *docker)
{
	int dockerID = docker->m_id;
	for (int i = 0; i < m_approachPositionOwners.size(); ++i)
	{
		if (m_approachPositionOwners[i] == dockerID)
		{
			((DockUpdate *)((char *)this - 0x20))->rva00589AFF(i);
			break;
		}
	}
	if (m_activeDocker == dockerID)
	{
		Object *dockingObject = TheGameLogic->findObjectByID((ObjectID)m_activeDocker);
		m_activeDocker = 0;
		m_dockerInside = false;
		RvaDockClearMask clear;
		clear.set(0x54);
		clear.set(0x52);
		clear.set(0x53);
		clear.set(0x51);
		((Rva001E42F2 *)*(Object **)((char *)this - 0x18))->rva001E42F2((const int *)&clear);
		if (dockingObject)
			((Rva001E42F2 *)dockingObject)->rva001E42F2((const int *)&clear);
	}
}
