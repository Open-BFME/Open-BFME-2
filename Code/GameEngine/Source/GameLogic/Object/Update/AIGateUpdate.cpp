// cl: /O1 /EHsc /MD /arch:SSE
// AIGateUpdate.cpp -- AIGateUpdate members recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv): WB's debug build names the function; retail
// supplies the bytes.
//
// The gate's opener is looked up once for the owning object (+0x08) by the
// unrowed cdecl helper 0x00498725 (unnamed in WB) and cached at +0x20.

class Object;
class GateOpener;

GateOpener *rva00498725(Object *gate);			// 0x00498725

class AIGateUpdate
{
public:
	GateOpener *getOpener();

private:
	void *m_vtbl;
	unsigned char m_pad04[4];
	Object *m_object;				// +0x08
	unsigned char m_pad0C[0x20 - 0xc];
	GateOpener *m_opener;				// +0x20
};

// AIGateUpdate::getOpener, retail 0x004B0942.
GateOpener *AIGateUpdate::getOpener()
{
	if (m_opener == 0)
		m_opener = rva00498725(m_object);
	return m_opener;
}
