// cl: /O1 /G7 /DNDEBUG /MD /arch:SSE
//
// ?rva004A6A58@Rva004A6A58@@QAEHXZ @0x004A6A58 41B.
// Virtual slot 4 on the object at +0x3D8, clamped to at least 1, then the
// minimum of that and AIUpdateInterface::update (direct call, rowed symbol
// 0x0026E267). cmovl keeps the smaller signed result.

enum UpdateSleepTime
{
	USLEEP_MIN = 0
};

class SlotOwner
{
public:
	virtual int s0();
	virtual int s1();
	virtual int s2();
	virtual int s3();
	virtual int s4();
};

class AIUpdateInterface
{
public:
	virtual UpdateSleepTime update();
};

class Rva004A6A58
{
public:
	int rva004A6A58();

private:
	char m_pad[0x3D8];
	SlotOwner *m_slot;
};

int Rva004A6A58::rva004A6A58()
{
	int raw = m_slot->s4();
	int n;
	if (raw > 0)
		n = raw;
	else
		n = 1;
	int slept = ((AIUpdateInterface *)this)->AIUpdateInterface::update();
	if (n < slept)
		slept = n;
	return slept;
}
