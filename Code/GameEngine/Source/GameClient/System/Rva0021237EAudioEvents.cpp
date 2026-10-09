// cl: /O1 /G7 /arch:SSE /DNDEBUG /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?rva0021237E@Rva0021237E@@QAEXXZ @0x0021237E 64B
// The target walks the four-byte range at this+0x2CC, passes each word to
// TheAudio's slot 0x6C, then erases the whole range through rowed vector erase
// 0x0031BD55. TheAudio is pinned at VA 0x00DFE6E8. The neighboring 0x0021246D
// caller invokes this body at +0x48B. The handle interpretation follows the
// target call and AudioManager's established removeAudioEvent slot; the owning
// class identity remains address-derived.
#include <vector>

typedef unsigned int AudioHandle;

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
	virtual void _pad25() = 0;
	virtual void _pad26() = 0;
	virtual void removeAudioEvent(AudioHandle handle) = 0;
};

extern AudioManager *TheAudio;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva0021237E
{
	char m_pad[0x2CC];

public:
	void rva0021237E();
	void rva002123BE();
};

void Rva0021237E::rva0021237E()
{
	_STL::vector<void *> *eventHandles = (_STL::vector<void *> *)((char *)this + 0x2CC);
	unsigned int i;
	for (i = 0; i < (unsigned int)(eventHandles->end() - eventHandles->begin()); ++i)
	{
		_ReadWriteBarrier();
		TheAudio->removeAudioEvent((AudioHandle)(unsigned int)eventHandles->begin()[i]);
	}
	eventHandles->erase(eventHandles->begin(), eventHandles->end());
}

// Native 6123BE..61246D (175B); WB B5EDA0 confirms ordered update calls.
// +218 is a pointer-key hash table. The WindowVideoManager specialization
// is the existing byte-and-ABI twin at 427195/41E832; it does not establish
// the target map's original key/value class names. Values dispatch slot0C.
#include <hash_map>
class GameWindow;
class WindowVideo;
class WindowVideoManager { public: struct hashConstGameWindowPtr { unsigned int operator()(const GameWindow *p) const { return (unsigned int)p; } }; };
typedef _STL::hash_map<const GameWindow*,WindowVideo*,WindowVideoManager::hashConstGameWindowPtr,_STL::equal_to<const GameWindow*> > UpdateMapView;
struct UpdateSlot21123 { virtual void v00();virtual void v04();virtual void v08();virtual void v0C(); };
struct Rva00211494 { void rva00211494(); };
struct Rva002112A9 { void rva002112A9(); };
struct Rva003EEAB7 { void rva003EEAB7(); };
class LivingWorldEyeTower { friend struct Rva0021237E; void updateState(); };
struct Rva002B5073 { bool rva002B5073(int); };
class LivingWorldLogic; extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002D3627Host; extern Rva002D3627Host *g_00DFEF18; extern Rva002D3627Host *TheRva002D3627Host;
struct SingletonView21123 { char pad14[0x14];int mode; };
struct RadarWindowOverrideSource {
 virtual void v00();virtual void v04();virtual void v08();virtual void v0C();virtual void v10();virtual void v14();virtual void v18();virtual void v1C();virtual void v20();virtual void v24();virtual void v28();
 bool rva002D35E6() const;
};
struct Mouse { void _bfme_setEngineVisibility(bool); }; extern Mouse *TheMouse;
struct UpdateReceiverView21123 {
 char pad[0x218];
 UpdateMapView map218;
 char gap[(0x268-0x218)-sizeof(UpdateMapView)];
 Rva003EEAB7 *object268;
 char pad26C[0x2C0-0x26C];
 bool hidden2C0;
 char pad2C1[3];
 LivingWorldEyeTower *tower2C4;

};
void Rva0021237E::rva002123BE()
{
 UpdateReceiverView21123 *view=(UpdateReceiverView21123*)this;
 ((Rva00211494*)this)->rva00211494();
 ((Rva002112A9*)this)->rva002112A9();
 if(view->object268) view->object268->rva003EEAB7();
 if(view->tower2C4) view->tower2C4->updateState();
 for(UpdateMapView::iterator it=view->map218.begin();it!=view->map218.end();++it)
  ((UpdateSlot21123*)it->second)->v0C();
 if(!view->hidden2C0 && ((SingletonView21123*)g_00DFEF18)->mode==1 && ((RadarWindowOverrideSource*)TheRva002D3627Host)->rva002D35E6() && !((Rva002B5073*)TheLivingWorldLogic)->rva002B5073(8) && TheMouse)
  TheMouse->_bfme_setEngineVisibility(true);
 ((RadarWindowOverrideSource*)TheRva002D3627Host)->v28();
}
