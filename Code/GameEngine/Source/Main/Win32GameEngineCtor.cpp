// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??0Win32GameEngine@@QAE@XZ,
// retail 0x00041D41, 29 bytes. Dedicated shard.
//
// ZH Win32GameEngine.cpp donor verbatim: base GameEngine ctor plus
// SetErrorMode(SEM_FAILCRITICALERRORS) saved to m_previousErrorMode at
// +0x60 plus Win32 vtable 0xBC2530. Base ctor is pinned at 0x22DA66;
// SetErrorMode resolves via its kernel32 import. Shard (not graft into
// CreateGameEngine.cpp) so the landed parent keeps calling out-of-line.

extern "C" __declspec(dllimport) unsigned int __stdcall SetErrorMode(unsigned int mode);

class GameEngine
{
public:
	GameEngine();
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

private:
	char m_padAfterVtable[0x60 - 4];
};

class Win32GameEngine : public GameEngine
{
public:
	Win32GameEngine();

private:
	unsigned int m_previousErrorMode;
};

Win32GameEngine::Win32GameEngine()
{
	m_previousErrorMode = SetErrorMode(1);
}
