// cl: /DNDEBUG /MD /EHsc
// Ported from Open-BFME-1's game/GameEngineDevice/Source/W3DDevice/GameClient/W3DSmudgeManagerDestructor.cpp
// (donor revision 6583b3c1ff21db4a561285717028fdafc780b7db) with /O1 /arch:SSE
// added to its flags, the settings W3DView.cpp's donor bodies match under.
// Searched by masked whole-.text search, the body places once on unclaimed
// game.dat .text at 0x000A6454 (56B).

class SmudgeManager
{
public:
	virtual ~SmudgeManager();
};

class W3DSmudgeManager : public SmudgeManager
{
public:
	virtual ~W3DSmudgeManager();
	virtual void init();
	virtual void reset();
	virtual void ReleaseResources();
	virtual void ReAcquireResources();
};

W3DSmudgeManager::~W3DSmudgeManager()
{
	ReleaseResources();
}
