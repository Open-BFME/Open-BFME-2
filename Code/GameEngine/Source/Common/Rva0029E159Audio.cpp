// cl: /MD /EHsc /DNDEBUG
// WorldBuilder DA7520 names InGameUI::FormationPreviewDecal's constructor
// at InGameUI.cpp:314. The complete native 29E159..29E1EF body initializes
// its four-byte shadow handle using ShadowTypeInfo and manager slot 8.
// The source descriptor is an AsciiString followed by two decal dimensions.
// AudioManager0029E159 below is the existing borrowed manager ABI view;
// consumers cast the canonical projected-shadow singleton to that private view.
typedef int Int;

#include "../../Include/Common/BfmeStringData.h"

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"


// The descriptor is Shadow::ShadowTypeInfo (rowed ctor 0x00079514 and dtor
// 0x000793FA); the type set below (0x20) is its +8 shadow type.
class Shadow
{
public:
	struct ShadowTypeInfo { ShadowTypeInfo(); ~ShadowTypeInfo(); AsciiString m_first; AsciiString m_second; int m_type; float m_floatC; float m_float10; float m_float14; float m_float18; float m_float1C; float m_float20; unsigned char m_byte24; unsigned char m_byte25; unsigned char m_byte26; };
	void setColor(int color);
};

struct Source0029E159
{
public:
	AsciiString m_name; // +0x00
	float m_x; // +0x04
	float m_y; // +0x08
};

class AudioManager0029E159
{
public:
	virtual ~AudioManager0029E159() {}
	virtual void s04() = 0;
	virtual int addDecal(Shadow::ShadowTypeInfo *ev) = 0;
};

// Retail VA 0x00DEC2D4 is owned by W3DProjectedShadowUpdate.cpp.
class ProjectedShadowManager;
extern ProjectedShadowManager *TheProjectedShadowManager;
#include "../../Include/GameClient/InGameUI.h"
class InGameUI::FormationPreviewDecal
{
 int m_handle;
public:
 FormationPreviewDecal(const Source0029E159 &src);
};

InGameUI::FormationPreviewDecal::FormationPreviewDecal(const Source0029E159 &src)
{
	m_handle = 0;
	if (src.m_name.isEmpty())
		return;
	Shadow::ShadowTypeInfo ev;
	ev.m_first = src.m_name;
	ev.m_floatC = src.m_x;
	AudioManager0029E159 *mgr = (AudioManager0029E159 *)TheProjectedShadowManager;
	ev.m_float10 = src.m_y;
	ev.m_byte25 = 0;
	ev.m_byte26 = 1;
	ev.m_type = 0x20;
	ev.m_float14 = 0.0f;
	ev.m_float18 = 0.0f;
	m_handle = mgr->addDecal(&ev);
	return;
}
