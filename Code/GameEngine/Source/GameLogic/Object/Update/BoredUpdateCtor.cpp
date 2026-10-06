// cl: /GX /DNDEBUG /MD
//
// ??0BoredUpdate@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x00496791, 98 bytes. Dedicated TU: the Update ctor runs the
// rowed UpdateModule base ctor (thing plus data), re-stores the inherited
// +0x0C/+0x10/+0x20 pointer slots (address-of TU-local dummies,
// DIR32-masked), zeroes the scan timer, then adds a GetGameLogicRandomValue
// (rowed) roll over the owner's scan range with the TU file and line. The
// declared-only base dtor drives the single EH state with zero emitted code.
// Do NOT declare an explicit vptr member on the base: the compiler's hidden
// vptr already sits at +0 and a declared one shifts every slot by 4.
// Recipe: OCLUpdateCtor.cpp opaque-base pattern with the rowed BoredUpdate
// file-unit (pool key plus proc plus factories) and the UpdateModule base
// truth ([esi+4] owner). The row supersedes the sole-caller pin at the same
// address.

class Thing;
class ModuleData;

struct BoredScanRange
{
	int m_pad00;
	int m_pad04;
	int m_maxScanDistance;
};

static int s_dummy0C;
static int s_dummy10;

static const char s_boredUpdateFile[] = "BoredUpdate";

int __cdecl GetGameLogicRandomValue(int low, int high, char *file, int line);

// Opaque UpdateModule base; ctor resolves to its row. Protected slots mirror
// the retail stores.
class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();

protected:
	BoredScanRange *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad2[0x20 - 0x14];
	int m_scanTimer;
};

class BoredUpdate : public UpdateModule
{
public:
	BoredUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~BoredUpdate();
};

// ??0BoredUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
BoredUpdate::BoredUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	BoredScanRange *owner = m_owner;
	m_p0C = &s_dummy0C;
	m_p10 = &s_dummy10;
	m_scanTimer = 0;
	m_scanTimer += GetGameLogicRandomValue(0, owner->m_maxScanDistance, const_cast<char *>(s_boredUpdateFile), 70);
}
