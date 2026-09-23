// ??0AudioLoopUpgradeModuleData@@QAE@XZ
// partial score=0.96 date=2026-09-23
// cl: /O1 /MD /DNDEBUG /EHsc
//
// ??0AudioLoopUpgradeModuleData@@QAE@XZ, retail 0x004B7C00 (76 bytes). EH
// ModuleData ctor over a trivial base (no out-of-line call): installs vtable
// 0x00C58CF8, clears the +0x08/+0x0C words and sets the +0x10 flag, runs the
// +0x14 member setup through the rowed construct@Rva0025342CMember at
// 0x0025342C, then inits the +0x124 DieMuxData through the rowed
// init@DieMuxData at 0x004CE534 (which the DieMuxDataInit row notes is
// needed by AudioLoop). Two unwind states count the destructible members
// for the throwing calls. Donor: BFME1 Upgrade files (BFME2 appends the
// DieMuxData tail past the 0x110 member).

class Rva0025342CMember
{
public:
	Rva0025342CMember *construct();
	~Rva0025342CMember();

private:
	unsigned char m_opaque[0x110];
};

class DieMuxData
{
public:
	DieMuxData *init();

private:
	unsigned char m_opaque[0x30];
};

class UpgradeModuleData
{
public:
	virtual ~UpgradeModuleData();

protected:
	void *m_unsourced04;	// +0x04, retail never stores it
};

class AudioLoopUpgradeModuleData : public UpgradeModuleData
{
public:
	AudioLoopUpgradeModuleData();
	virtual ~AudioLoopUpgradeModuleData();

private:
	int m_int08;	// +0x08
	int m_int0C;	// +0x0C
	bool m_flag10;	// +0x10
	char m_pad11[3];	// +0x11, retail addresses the +0x14 member past it
	Rva0025342CMember m_member14;	// +0x14
	DieMuxData m_die124;	// +0x124
};

AudioLoopUpgradeModuleData::AudioLoopUpgradeModuleData()
{
	m_int08 = 0;
	m_int0C = 0;
	m_flag10 = true;
	m_member14.construct();
	m_die124.init();
}
