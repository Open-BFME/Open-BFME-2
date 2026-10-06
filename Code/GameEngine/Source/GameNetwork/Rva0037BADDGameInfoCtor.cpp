// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc

// ?rva0037BADD@Rva0037BADD@@QAE@XZ @0x0037BADD 112B: identity inferred
// from constructor shape shared with retail SkirmishGameInfoCtor.cpp;
// distinct vtable/global values leave donor identity unproven.
typedef int Int;

class GameSlot
{
public:
	GameSlot();
	virtual ~GameSlot();
private:
	char m_storage[0x1A8];
};

class GameInfo
{
public:
	GameInfo();
	virtual ~GameInfo();
	virtual void reset();
	void setSlotPointer(int index, GameSlot *slot);
private:
	char m_storage[0xD8];
};

class Rva0037BADD : public GameInfo
{
public:
	Rva0037BADD();
private:
	GameSlot m_skirmishSlot[8];
};

Rva0037BADD::Rva0037BADD()
{
	for (Int i = 0; i < 8; ++i)
		setSlotPointer(i, &m_skirmishSlot[i]);
}
