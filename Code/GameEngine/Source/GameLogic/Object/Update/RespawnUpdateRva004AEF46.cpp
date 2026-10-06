// cl: /DNDEBUG /MD /GX
// ?rva004AEF46@RespawnUpdate@@QAEXXZ @0x004AEF46 103B
// Chain from Money 0x003B0D7C: RespawnUpdate state gate plus wake plus Money cond-add; layout from RespawnUpdateCtor and Rva004AEFAD.
// Evidence: callees getControllingPlayer 0x0028AFA9 setWakeFrame 0x0044DF71 Money 0x003B0D7C rowed; touches +0x2C +0x30 +0x34 +0x3C +0x40.
class Player;
class Object
{
public:
	Player *getControllingPlayer() const;
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class Thing;
class ModuleData;

class UpdateModule
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();

protected:
	void setWakeFrame(Object *object, UpdateSleepTime frame);

	const ModuleData *m_moduleData;
	Object *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

class Rva0039B7AD;
class Rva003B0D7C
{
public:
	void rva003B0D7C(int amount, Rva0039B7AD *arg2, bool flag);
};

class Player
{
public:
	char m_pad00[0x3C0];
};

class RespawnUpdate : public UpdateModule
{
public:
	void rva004AEF46();

private:
	float m_20;
	unsigned int m_24;
	unsigned int m_28;
	unsigned int m_2C;
	unsigned int m_30;
	unsigned int m_34;
	unsigned int m_38;
	unsigned int m_3C;
	unsigned char m_40;
	unsigned char m_41;
};

void RespawnUpdate::rva004AEF46()
{
	Object *obj = m_object;
	Player *player = obj->getControllingPlayer();
	Rva003B0D7C *money;
	if (player != 0)
		money = (Rva003B0D7C *)((char *)player + 0x90);
	else
		money = 0;
	if (m_2C == 0)
		return;
	m_2C = 1;
	setWakeFrame(obj, UPDATE_SLEEP_FOREVER);
	m_34 = (unsigned int)-1;
	m_30 = 0;
	m_40 = 1;
	money->rva003B0D7C(m_3C, (Rva0039B7AD *)((char *)player + 0x3BC), true);
}
