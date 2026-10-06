// cl: /O1 /EHsc /MD /arch:SSE
// HordeMeleeHoldGround.cpp -- per-unit attack-state accessors recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv). WB's debug build names the
// members and asserts !(index<0||index>=m_AttackInfo.size()); retail keeps
// that range check as a guard. m_AttackInfo is a vector of per-unit states at
// +0x08 (WB member name); the state values 2 (rotating) and 3 (arrived) come
// from the accessor names.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

// STLport vector<Int> view.
class AttackInfoVector
{
public:
	UnsignedInt size() const { return m_finish - m_start; }
	Int &operator[](UnsignedInt i) { return m_start[i]; }
	const Int &operator[](UnsignedInt i) const { return m_start[i]; }

private:
	Int *m_start;
	Int *m_finish;
	Int *m_endOfStorage;
};

enum { UNIT_ROTATING = 2, UNIT_ARRIVED = 3 };

class HordeMeleeHoldGround
{
public:
	virtual Bool isUnitRotating(Int index) const;
	virtual void setUnitRotating(Int index);
	virtual void setUnitArrived(Int index);

private:
	unsigned char m_pad04[4];
	AttackInfoVector m_AttackInfo;		// +0x08
};

// HordeMeleeHoldGround::isUnitRotating, retail 0x00583726.
Bool HordeMeleeHoldGround::isUnitRotating(Int index) const
{
	if (index < 0 || index >= m_AttackInfo.size())
		return false;
	return m_AttackInfo[index] == UNIT_ROTATING;
}

// HordeMeleeHoldGround::setUnitRotating, retail 0x00583750.
void HordeMeleeHoldGround::setUnitRotating(Int index)
{
	if (index < 0 || index >= m_AttackInfo.size())
		return;
	m_AttackInfo[index] = UNIT_ROTATING;
}

// HordeMeleeHoldGround::setUnitArrived, retail 0x00583772.
void HordeMeleeHoldGround::setUnitArrived(Int index)
{
	if (index < 0 || index >= m_AttackInfo.size())
		return;
	m_AttackInfo[index] = UNIT_ARRIVED;
}
