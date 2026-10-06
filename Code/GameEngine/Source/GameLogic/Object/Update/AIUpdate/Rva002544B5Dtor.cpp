// cl: /MD
// ??1Rva002544B5@@UAE@XZ @0x002544B5 60B.
// WorkerAI-adjacent dtor (rowed ctor 0x00254434 plus factory 0x002544F1) landed
// under an honest address name because ??1WorkerAIUpdateModuleData@@UAE@XZ is
// already rowed at 0x00240831 (first-on-master wins; see re_attempts log).
// Destroys SoundHolder at +0x90 via rowed Release_Ref 0x00050ED3 when non-null
// then base TransportAIUpdateModuleData via twin pin at 0x0026E1FC (ICF fold
// under gen-uw pin ??1Gen_uwm_0026e1fc@@QAE@XZ). Layout from rowed ctor (base
// 0x64 plus +0x90 zeroed; factory news 0x94). No vptr store (novtable).
// Shape follows DeployStyle dtor 0x00255F70. Byte-exact body from banked
// reverse/attempts/0x002544b5.cpp (score 1.00) with only the class renamed.
class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct SoundHolder
{
	~SoundHolder()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}
	OpaqueRefCounted *m_ptr;
};

class __declspec(novtable) TransportAIUpdateModuleData
{
public:
	TransportAIUpdateModuleData();
	virtual ~TransportAIUpdateModuleData();

private:
	unsigned char m_pad[0x64 - 4];
};

class __declspec(novtable) Rva002544B5 : public TransportAIUpdateModuleData
{
public:
	virtual ~Rva002544B5();

private:
	unsigned char m_pad64[0x90 - 0x64];
	SoundHolder m_holder90; // +0x90 holder zeroed by ctor
};

Rva002544B5::~Rva002544B5()
{
}
