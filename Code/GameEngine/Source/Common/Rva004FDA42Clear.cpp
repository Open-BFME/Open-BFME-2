// cl: /O1 /DNDEBUG /MD /EHsc
//
// 0x004FDA42 (32B): call 0x1F34BA, then free the +0x101C pointer via
// rowed FreeGame when non-null and clear it. Identities unproven.

class Image;
class GameSlot;
class AsciiString;

struct BfmeNetAddress
{
	unsigned int m_ip;
	unsigned short m_port;
};

class GameInfo
{
public:
	GameInfo();
	virtual ~GameInfo();
	virtual void v1() = 0; virtual void v2() = 0; virtual void v3() = 0;
	virtual void v4() = 0; virtual void v5() = 0;
	virtual const Image *rva00401015(int column);
	virtual void v7() = 0; virtual void v8() = 0; virtual void v9() = 0;
	virtual void reset(void);			// slot 10 (+0x28)
	virtual void startGame(int gameID) = 0;		// slot 11
	virtual bool amIHost(void) const = 0;		// slot 12
	virtual int getLocalSlotNum(void) const = 0;	// slot 13 (+0x34)
	virtual void resetAccepted(void);
	void init();
	const GameSlot *getConstSlot(int slotNum) const;
	void setSlotPointer(int index, GameSlot *slot);
	GameSlot *getSlot(int slotNum);
	void setMap(AsciiString mapName);
	AsciiString getMap(void) const;
	void markPlayerAsPreorder(int index);
	void setGameInProgress(bool inProgress) { m_inProgress = inProgress; }
	unsigned int getSeed(void) const { return m_seed; }
private:
	char m_pad04[0x10 - 4];
protected:
	bool m_inGame; // +0x10
private:
	bool m_inProgress;				// +0x11
	char m_pad12[0x38 - 0x12];
protected:
	BfmeNetAddress m_localAddress;			// +0x38
private:
	char m_pad40[0x50 - 0x40];
	unsigned int m_seed;				// +0x50
	char m_pad54[0x58 - 0x54];
protected:
	int m_bfme58;					// +0x58
private:
	char m_pad5C[0x60 - 0x5C];
public:
	int m_bfme60;					// +0x60, zero when heroes are allowed
private:
	char m_pad64[0x6C - 0x64];
public:
	// Inline reads: retail 0x4FE5CA loads both into registers before pushing
	// them, where a plain member access is pushed from memory.
	int getCmdPointFactor(void) const { return m_bfme6C; }
	int getIniResource(void) const { return m_bfme70; }
	int m_bfme6C;					// +0x6C, the command point factor
	int m_bfme70;					// +0x70, the initial resources
private:
	char m_pad74[0xDC - 0x74];
};

extern "C" void __cdecl FreeGame(void *p);

class Rva004FDA42Owner
{
public:
	void rva004FDA42();

private:
	char m_pad[0x101C];	// +0x00..0x101B
	void *m_101C;		// +0x101C freed pointer
};

void Rva004FDA42Owner::rva004FDA42()
{
	((GameInfo *)this)->init();
	void *allocation = m_101C;
	if (allocation)
		FreeGame(allocation);
	m_101C = 0;
}
