// cl: /DNDEBUG /MD /EHsc
// ??0AnimationSoundClientBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004CA05A, 203 bytes.
// AnimationSoundClientBehavior (Thing*,ModuleData*) ctor: base Rva00252B68,
// volatile-first C6FFFC at +0x0C then primary C5EE80 plus secondary C5EE74,
// zero links at +0x14/+0x18, TheAudio-gated max-range over the ModuleData
// map (payload float at +0x98, second at node +0x14 via rowed _M_increment),
// clamp to ModuleData +0x14, square to +0x10, insert via rowed rva00432F7D.
// Donor: BFME1 AnimationSoundClientBehaviorCtorThunk (same double-store plus
// global check plus max loop; BFME2 adds SSE plus 0x98 plus squaring plus
// container). Caller at 0x00252BB1 in friend_newModuleInstance; vtables
// C5EE80/C5EE74 DIR32; container 0x00A032D0; TheAudio 0x009FE6E8.
extern "C" const void *const __identifier("??_7?$CategoryModuleClass@$04@FXParticleSystem@@6B@")[];  // folded vftable 0x00C6FFFC (10 classes), by its data-ledger name

extern "C" const void *const __identifier("??_7AnimationSoundClientBehavior@@6BRva004C9E33Iface@@@")[];  // vftable 0x00C5EE74
extern "C" const void *const __identifier("??_7AnimationSoundClientBehavior@@6BRva004C9DC9Primary@@@")[];  // vftable 0x00C5EE80

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

class Thing;

struct Payload98
{
	char m_pad[0x98];
	float m_range98;
};

namespace _STL
{
typedef bool _Rb_tree_Color_type;
struct _Rb_tree_node_base
{
	_Rb_tree_Color_type _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};
template <class Dummy>
class _Rb_global
{
public:
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);
};
}

#include "../../Include/Common/ModuleData.h"

class AnimationSoundClientBehaviorModuleData : public ModuleData
{
public:
	_STL::_Rb_tree_node_base *m_header08;
	int m_unmodelled0C;
	int m_unmodelled10;
	float m_max14;
};

class Rva00252B68
{
public:
	Rva00252B68(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva00252B68();
	const ModuleData *m_moduleData04;
	void *m_drawable08;
};

class Rva00432F23Node
{
public:
	char m_pad00[0x14];
	Rva00432F23Node *m_next; // +0x14
	Rva00432F23Node *m_prev; // +0x18
};

#include "../../Include/Common/AnimationSoundModuleManager.h"

extern AnimationSoundModuleManager *TheAnimationSoundModuleManager;

class AudioManager;
extern AudioManager *TheAudio;
// TheAudio: matched references place it at VA 0xdfe6e8 (zero-filled .bss).
AudioManager * TheAudio;

class AnimationSoundClientBehavior : public Rva00252B68
{
public:
	AnimationSoundClientBehavior(Thing *thing, const ModuleData *moduleData);
private:
	int m_secondary0C;
	float m_float10;
	Rva00432F23Node *m_next14;
	Rva00432F23Node *m_prev18;
};

AnimationSoundClientBehavior::AnimationSoundClientBehavior(Thing *thing, const ModuleData *moduleData)
	: Rva00252B68(thing, moduleData)
{
	float zeroRange = 0.0f;
	int *initialSecondaryVtableSlot = (int *)&m_secondary0C;
	*initialSecondaryVtableSlot = (int)((unsigned int)__identifier("??_7?$CategoryModuleClass@$04@FXParticleSystem@@6B@"));
	m_next14 = 0;
	m_prev18 = 0;
	int *primaryVtableSlot = (int *)this;
	*primaryVtableSlot = (int)((unsigned int)__identifier("??_7AnimationSoundClientBehavior@@6BRva004C9DC9Primary@@@"));
	int *secondaryVtableSlot = (int *)&m_secondary0C;
	*secondaryVtableSlot = (int)((unsigned int)__identifier("??_7AnimationSoundClientBehavior@@6BRva004C9E33Iface@@@"));
	if (TheAudio == 0)
	{
		m_float10 = zeroRange;
	}
	else
	{
		const AnimationSoundClientBehaviorModuleData *behaviorData = static_cast<const AnimationSoundClientBehaviorModuleData *>(m_moduleData04);
		float maximumRange = zeroRange;
		_STL::_Rb_tree_node_base *node = behaviorData->m_header08->_M_left;
		if (node != behaviorData->m_header08)
		{
			do
			{
				Payload98 *rangePayload = *(Payload98 **)((char *)node + 0x14);
				rangePayload = (Payload98 *)((char *)rangePayload + 0x98);
				_ReadWriteBarrier();
				float soundRange = *(float *)rangePayload;
				if (soundRange > maximumRange)
					maximumRange = soundRange;
				node = _STL::_Rb_global<bool>::_M_increment(node);
			} while (node != behaviorData->m_header08);
		}
		if (maximumRange > behaviorData->m_max14)
			maximumRange = behaviorData->m_max14;
		m_float10 = maximumRange * maximumRange;
		if (TheAnimationSoundModuleManager)
			TheAnimationSoundModuleManager->rva00432F7D((Rva00432F23Node *)this);
	}
}
