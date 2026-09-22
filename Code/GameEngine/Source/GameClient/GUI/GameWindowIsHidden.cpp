// cl: /O1 /DNDEBUG /MD
// ?winIsHidden@GameWindow@@QAE_NXZ @0x00313CD9
// Shard TU: TextOnFrameTransitionInit.cpp calls this out-of-line; defining
// it there inlines and breaks init, so it lives here.

typedef bool Bool;

class GameWindow
{
public:
	Bool winIsHidden(void);

private:
	char m_pad00[8];
	unsigned int m_status;
};

// ?winIsHidden@GameWindow@@QAE_NXZ
Bool GameWindow::winIsHidden(void)
{
	return (m_status >> 4) & 1;
}
