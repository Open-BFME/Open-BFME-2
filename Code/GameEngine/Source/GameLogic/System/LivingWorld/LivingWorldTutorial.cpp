// cl: /O1 /EHsc /MD /arch:SSE
// LivingWorldTutorial.cpp -- tutorial session-task members recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names the
// function and getRegionParam (0x003F83FE, rowed under a placeholder name);
// retail supplies the bytes. The battle comes from the living-world logic's
// region manager (+0xB0) through 0x0020E57F (unnamed).

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
typedef int Int;

class Rva0020E57FManager
{
public:
	void *rva0020E57F(void *region);	// 0x0020E57F
};

class Rva002BA8F1Logic
{
public:
	unsigned char m_pad00[0xb0];
	Rva0020E57FManager *m_regionManager;	// +0xB0
};

	// TheLivingWorldLogic

class Rva003F802B
{
public:
	bool rva003F802B();
private:
	unsigned char m_pad00[8];
	void *m_08;
	int m_0C;
};

class LivingWorldTutorial
{
public:
	class SessionTask
	{
	public:
		void *getBattleParam(Int index);
		void *getRegionParam(Int index);	// 0x003F83FE
		void create();				// 0x003F88BC (WB name, unrowed)
	};

	// A phase session holds the task it creates once its audio is done
	// (+0x14) and a created flag (+0x18).
	class PhaseSession
		: public Rva003F802B
	{
	public:
		void createTaskAfterAudio();
		void rva003F8F94();

	private:
		unsigned char m_pad10[4];
		SessionTask *m_task;			// +0x14
		bool m_taskCreated;			// +0x18
	};
};

// LivingWorldTutorial::SessionTask::getBattleParam, retail 0x003F841D.
void *LivingWorldTutorial::SessionTask::getBattleParam(Int index)
{
	void *region = getRegionParam(index);
	if (region)
	{
		Rva0020E57FManager *manager = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->m_regionManager;
		return manager->rva0020E57F(region);
	}
	return 0;
}

// LivingWorldTutorial::PhaseSession::createTaskAfterAudio, retail 0x003F8DAB
// (21 bytes): WB names it (asserts !isAudioPlaying() at
// LivingWorldTutorial.cpp:1006, compiled out of retail) and its callee
// SessionTask::create.
void LivingWorldTutorial::PhaseSession::createTaskAfterAudio()
{
	if (m_task)
		m_task->create();
	m_taskCreated = true;
}

void LivingWorldTutorial::PhaseSession::rva003F8F94()
{
	if (rva003F802B())
		return;
	if (!m_taskCreated)
	{
		createTaskAfterAudio();
		m_taskCreated = true;
	}
}
