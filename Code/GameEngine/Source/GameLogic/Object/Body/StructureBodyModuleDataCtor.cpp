// cl: /O1 /arch:SSE /GX /Oy- /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0StructureBodyModuleData@@QAE@XZ, retail 0x00257006, 101 bytes.
// Structure-body module data: the rowed StructureBody pool key at
// 0x4C09B5, the rowed chained proc at 0x2514AF (ActiveBody base plus own
// table), the rowed behavior ctor at 0x4C0951 and the rowed ModuleData
// factory at 0x25708C (ModuleFactory registers StructureBody with it)
// prove the class; the factory sole-calls this ctor. Shape follows the
// ChinookAIUpdate precedent (opaque empty ActiveBody base through the
// rowed 0x4BF59F spelling, explicit vtable first member) with the
// SupplyTruck HealingBuffFx tail verbatim: materialized healing-default
// reference out of TheGlobalData plus inline c_str plus rowed isEmpty
// 0x1E2F plus rowed findFXList 0x1E281A. The empty base carries a
// declared-only dtor so single-state EH arms with zero code (Topple
// precedent); the base leaves +0x48 alone so no zero store precedes the
// guarded fill.

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	void clear();
	~AsciiString();

	void set(const char *str);
	bool isEmpty() const;
	const char *c_str() const { return m_data ? (const char *)m_data + 8 : ""; }

private:
	void *m_data;
};

class GlobalData
{
public:
	unsigned char m_pad[0x9E0];
	AsciiString m_healingBuff;
};

extern GlobalData *TheGlobalData;

class FXList;
class FXListStore
{
public:
	const FXList *findFXList(const char *name) const;
};

extern FXListStore *TheFXListStore;

class ActiveBodyModuleData
{
public:
	ActiveBodyModuleData();
	~ActiveBodyModuleData();
};

class StructureBodyModuleData : public ActiveBodyModuleData
{
public:
	StructureBodyModuleData();

private:
	const void *m_vtable; // +0
	unsigned char m_pad[0x48 - 4]; // +4
	const FXList *m_healingBuffFx; // +0x48
};

// ??0StructureBodyModuleData@@QAE@XZ @0x257006
StructureBodyModuleData::StructureBodyModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00BF4028))
{
	AsciiString &healingDefault = TheGlobalData->m_healingBuff;
	if (!healingDefault.isEmpty())
		m_healingBuffFx = TheFXListStore->findFXList(healingDefault.c_str());
}
