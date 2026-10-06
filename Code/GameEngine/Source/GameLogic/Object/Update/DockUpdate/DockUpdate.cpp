// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// BFME2 DockUpdate crippled-flag setter v2, transferred from the exact BFME1
// reconstruction (Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/DockUpdate.cpp).
// Retail BFME2 keeps the flag at the same offset (+0x65): crippling means
// approach requests are accepted but enter clearance is never granted.

class Object
{
public:
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

class DockUpdate
{
public:
	virtual bool isClearToApproach(const Object *docker) const;
	virtual void setDockCrippled(bool setting);
	virtual bool isClearToEnter(const Object *docker) const;

private:
	unsigned char m_pre04[0x24];	// interface vptr at +0x0, count at +0x28
	int m_numberApproachPositions;	// +0x28
	unsigned char m_pre2C[0x14];	// +0x2C..+0x3F
	ObjectIDVector m_approachPositionOwners;	// +0x40
	unsigned char m_pre4C[0x14];	// +0x4C..+0x5F
	int m_activeDocker;	// +0x60
	unsigned char m_pad64;	// +0x64
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
