// cl: /O1 /G7 /arch:SSE /MD /EHs /DNDEBUG /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?rva0010BE72@W3DProjectedShadowManager@@UAEXXZ @ 0x0010BE72 499B, ret
//
// Slot 1 of the projected-shadow manager vtable 0x007CF9C4 (see
// Rva0010C785Lifecycle.cpp); nothing else reaches it. Once per call it walks
// the decal list (+0x08) and then the shadow list (+0x04). Timed decals (type
// 0x400 or 0x800) past their end frame (+0x3C) are collected and released
// through Shadow vtable slot 2; the rest have their opacity faded in and out
// against the client frame using the frame and opacity values at
// +0x38 .. +0x54, through the rowed Shadow::setOpacity (0x003308F6).
//
// Donor: Open-BFME-1 W3DProjectedShadowManagerRva007B4620.cpp (BFME 1 retail
// 0x007B4620, slot 1 of that game's manager vtable), the same walk with the
// same field offsets. Target deltas read from retail: the projected shadow's
// list link sits at +0x114 (BFME 1: +0xD4), and the fade value rounds
// through the dllimport ceil (slot 0x00BBA578). The method name is
// address-derived; neither image names the slot. Each fade rounds the
// lerp through the <math.h> float ceil overload (ceil(float) -> ceilf ->
// the dllimport ceil): those two inline levels give retail's x87 pop order
// around the double argument store. The list's base constructor, destructor,
// clear and insert are the ICF-folded STLport pointer-list bodies, pinned
// with this unit as their fold proof. Those bodies free nodes with a direct
// call to _free (0x00030830), as /D_CRTIMP= gives the other units proving
// these folds, while ceil stays imported, so _CRTIMP is emptied only after
// <math.h>.

#include <math.h>
#undef _CRTIMP
#define _CRTIMP
#include <list>
// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper
// (retail keeps one _List_iterator_base::operator!=; BfmeAptScreenLanLobbyOnInitGadget.cpp pattern).
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#include "../../../../../GameEngine/Include/GameClient/GameClientClass.h"
extern GameClient *TheGameClient;

class Shadow
{
public:
	struct ShadowTypeInfo;
	void setOpacity(int value);
	virtual void vslot00(void);
	virtual void vslot04(void);
	virtual void release(void);
	char m_pad04[0x30];
	unsigned int m_type; // +0x34
	unsigned int m_value38; // +0x38
	unsigned int m_value3C; // +0x3C
	unsigned int m_value40; // +0x40
	unsigned int m_value44; // +0x44
	unsigned int m_value48; // +0x48
	unsigned int m_value4C; // +0x4C
	unsigned int m_value50; // +0x50
	unsigned int m_value54; // +0x54
};

class W3DProjectedShadow : public Shadow
{
public:
	unsigned char m_pad58[0x114 - 0x58];
	W3DProjectedShadow *m_next;		// +0x114
};

class W3DProjectedShadowManager
{
public:
	virtual ~W3DProjectedShadowManager();
	virtual void rva0010BE72(void);

private:
	W3DProjectedShadow *m_shadowList;	// +0x04
	W3DProjectedShadow *m_decalList;	// +0x08
};

void W3DProjectedShadowManager::rva0010BE72(void)
{
	_STL::list<W3DProjectedShadow *> expired;
	UnsignedInt frame = TheGameClient->getFrame();

	for (Int i = 0; i <= 1; ++i)
	{
		for (W3DProjectedShadow *shadow = i ? m_shadowList : m_decalList; shadow; shadow = shadow->m_next)
		{
			if (shadow->m_type == 0x400 || shadow->m_type == 0x800)
			{
				if (shadow->m_value3C <= frame)
					expired.push_back(shadow);
				else
				{
					UnsignedInt fadeInStartFrame = shadow->m_value38;
					UnsignedInt opacityStart = shadow->m_value40;
					UnsignedInt fadeInEndFrame = shadow->m_value44;
					UnsignedInt peakOpacity = shadow->m_value48;
					UnsignedInt fadeOutStartFrame = shadow->m_value4C;
					UnsignedInt fadeOutEndFrame = shadow->m_value50;
					UnsignedInt opacityEnd = shadow->m_value54;
					if (frame < fadeInStartFrame)
						shadow->setOpacity(0);
					else if (frame < fadeInEndFrame)
					{
						double from = opacityStart;
						shadow->setOpacity(fast_float2long_round(ceil((float)(from + (Real)(frame - fadeInStartFrame) / (Real)(fadeInEndFrame - fadeInStartFrame) * (peakOpacity - from)))));
					}
					else if (frame < fadeOutStartFrame)
						shadow->setOpacity(peakOpacity);
					else if (frame < fadeOutEndFrame)
					{
						double from = peakOpacity;
						shadow->setOpacity(fast_float2long_round(ceil((float)(from + (Real)(frame - fadeOutStartFrame) / (Real)(fadeOutEndFrame - fadeOutStartFrame) * (opacityEnd - from)))));
					}
					else
						shadow->setOpacity(opacityEnd);
				}
			}
		}
	}

	for (_STL::list<W3DProjectedShadow *>::iterator it = expired.begin(); it != expired.end(); ++it)
		(*it)->release();

	expired.clear();
}
