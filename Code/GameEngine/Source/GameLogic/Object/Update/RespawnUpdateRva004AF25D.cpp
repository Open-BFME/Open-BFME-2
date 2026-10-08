// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva004AF25D@RespawnUpdate@@QAEPAXXZ, retail 0x004AF25D, 50 bytes.
// Lazy RespawnUpdate getter: cached void at +0x28 (init -1 per ctor
// 0x004AF096) else lookup ModuleData string at +0x11C through global
// 0x00DFF000 via rowed 0x002D06CA else Object+4 fallback. Caller at
// 0x0029111F finds RespawnUpdate module then adds 0x64 for AsciiString.
#include "ascii_string.h"

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

extern class ThingFactory *TheThingFactory;

struct RespawnUpdateModuleDataRef
{
	char m_pad[0x11C];
	AsciiString m_str11C;
};

struct RespawnUpdateObjectRef
{
	char m_pad[4];
	void *m_unk04;
};

class RespawnUpdate
{
public:
	void *rva004AF25D();

private:
	void *m_vptr;
	RespawnUpdateModuleDataRef *m_moduleData;
	RespawnUpdateObjectRef *m_object;
	unsigned char m_pad0C[0x28 - 0x0C];
	void *m_cached;
};

void *RespawnUpdate::rva004AF25D()
{
	if (m_cached == (void *)-1) {
		void *found = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(&m_moduleData->m_str11C);
		m_cached = found;
		if (found == 0)
			m_cached = m_object->m_unk04;
	}
	return m_cached;
}
