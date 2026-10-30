// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /EHsc /MD /DNDEBUG
// ?rva0048C7BF@FlammableUpdate@@QAEXXZ @0x0048C7BF 96B
// Evidence: rowed ??0BfmeAudioEventPrefix136 ObjectID overload 0x002DA461 plus rowed ??1BfmeStringTailRecord144 0x002D9A43 plus TheAudio 0x009FE6E8 slot 0x64 addAudioEvent storing handle to +0x34; neighbours FlammableUpdate doAflameDamage and FlammableUpdate layout with m_34 audio handle.
#include "Common/BfmeAudioEventPrefix136.h"

enum ObjectID
{
	INVALID_ID = 0
};

class Object
{
public:
	char m_pad00[0x74];
	ObjectID m_id74;
};

struct FlammableUpdateModuleData
{
	char m_pad00[0x18];
	OpaqueRefElement4 m_ref18;
};

struct BfmeAudioEventPrefix136;
class Xfer;
struct AbilityMiscAudio;
class AudioManager
{
public:
	virtual void _pad00() = 0;
	virtual void _pad01() = 0;
	virtual void _pad02() = 0;
	virtual void _pad03() = 0;
	virtual void _pad04() = 0;
	virtual void _pad05() = 0;
	virtual void _pad06() = 0;
	virtual void _pad07() = 0;
	virtual void _pad08() = 0;
	virtual void _pad09() = 0;
	virtual void _pad10() = 0;
	virtual void _pad11() = 0;
	virtual void _pad12() = 0;
	virtual void _pad13() = 0;
	virtual void _pad14() = 0;
	virtual void _pad15() = 0;
	virtual void _pad16() = 0;
	virtual void _pad17() = 0;
	virtual void _pad18() = 0;
	virtual void _pad19() = 0;
	virtual void _pad20() = 0;
	virtual void _pad21() = 0;
	virtual void _pad22() = 0;
	virtual void _pad23() = 0;
	virtual void _pad24() = 0;
	// vslot 25 (+0x64)
	virtual int addAudioEvent(BfmeAudioEventPrefix136 *event) = 0;
	virtual void _pad26() = 0;
	// vslot 27 (+0x6C)
	virtual void removeAudioEvent(unsigned int handle) = 0;
	virtual void _pad28() = 0;
	virtual void _pad29() = 0;
	virtual void _pad30() = 0;
	virtual void _pad31() = 0;
	virtual void _pad32() = 0;
	virtual void _pad33() = 0;
	virtual void _pad34() = 0;
	virtual void _pad35() = 0;
	virtual void _pad36() = 0;
	virtual void _pad37() = 0;
	virtual void _pad38() = 0;
	virtual void _pad39() = 0;
	virtual void _pad40() = 0;
	virtual void _pad41() = 0;
	virtual void _pad42() = 0;
	virtual void _pad43() = 0;
	virtual void _pad44() = 0;
	virtual void _pad45() = 0;
	virtual void _pad46() = 0;
	virtual void _pad47() = 0;
	virtual void _pad48() = 0;
	virtual void _pad49() = 0;
	virtual void _pad50() = 0;
	virtual void _pad51() = 0;
	// vslot 52 (+0xD0)
	virtual bool isCurrentlyPlaying(int handle) = 0;
	virtual void _pad53() = 0;
	virtual void _pad54() = 0;
	virtual void _pad55() = 0;
	virtual void _pad56() = 0;
	virtual void _pad57() = 0;
	virtual void _pad58() = 0;
	virtual void _pad59() = 0;
	virtual void _pad60() = 0;
	virtual void _pad61() = 0;
	virtual void _pad62() = 0;
	virtual void _pad63() = 0;
	virtual void _pad64() = 0;
	virtual void _pad65() = 0;
	virtual void _pad66() = 0;
	virtual void _pad67() = 0;
	virtual void _pad68() = 0;
	virtual void _pad69() = 0;
	virtual void _pad70() = 0;
	virtual void _pad71() = 0;
	virtual void _pad72() = 0;
	virtual void _pad73() = 0;
	virtual void _pad74() = 0;
	virtual void _pad75() = 0;
	virtual void _pad76() = 0;
	virtual void _pad77() = 0;
	// vslot 78 (+0x138)
	virtual AbilityMiscAudio * getMiscAudio() = 0;
	virtual void _pad79() = 0;
	virtual void _pad80() = 0;
	virtual void _pad81() = 0;
	virtual void _pad82() = 0;
	virtual void _pad83() = 0;
	virtual void _pad84() = 0;
	virtual void _pad85() = 0;
	virtual void _pad86() = 0;
	virtual void _pad87() = 0;
	// vslot 88 (+0x160)
	virtual void xferAudioHandle(Xfer *xfer, unsigned int *handle) = 0;
};

extern AudioManager *TheAudio;

class FlammableUpdate
{
public:
	void rva0048C7BF();
private:
	const void *m_vtable;
	const FlammableUpdateModuleData *m_moduleData;
	Object *m_object;
	char m_pad0C[0x34 - 0x0C];
	int m_handle34;
};

void FlammableUpdate::rva0048C7BF()
{
	const FlammableUpdateModuleData *md = m_moduleData;
	Object *obj = m_object;
	BfmeAudioEventPrefix136 evt(md->m_ref18, obj->m_id74);
	m_handle34 = TheAudio->addAudioEvent(&evt);
}
