// cl: /O1 /G7 /Oy- /MD /EHsc
// Clean BF1 PlayerListXfer.cpp donor at ba7ddda7e8 with target-specific
// Xfer::Version1 and signed-int slot31. WB D24980 names PlayerList::DoXfer
// in Common/RTS/PlayerList.cpp; retail 2A7D63..2A7DD0 proves the complete
// 109B boundary, local-player4/count8/player-pointer-arrayC and Snapshot12.
// The mismatch branch formats XferException tag5 and throws the existing
// type-info object recorded in data_ledger at8FFD18. No new pins or RTTI.
// This is an accessed prefix view; the total player-array bound stays open.

typedef unsigned char UnsignedByte;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Snapshot;

class Xfer
{
public:
	void Version1();
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion *);
	virtual void slot11();
	virtual void xferSnapshot(Snapshot *);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void xferInt(int *);
};

class Player;

class PlayerList
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void DoXfer(Xfer *xfer);

private:
	Player *m_local;
	int m_playerCount;
	Player *m_players[1];
};

struct BfmeFormattedText
{
	char *m_text;
	int m_tag;
};

union PlayerListXferLocal
{
	XferVersion version;
	BfmeFormattedText error;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(BfmeFormattedText *, int, const char *, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *, void *);
extern int g_guardTargetTypeThrowInfo;

void PlayerList::DoXfer(Xfer *xfer)
{
	PlayerListXferLocal local;
	xfer->Version1();

	int playerCount = m_playerCount;
	xfer->xferInt(&playerCount);
	if (playerCount != m_playerCount)
	{
		bfmeFormatText(&local.error, 5, 0);
		_CxxThrowException(&local.error, &g_guardTargetTypeThrowInfo);
	}

	for (int i = 0; i < playerCount; ++i)
		xfer->xferSnapshot(reinterpret_cast<Snapshot *>(m_players[i]));
}
