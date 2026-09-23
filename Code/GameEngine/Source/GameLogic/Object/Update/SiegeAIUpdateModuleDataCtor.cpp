// cl: /O1 /DNDEBUG /MD
//
// ??0SiegeAIUpdateModuleData@@QAE@XZ, retail 0x004904D9, 18 bytes.
// ModuleData ctor over the pinned TransportAIUpdateModuleData base
// (0x26E5D7): installs vtable 0x00C4B6C8 explicitly (novtable; no new
// members initialized here). Class size 0x64 proven by the SiegeAIUpdate
// data factory (news 0x64, sole caller at 0x24D4EC). Row supersedes the
// ctor pin.

class __declspec(novtable) TransportAIUpdateModuleData
{
public:
	TransportAIUpdateModuleData();
	virtual ~TransportAIUpdateModuleData();

private:
	// +0x00 vptr (novtable: no compiler install here).
	// Remainder is opaque (0x60 bytes); only the 0x64 size matters.
	unsigned char m_opaque[0x60];
};

class __declspec(novtable) SiegeAIUpdateModuleData : public TransportAIUpdateModuleData
{
public:
	SiegeAIUpdateModuleData();
};

// ??0SiegeAIUpdateModuleData@@QAE@XZ @0x004904D9
SiegeAIUpdateModuleData::SiegeAIUpdateModuleData()
	: TransportAIUpdateModuleData()
{
	*(unsigned int *)this = 0x00C4B6C8;
}
