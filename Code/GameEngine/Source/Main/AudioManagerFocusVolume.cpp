// cl: /Ireference/shims/bfmelist /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?LookupFocusChannelVolume@@YAMH@Z @0x0035D20C 166B.
// Per-channel focus volume: start from 1.0f, gate on the WM_ACTIVATE focus
// singleton at 0x00DFDC14 (TheTransitionHandler, defined in WinMain.cpp; not
// TheAudio, which is 0x00DFE6E8), guarded list
// copy via GameWindowTransitionsHandler::rva001DC57C then multiply by each
// matching factor.
// Evidence: pin LookupFocusChannelVolume, caller 0x0035D2F7 regainFocus,
// callee 0x001DC57C rowed, float 1.0f via g_Va00BBB8D8.
#include <list>

// Retain bfmealloc's native null-checked free and proxy forwarding inline.
// The matched bodies already inline these STLport ownership wrappers.
namespace _STL {
template<> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(pointer p, size_type n) const
{ if (p != 0) ::free((void*)p); }
template<> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int>*, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int>* p, size_t n)
{ __stl_alloc_rebind(static_cast<_Base&>(*this), (_List_node<int>*)0).deallocate(p, n); }
}

class GameWindowTransitionsHandler;
extern GameWindowTransitionsHandler *TheTransitionHandler;
// Matched DIR32 sites place this shared default at VA 0x00BBB8D8; retail
// stores 00 00 80 3F (1.0f) there.
float g_Va00BBB8D8 = 1.0f;

class GameWindowTransitionsHandler
{
public:
	void rva001DC57C(_STL::list<int> *dest);
};

class FocusVolume
{
public:
	char m_pad00[0x18];
	int m_channelMask;
	char m_pad1C[4];
	float m_factor;
};

class FocusResolver
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual FocusVolume *GetVolume();
};

struct FocusHandle
{
	char m_pad[0x10];
	FocusResolver *m_resolver;
};

float LookupFocusChannelVolume(int channel)
{
	float volume = g_Va00BBB8D8;
	int mask = 1 << channel;
	if (TheTransitionHandler == 0)
		return volume;
	_STL::list<int> ids;
	TheTransitionHandler->rva001DC57C(&ids);
	for (_STL::list<int>::iterator it = ids.begin(); it._M_node != ids.end()._M_node; ++it) {
		FocusHandle *h = (FocusHandle *)(*it);
		if (h == 0)
			continue;
		if (h->m_resolver == 0)
			continue;
		FocusVolume *v = h->m_resolver->GetVolume();
		if (v == 0)
			continue;
		if ((v->m_channelMask & mask) == 0)
			continue;
		volume *= v->m_factor;
	}
	return volume;
}
