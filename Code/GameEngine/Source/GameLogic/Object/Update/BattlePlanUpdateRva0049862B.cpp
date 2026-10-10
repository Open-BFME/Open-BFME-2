// cl: /O1 /DNDEBUG /MD
//
// ?rva0049862B@Rva0049862B@@QAEHXZ @0x0049862B 213B.
// This sits at BattlePlanUpdate+0x10. The byte at +0x2c and a future frame
// both return 1. State +0x20 is 0..3 and drives the plan helper at 0x00497FF3,
// plus the rowed turret helpers. The answer is always 1.

class Object;
class AIUpdateInterface;
class Rva0049862B;

enum CommandSourceType
{
	COMMAND_SOURCE_TWO = 2
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType source);
};

class AIUpdateInterface
{
public:
	char m_pad[0x20];
	AICommandInterface m_commands;
};

class Object
{
public:
	char m_pad[0x258];
	AIUpdateInterface *m_ai;
};

class GameLogic
{
public:
	unsigned getFrame() const { return m_frame; }

private:
	char m_pad[0x40];
	unsigned m_frame;
};

extern GameLogic *TheGameLogic;

enum TransitionStatus { TRANSITION_STATUS_0 };

class BattlePlanUpdate
{
	friend class Rva0049862B;

public:
	char m_pad[8];
	Object *m_object;

protected:
	void setStatus(TransitionStatus status);	// 0x00497FF3
	void enableTurret(bool enable);
	void recenterTurret();
	bool isTurretInNaturalPosition();
};

class Rva0049862B
{
public:
	int rva0049862B();

private:
	BattlePlanUpdate *plan()
	{
		return (BattlePlanUpdate *)((char *)this - 0x10);
	}

	char m_pad[0x14];
	int m_current;
	int m_pending;
	int m_pad1C;
	int m_state;
	unsigned m_frame;
	char m_pad28[4];
	unsigned char m_closed;
	unsigned char m_turretHeld;
};

int Rva0049862B::rva0049862B()
{
	if (m_closed != 0)
		return 1;
	// The frame test stays in the same region as the switch so the
	// ebp/edi saves land between the compare and the unsigned ja.
	if (m_frame <= TheGameLogic->getFrame())
	{
		switch (m_state)
		{
		case 0:
			if (m_pending != 0)
			{
				m_current = m_pending;
				plan()->setStatus((TransitionStatus)1);
			}
			break;
		case 1:
		{
			BattlePlanUpdate *owner = plan();
			owner->setStatus((TransitionStatus)2);
			if (m_current == 1)
				owner->enableTurret(true);
			break;
		}
		case 2:
			if (m_current != m_pending)
			{
				if (m_current == 1)
				{
					Object *obj = *(Object **)((char *)this - 8);
					AIUpdateInterface *ai = obj->m_ai;
					if (ai)
					{
						BattlePlanUpdate *owner = plan();
						if (owner->isTurretInNaturalPosition())
						{
							owner->setStatus((TransitionStatus)3);
							m_turretHeld = 0;
							owner->enableTurret(false);
						}
						else if (m_turretHeld == 0)
						{
							ai->m_commands.aiIdle(COMMAND_SOURCE_TWO);
							owner->recenterTurret();
							m_turretHeld = 1;
						}
					}
				}
				else
					plan()->setStatus((TransitionStatus)3);
			}
			break;
		case 3:
			plan()->setStatus((TransitionStatus)0);
			break;
		}
	}
	return 1;
}
