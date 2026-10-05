// ??0GameEngine@@QAE@XZ
// partial score=0.88 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE
// ??0GameEngine@@QAE@XZ
// retail 0x0022DA66 195 bytes. GameEngine ctor: base BFME2NativeNetwork
// baseConstruct at 0x1B4E63 then vtable 0x007E7188 then zero/one/float
// inits then timeBeginPeriod(1) then obfuscated array clear via rowed
// Rva00077710Value ops. Evidence: caller 0x41D44 Win32GameEngine ctor,
// pin ??0GameEngine, donor BFME1 GameEngine.cpp:194 trivial shape diverged.

extern "C" __declspec(dllimport) unsigned int __stdcall timeBeginPeriod(unsigned int uPeriod);
extern float g_Va00BBB8D8;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

extern "C++"
{
	int Rva0022CC0EHook(int a, int b);
}

class Rva00077710Value
{
public:
	bool operator!=(const Rva00077710Value &other) const;
	void rva0022D189(int value);
	Rva00077710Value *rva0022D89D(Rva00077710Value &other);
	int m_valuePublic;
	int m_valuePublic2;
};

class BFME2NativeNetwork
{
public:
	BFME2NativeNetwork *baseConstruct();
};

class __declspec(novtable) BFME2NativeNetworkBase
{
public:
	__forceinline BFME2NativeNetworkBase() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual ~BFME2NativeNetworkBase() { _ReadWriteBarrier(); }
private:
	char m_flag;
	int m_value;
};

class GameEngine : public BFME2NativeNetworkBase
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
	int m_0C;
	bool m_10;
	bool m_11;
	int m_14;
	int m_array18[7];
	int m_34;
	int m_38;
	float m_3C;
	bool m_40;
	float m_44;
	float m_48;
	int m_4C;
	int m_50;
	int m_54;
	float m_58;
	int m_5C;
};

// ??0GameEngine@@QAE@XZ present-unmatched
GameEngine::GameEngine() : BFME2NativeNetworkBase()
{
	float earlyFloat = g_Va00BBB8D8;
	m_0C = 0;
	m_10 = false;
	m_11 = false;
	m_14 = 0;
	m_34 = 0;
	m_38 = 1;
	m_3C = 0.0f;
	m_40 = false;
	m_44 = earlyFloat;
	m_48 = 0.0f;
	m_4C = 0;
	m_50 = 0;
	m_54 = 0;
	m_58 = 0.0f;
	m_5C = 0;
	timeBeginPeriod(1);
	Rva00077710Value cur;
	cur.rva0022D189(0);
	Rva00077710Value limit;
	limit.m_valuePublic2 = (int)0xE0092DC0;
	Rva00077710Value dummy;
	while (cur != limit)
	{
		m_array18[Rva0022CC0EHook(cur.m_valuePublic2, cur.m_valuePublic2)] = 0;
		cur.rva0022D89D(dummy);
	}
}
