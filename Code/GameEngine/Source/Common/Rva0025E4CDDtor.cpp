// cl: /MD /EHsc
// ??1Rva0025E4CD@@UAE@XZ retail 0x0025E4CD 80B
// Own vptr BF6040; under EH state 0 the object at +0xC is destroyed through
// the rowed non-virtual dtor ??1Rva004D2344@@QAE@XZ 0x004D2344 and freed with
// the global ??3@YAXPAX@Z; the intermediate base's inline dtor restores BF5F30
// and the rowed base dtor ??1GameEngineDeletingBase@@UAE@XZ 0x001B4E74 runs.
// Names address-derived.

class Rva004D2344
{
public:
	~Rva004D2344();
};

void *operator new(unsigned int size);
void operator delete(void *p);

class ConnectionManager
{
public:
	ConnectionManager();
	virtual void init();
	virtual void reset();
	virtual void update(bool isInGame, int frameAdvanced);
private:
	char m_pad[0x121AC];
};

class GameLogic
{
public:
	void rva0023D17D();
};

extern GameLogic *TheGameLogic;
extern unsigned int g_00DFEA2C;

struct LARGE_INTEGER
{
	int LowPart;
	int HighPart;
};

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(LARGE_INTEGER *freq);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(LARGE_INTEGER *counter);
extern "C" __declspec(dllimport) unsigned int __stdcall timeGetTime();

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();

private:
	char m_pad04[8];
};

class Rva0025E4CDBase : public GameEngineDeletingBase
{
public:
	virtual ~Rva0025E4CDBase() {}
};

class Rva0025E4CD : public Rva0025E4CDBase
{
public:
	virtual ~Rva0025E4CD();
	void rva0025DF01();

private:
	union
	{
		Rva004D2344 *m_rva;
		ConnectionManager *m_conn;
	};
	int m_10;
	char m_pad14[4];
	LARGE_INTEGER m_18;
	LARGE_INTEGER m_20;
	int m_28;
	int m_2C;
	bool m_30;
	char m_pad31[3];
	int m_34;
	char m_pad38[4];
	int m_3C;
};

Rva0025E4CD::~Rva0025E4CD()
{
	delete m_rva;
}

void Rva0025E4CD::rva0025DF01()
{
	if (m_rva)
		delete m_rva;
	m_conn = new ConnectionManager;
	m_conn->init();
	m_10 = 0;
	QueryPerformanceFrequency(&m_18);
	QueryPerformanceCounter(&m_20);
	m_28 = 0;
	m_2C = 0;
	unsigned int t = timeGetTime();
	m_30 = false;
	m_34 = 0;
	g_00DFEA2C = t;
	TheGameLogic->rva0023D17D();
	m_3C = -1;
}
