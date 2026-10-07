// cl: /MD /O1 /arch:SSE /G7
// ?rva002BD603@LivingWorldLogic@@QAEXH@Z at 0x002BD603, 76 bytes.
// The caller passes this as LivingWorldLogic*; the target accesses the owned-pointer slot at +0x178.
// The constructor signature comes from the target call to ??0Rva002B74DE@@QAE@PAVLivingWorldLogic@@H@Z.

class LivingWorldLogic;

class Rva002B74DE
{
public:
	char m_unknown[0x28];
	Rva002B74DE(LivingWorldLogic *logic, int value);
};

class Rva002B90B3
{
public:
	void reset(Rva002B74DE *p);
};

class LivingWorldLogic
{
public:
	char m_unknown[0x178];
	Rva002B90B3 m_rva002BD603OwnedPointer;

	void rva002BD603(int value);
};

void LivingWorldLogic::rva002BD603(int value)
{
	Rva002B74DE *p = new Rva002B74DE(this, value);
	m_rva002BD603OwnedPointer.reset(p);
}
