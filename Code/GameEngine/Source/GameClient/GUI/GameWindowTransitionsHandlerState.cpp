// cl: /DNDEBUG /MD /EHsc
// ?isFinished@GameWindowTransitionsHandler@@QAE_NXZ @0x001DBFEE 46B
//
// Zero Hour's GameWindowTransitionsHandler::isFinished (current group's
// isFinished, true when there is none) under BFME 2's critical section at
// +0x38. Callers 0x001DC07E and Shell 0x0035BE55 load the receiver from
// TheTransitionHandler (0x00DFDC14); the donor-sweep pin in symbols.csv names
// this address isFinished. Callee row ?rva001DBD83@Rva001DBDA4@@QBE_NXZ
// (TransitionGroup); offsets from retail lea/mov. The class is the one whose
// ctor 0x001DCBC3 installs vftable 0x00BDBC30; slots 9 and 12 follow.
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *);

class GameMessage
{
public:
	enum Type
	{
		MSG_IDLE_70 = 0x70
	};
	void appendIntegerArgument(int arg);
};

class MessageStream
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual GameMessage *appendMessage(GameMessage::Type type);
};
extern class MessageStream *TheMessageStream;

class HandlerLock
{
public:
	HandlerLock(void *cs) : m_cs(cs) { EnterCriticalSection(m_cs); }
	~HandlerLock() { LeaveCriticalSection(m_cs); }
private:
	void *m_cs;
};

struct GroupView
{
	char _00[0x04];
	int m_dir;
	char _08[0x08];
	unsigned char m_fireOnce;
};

class Rva001DBDA4
{
public:
	bool rva001DBD83() const;
	void rva001DBE17();
	void rva001DBE51();
	void rva001DBD5D();
};

struct AudioLock
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
};

class GameWindowTransitionsHandler
{
public:
	bool isFinished();
	void rva001DBE6E();
	void rva001DBFD1();
	void rva001DBEB6();
private:
	char m_pad00[0x24];
	Rva001DBDA4 *m_24;
	Rva001DBDA4 *m_28;
	Rva001DBDA4 *m_2C;
	Rva001DBDA4 *m_30;
	char m_pad34[0x4];
	AudioLock m_38;
	char m_pad50;
	bool m_unk51;
	char m_pad52[0x17];
	bool m_69;
};

bool GameWindowTransitionsHandler::isFinished()
{
	EnterCriticalSection(&m_38);
	bool b;
	if (m_24)
		b = m_24->rva001DBD83();
	else
		b = true;
	LeaveCriticalSection(&m_38);
	return b;
}

// Retail 0x001DBE6E 72B: GameWindowTransitionsHandler slot 9 release of four Rva001DBDA4 lists plus clear byte at +0x69.
// Evidence: vtable 0x007DBC30 slot 9 of the handler ctor; rowed rva001DBE17 callee; offsets +0x24 +0x28 +0x30 +0x2C +0x69; neighbours 0x001DBE51 and 0x001DBFEE.
void GameWindowTransitionsHandler::rva001DBE6E()
{
	if (m_24)
	{
		m_24->rva001DBE17();
		m_24 = 0;
	}
	if (m_28)
	{
		m_28->rva001DBE17();
		m_28 = 0;
	}
	if (m_30)
	{
		m_30->rva001DBE17();
		m_30 = 0;
	}
	if (m_2C)
	{
		m_2C->rva001DBE17();
		m_2C = 0;
	}
	m_69 = false;
}

// Retail 0x001DBFD1 29B: GameWindowTransitionsHandler slot 12 apply rva001DBE51 to lists at +0x30 then +0x2C.
// Evidence: vtable 0x007DBC30 slot 12 of the handler ctor; rowed rva001DBE51 callee; offsets +0x30 +0x2C.
void GameWindowTransitionsHandler::rva001DBFD1()
{
	if (m_30)
		m_30->rva001DBE51();
	if (m_2C)
		m_2C->rva001DBE51();
}

// Retail 0x001DBEB6 283B: GameWindowTransitionsHandler vftable 0x00BDBC30 slot 10 update.
// Target evidence: slot adjacency (slot 9 0x1DBE6E + slot 12 0x1DBFD1 + isFinished 0x1DBFEE same TU/lock/layout);
// thiscall void with EH prolog (__EH_prolog 0x629188, cookie 0xB69886) holding CRITICAL_SECTION at +0x38
// across the whole body (Enter 0xBBA200 / Leave 0xBBA204, same pair as isFinished); group pointers
// +0x24 current / +0x28 pending / +0x2C draw / +0x30 secondary (BFME2 +4 shift of ZH/BFME1);
// rowed callees E17 (reset spell) / D83 (isFinished) / D5D (update-accumulate); direct tests
// [group+0x10] fireOnce and [group+0x04] direction<0 (Groups.cpp TransitionGroup layout);
// +0x69 hold flag with early return (still leaves lock via RAII) and +0x51 idle-notify flag
// (MessageStreamSubsystem 0x00E00950 slot 18 +0x48 appendMessage 0x70, same VA/slot as
// KeyboardInitUpdate and ReloadIniFileNotices); seven ZH-update-ordered phases in retail order.
// Donor-carried: BFME1 GameWindowTransitionsHandler::update 0x0048A320 300B logic (lock, secondary
// E17-reset, hold-gated fireOnce discard, MessageStream idle-notify) + ZH GameWindowTransitions.cpp
// update phase order; BFME2 deltas are target facts (+4 shifts, lock +0x38, 0x70 vs 0x6D, +0x51/+0x69).
void GameWindowTransitionsHandler::rva001DBEB6()
{
	HandlerLock lock(&m_38);
	if (m_2C != m_24)
	{
		if (m_30)
			m_30->rva001DBE17();
		m_30 = m_2C;
	}
	else if (m_30)
	{
		m_30->rva001DBE17();
		m_30 = 0;
	}
	Rva001DBDA4 *cur = m_24;
	m_2C = cur;
	if (cur && !cur->rva001DBD83())
		cur->rva001DBD5D();
	cur = m_24;
	if (cur && cur->rva001DBD83() && ((GroupView *)cur)->m_fireOnce && !m_28)
	{
		if (m_69)
			return;
		cur->rva001DBE17();
		m_24 = 0;
	}
	cur = m_24;
	if (cur && m_28 && cur->rva001DBD83())
	{
		cur->rva001DBE17();
		m_24 = m_28;
		m_28 = 0;
	}
	if (!m_24 && m_28)
	{
		m_24 = m_28;
		m_28 = 0;
	}
	cur = m_24;
	if (cur && cur->rva001DBD83() && ((GroupView *)cur)->m_dir < 0)
		m_24 = 0;
	if (m_unk51 && !m_24 && !m_28)
	{
		TheMessageStream->appendMessage(GameMessage::MSG_IDLE_70);
		m_unk51 = false;
	}
}
