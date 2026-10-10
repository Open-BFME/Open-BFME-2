// cl: /EHsc /DNDEBUG /MD
//
// ??1EmotionTrackerUpdate@@UAE@XZ, retail 0x004B1322, 107 bytes.
// EmotionTrackerUpdate destructor: reinstalls the four vptrs (+0 0x00C5667C,
// +0x0C 0x00C565C0, +0x10 0x00C565B0, +0x20 0x00C565AC), destroys the +0xA4
// member through the rowed ??1Rva002EE9B7 (state 1), frees the +0x90 vector
// storage through the rowed _free (state 0), then calls the rowed base
// ??1UpdateModule at 0x0024A797 (state -1). Layout from the pinned ctor
// 0x004B21B9 (UpdateModule base 0x20, 12-bool + 12-int + 12-int arrays to
// 0x90, vector at 0x90, ints at 0x9C/0xA0, set/pool at 0xA4, tail to 0xC8)
// and the BFME1 EmotionTrackerUpdate donor (UpdateModule plus secondary base
// with bool/int/int arrays, vector, set, state tail). Base is the opaque
// rowed middle so the call mangles to the row name and links; vtable
// immediates are DIR32.

extern "C" void free(void *block) throw(...);

// UpdateModule carries its own three vptrs (+0x00/+0x0C/+0x10), as the
// pinned ctor 0x004B21B9 and UpdateModule::~UpdateModule 0x0024A797 show, so
// this unit's vftable names agree with the ctor's: the +0x10
// UpdateModuleInterface one (0x00C565B0) is
// ??_7EmotionTrackerUpdate@@6BUpdateModule@@@.
class ObjectModule
{
public:
	virtual ~ObjectModule();

private:
	char m_pad04[8];
};

class BehaviorModuleInterface
{
public:
	virtual void getBody();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule();

private:
	char m_pad14[12];
};

class EmotionTrackerUpdateSecondaryBase
{
public:
	virtual void slot();
};

class Rva002EE9B7
{
public:
	~Rva002EE9B7();

private:
	void *m_header;
	int m_flag;
};

struct EmotionTrackerVecHolder
{
	~EmotionTrackerVecHolder()
	{
		if (m_start != 0)
			free(m_start);
	}

	void *m_start;
	void *m_finish;
	void *m_end;
};

class EmotionTrackerUpdate : public UpdateModule, public EmotionTrackerUpdateSecondaryBase
{
public:
	virtual ~EmotionTrackerUpdate();

private:
	bool m_active[12]; // +0x24
	int m_startFrame[12]; // +0x30
	int m_endFrame[12]; // +0x60
	EmotionTrackerVecHolder m_emotions; // +0x90
	int m_unknown9C; // +0x9C
	int m_distributionIndex; // +0xA0
	Rva002EE9B7 m_pool; // +0xA4
	int m_padAC; // +0xAC
	int m_B0; // +0xB0
	int m_B4; // +0xB4
	int m_B8; // +0xB8
	int m_BC; // +0xBC
	bool m_enabled; // +0xC0
	unsigned char m_padC1[3];
	int m_C4; // +0xC4
};

// ??1EmotionTrackerUpdate@@UAE@XZ @0x004B1322
EmotionTrackerUpdate::~EmotionTrackerUpdate()
{
}
