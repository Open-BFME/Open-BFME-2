// cl: /O1 /DNDEBUG /MD /EHsc /G7
//
// ?CreateGameEngine@@YAPAVGameEngine@@XZ,
// retail 0x00001D1F, 74 bytes. Dedicated shard.
//
// ZH WinMain.cpp CreateGameEngine donor (NEW Win32GameEngine 0x64 plus
// setIsActive(isWinMainActive) plus return) with BFME2 layout:
// - Win32GameEngine is 0x64 bytes (retail push immediate).
// - isWinMainActive is a byte global at 0x00DDE02A (retail mov cl).
// - setIsActive is vtable slot 25 (retail call [eax+0x64]); slots 1-24 are
//   currently unknown so they stay declared-only placeholders.
// - Win32GameEngine default ctor is pinned at 0x41D41 (sole caller here);
//   operator new resolves via its row. /G7 is the lever: it drops the
//   xor-before-mov-cl and orders mov-cl before mov-eax like retail;
//   /O1 without /G7 uses two LEAs/xor and mismatches by 2B.

extern bool g_Va00DDE02A;

class GameEngine
{
public:
	virtual ~GameEngine();
	virtual void m_unknown01();
	virtual void m_unknown02();
	virtual void m_unknown03();
	virtual void m_unknown04();
	virtual void m_unknown05();
	virtual void m_unknown06();
	virtual void m_unknown07();
	virtual void m_unknown08();
	virtual void m_unknown09();
	virtual void m_unknown10();
	virtual void m_unknown11();
	virtual void m_unknown12();
	virtual void m_unknown13();
	virtual void m_unknown14();
	virtual void m_unknown15();
	virtual void m_unknown16();
	virtual void m_unknown17();
	virtual void m_unknown18();
	virtual void m_unknown19();
	virtual void m_unknown20();
	virtual void m_unknown21();
	virtual void m_unknown22();
	virtual void m_unknown23();
	virtual void m_unknown24();
	virtual void setIsActive(bool active);
};

class Win32GameEngine : public GameEngine
{
public:
	Win32GameEngine();
	char m_unknownMembers[100 - 4];
};

GameEngine* CreateGameEngine()
{
	Win32GameEngine* engine = new Win32GameEngine;
	engine->setIsActive(g_Va00DDE02A);
	return engine;
}
