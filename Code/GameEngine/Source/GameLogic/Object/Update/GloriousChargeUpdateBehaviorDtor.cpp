// cl: /O1 /DNDEBUG /MD /GX- /arch:SSE
//
// ??1GloriousChargeUpdate@@UAE@XZ, retail 0x004AD58C, 60 bytes. Virtual dtor
// shard: ctor TU keeps its verified shape untouched, so the class is
// re-declared here with the ctor declared-only and only the dtor defined.
//
// Shape follows the RousingSpeechUpdate dtor precedent: explicit 4 vtable
// installs plus freelist-node member at +0x88 via pinned reset plus
// pool-free via 0x268902 pin plus implicit Rva0044EF5E base-dtor tail call.
// The class is proven by the poolkey, name getter, ModuleData and instance
// factories plus the ctor installing these same 4 vtables. Zero new pins.

class Thing;
class ModuleData;

class Rva0044EF5E
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva0044EF5E();
private:
	char m_pad[0x88];
};

class Rva0029FB3BMember
{
public:
	void init(void *context);
	void reset();
};

class PoolMember
{
public:
	void Rva00268902();
};

class GloriousChargeUpdate : public Rva0044EF5E
{
public:
	GloriousChargeUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~GloriousChargeUpdate();
private:
	Rva0029FB3BMember m_88;
	int m_8C;
	unsigned char m_90;
};

// ??1GloriousChargeUpdate@@UAE@XZ @0x004AD58C
GloriousChargeUpdate::~GloriousChargeUpdate()
{
	Rva0029FB3BMember *member = (Rva0029FB3BMember *)((char *)this + 0x88);
	*(const void **)this = (const void *)0x00C55118;
	*(const void **)((char *)this + 0x0C) = (const void *)0x00C4D640;
	*(const void **)((char *)this + 0x10) = (const void *)0x00C55108;
	*(const void **)((char *)this + 0x20) = (const void *)0x00C552A4;
	member->reset();
	((PoolMember *)member)->Rva00268902();
}
