// ?rva0035B6FA@CommandButton@@QAEXW4ObjectID@@_N@Z
// partial score=0.98 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /MD /EHsc /Oy-
// ?rva0035B6FA@CommandButton@@QAEXW4ObjectID@@_N@Z, retail 0x0035B6FA (86 bytes).
// CommandButton identity and fields at +0x14, +0x1c, and +0xfc are supported by
// adjacent CommandButton rows; the two arguments follow the call-site and callee shapes.
enum ObjectID { OBJECT_ID_0035B6FA = 0 };

class Object
{
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class CommandButton
{
public:
	int rva0035B164(int index);
	void rva0035B5C2(Object *object, bool value);
	void rva0035B6FA(ObjectID objectID, bool value);

private:
	unsigned char m_pad00[0x14];
	int m_stance;
	unsigned char m_pad18[4];
	unsigned int m_flags;
	unsigned char m_pad20[0xDC];
	int m_cachedAvailability;
};

void CommandButton::rva0035B6FA(ObjectID objectID, bool value)
{
	if (m_flags & 0x00800000)
	{
		if (m_stance != 0x23)
		{
			if (m_stance != 0x30)
				return;
		}
		else
		{
			m_cachedAvailability = rva0035B164(objectID);
			return;
		}
	}
	else if ((m_flags & 0x03000000) == 0)
	{
		return;
	}

	CommandButton *self = this;
	self->rva0035B5C2(TheGameLogic->findObjectByID(objectID), value);
}
