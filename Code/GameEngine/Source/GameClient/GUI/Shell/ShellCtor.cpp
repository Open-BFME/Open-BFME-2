// cl: /DNDEBUG /MD /EHs
// ??0Shell@@QAE@XZ @0x0035BFBC (203B): chain ctor calls baseConstruct 0x001B4E63 then sets vtable 0x00816208; clears stack +0xC-0x4B; String set at +0x58 with empty string; NEW AnimateWindowManager 0x38 at +0x60 via 0x0053B550; NEW Rva002007D5 8 at +0x64 via 0x00200774.
// Retail's unwind map destroys the SubsystemInterface-style base (0x001B4E74)
// in state 0 and the narrow string at +0x58 in state 1, then guards both
// allocations (states 2 and 3). The string therefore has a destructor; the
// banked 0.93 attempt gave it none and lost state 1.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class BFME2NativeNetwork
{
public:
	void baseConstruct();
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

class WindowLayout;
class AnimateWindowManager
{
public:
	AnimateWindowManager();
private:
	char m_pad[0x38];
};

class Rva002007D5
{
public:
	Rva002007D5();
private:
	char m_pad[8];
};

template <typename T>
class StringBase
{
public:
	StringBase() : m_data(0) {}
	~StringBase();
	void set(const T *str);
private:
	T *m_data;
};

class Shell : public BFME2NativeNetworkBase
{
public:
	Shell();
	virtual void init();
	virtual void reset();
	virtual void update();
private:
	WindowLayout *m_screenStack[16];
	int m_screenCount;
	unsigned char m_50;
	unsigned char m_51;
	unsigned char m_52;
	unsigned char m_53;
	unsigned char m_54;
	unsigned char m_pad55[3];
	StringBase<char> m_pendingPushName;
	bool m_isShellActive;
	bool m_shellMapOn;
	unsigned char m_pad5E[2];
	AnimateWindowManager *m_animate;
	Rva002007D5 *m_scheme;
	int m_68;
	bool m_6c;
	bool m_6d;
	unsigned char m_pad6E[2];
	int m_70;
	int m_74;
};

Shell::Shell()
{
	int i;
	m_screenCount = 0;
	for (i = 0; i < 16; i++)
		m_screenStack[i] = 0;
	m_52 = 0;
	m_53 = 0;
	m_50 = 0;
	m_51 = 0;
	m_54 = 0;
	m_pendingPushName.set("");
	m_isShellActive = true;
	m_shellMapOn = false;
	m_animate = new AnimateWindowManager;
	m_scheme = new Rva002007D5;
	m_68 = 1;
	m_6c = true;
	m_6d = true;
	m_70 = 0;
	m_74 = 0;
	m_screenCount = 0;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?update@Shell@@UAEXXZ=??1Coord2D@@QAE@XZ")
