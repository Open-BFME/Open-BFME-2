// cl: /DNDEBUG /MD
//
// ?isBusy@AIUpdateInterface@@UBE_NXZ, retail 0x00262B39, 26 bytes.
// ?rva00262BA9@AIUpdateInterface@@QAE_NXZ, retail 0x00262BA9, 67 bytes.
// ?rva00262BEC@AIUpdateInterface@@QAE_NXZ, retail 0x00262BEC, 39 bytes.
// AIUpdateInterface methods checking path and state machine states.

class State
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0C();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1C();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2C();
	virtual void v30();
	virtual void v34();
	virtual bool isBusy() const; // slot 14 (offset 0x38)
};

class StateMachine
{
public:
	char m_pad00[4];
	State *m_currentState; // +0x04

	bool isInBusyState() const
	{
		return m_currentState ? m_currentState->isBusy() : false;
	}
};

class Rva001E3591
{
public:
	bool rva001E3591();
};

class Rva003638BA : public Rva001E3591
{
public:
	bool rva003638BA();
	bool rva00262176();
};

class AIUpdateInterface
{
	char m_pad04[0x30 - 4];
	StateMachine *m_machine; // +0x30
	char m_pad34[0x140 - 0x34];
	Rva003638BA *m_path; // +0x140
	char m_pad144[0x1F0 - 0x144];
	int m_field1F0; // +0x1F0
	char m_pad1F4[0x1FC - 0x1F4];
	int m_locomotorGoalType; // +0x1FC
public:
	virtual bool isBusy() const;
	bool rva00262BA9();
	bool rva00262BEC();
};

bool AIUpdateInterface::isBusy() const
{
	if (m_machine)
		return m_machine->isInBusyState();
	return false;
}



bool AIUpdateInterface::rva00262BA9()
{
	if (!m_field1F0)
		return false;

	switch (m_locomotorGoalType)
	{
	case 1:
	case 4:
		if (Rva003638BA *path = m_path)
		{
			if (path->rva001E3591())
				return true;
			if (path->rva00262176())
				return true;
		}
		break;
	}
	return false;
}

bool AIUpdateInterface::rva00262BEC()
{
	switch (m_locomotorGoalType)
	{
	case 1:
	case 4:
		if (m_path && m_path->rva003638BA())
			return true;
		break;
	}
	return false;
}

