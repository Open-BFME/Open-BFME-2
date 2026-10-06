// cl: /DNDEBUG /MD
// ?rva0056468E@Rva0056468E@@QAEPBVFXList@@XZ, retail 0x0056468E, 46 bytes.
// Lazy FXList cache twin of LifeEventModuleInfo::getEventFX @0x0056410F (same
// 46B shape, same callees): on first call resolves the event name (m_data at
// +4 with the +8 header skip, else the pinned empty string at 0x00BBAC1C)
// through TheFXListStore::findFXList (rowed 0x001E281A) and caches it at
// +0x18 (this class carries 4 extra bytes before the cache vs +0x14).
// Evidence: callers at 0x00564719 and 0x0056495A; unblocks 0x005646BC/135
// and 0x005648FE/157.

class AsciiString
{
public:
	char *m_data;
};

class FXList
{
};

class FXListStore
{
public:
	const FXList *findFXList(const char *name) const;
};

extern FXListStore *TheFXListStore;

class Rva0056468E
{
public:
	const FXList *rva0056468E();
private:
	char m_pad0[4];
	AsciiString m_eventName;
	char m_pad8[16];
	const FXList *m_cached;
};

const FXList *Rva0056468E::rva0056468E()
{
	if (m_cached == 0)
	{
		const char *name = m_eventName.m_data != 0 ? (const char *)m_eventName.m_data + 8 : "";
		m_cached = TheFXListStore->findFXList(name);
	}
	return m_cached;
}
