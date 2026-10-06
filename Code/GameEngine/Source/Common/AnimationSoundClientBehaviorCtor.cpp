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
extern "C" const void *const vtbl_00C6FFFC[];  // folded, 10 classes; via ??_7?$CategoryModuleClass@$00@FXParticleSystem@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6FFFC=??_7?$CategoryModuleClass@$00@FXParticleSystem@@6B@")

extern "C" const void *const vtbl_00C5EE74[];  // ??_7AnimationSoundClientBehavior@@6BASCB_Iface@@@
#pragma comment(linker, "/alternatename:_vtbl_00C5EE74=??_7AnimationSoundClientBehavior@@6BASCB_Iface@@@")
extern "C" const void *const vtbl_00C5EE80[];  // ??_7AnimationSoundClientBehavior@@6BPrimaryP@@@
#pragma comment(linker, "/alternatename:_vtbl_00C5EE80=??_7AnimationSoundClientBehavior@@6BPrimaryP@@@")

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

class ModuleData
{
public:
	virtual ~ModuleData();
	int m_unmodelled04;
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
	char m_pad[0x14];
	Rva00432F23Node *m_next;
	Rva00432F23Node *m_prev;
};

class Rva00432F23
{
public:
	void rva00432F7D(Rva00432F23Node *node);
};

extern Rva00432F23 *g_004C9DC9Container;

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
	float fzero = 0.0f;
	int *slotInit = (int *)&m_secondary0C;
	*slotInit = (int)((unsigned int)vtbl_00C6FFFC);
	m_next14 = 0;
	m_prev18 = 0;
	int *vtab = (int *)this;
	*vtab = (int)((unsigned int)vtbl_00C5EE80);
	int *sec0C = (int *)&m_secondary0C;
	*sec0C = (int)((unsigned int)vtbl_00C5EE74);
	if (TheAudio == 0)
	{
		m_float10 = fzero;
	}
	else
	{
		const ModuleData *mod = m_moduleData04;
		float maxVal = fzero;
		_STL::_Rb_tree_node_base *node = mod->m_header08->_M_left;
		if (node != mod->m_header08)
		{
			do
			{
				Payload98 *p = *(Payload98 **)((char *)node + 0x14);
				p = (Payload98 *)((char *)p + 0x98);
				_ReadWriteBarrier();
				float v = *(float *)p;
				if (v > maxVal)
					maxVal = v;
				node = _STL::_Rb_global<bool>::_M_increment(node);
			} while (node != mod->m_header08);
		}
		if (maxVal > mod->m_max14)
			maxVal = mod->m_max14;
		m_float10 = maxVal * maxVal;
		if (g_004C9DC9Container)
			g_004C9DC9Container->rva00432F7D((Rva00432F23Node *)this);
	}
}
