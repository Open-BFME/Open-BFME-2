// cl: /MD
//
// ??0ScoreScaleUpTransition@@QAE@XZ @0x0035D6B8 37B.
// Ctor via base Rva001DBAA4 plus vtable 0x00816510 with +4=6 +9=1 +0xC=0 +0x20=-1.
// Evidence: vtable store, caller 0x0035D71B, callee 0x001DBAA4 row.
class GameWindow;
class Rva001DBAA4
{
public:
	Rva001DBAA4();
	virtual ~Rva001DBAA4();
	int m_frameLength; // +0x04 +0x04 +0x04
	bool m_isFinished; // +0x08 +0x08 +0x08
	bool m_isForward; // +0x09 +0x09 +0x09
	bool m_isReversed; // +0x0A +0x0A +0x0a
	char m_pad0B[0x1];
	GameWindow *m_win; // +0x0C +0x0C +0x0c
};

class ScoreScaleUpTransition : public Rva001DBAA4
{
public:
	ScoreScaleUpTransition();
	virtual ~ScoreScaleUpTransition();
private:
	char m_pad10[0x20 - 0x10];
	int m_20;
};

ScoreScaleUpTransition::ScoreScaleUpTransition()
{
	m_frameLength = 6;
	m_isForward = true;
	m_win = 0;
	m_20 = -1;
}
