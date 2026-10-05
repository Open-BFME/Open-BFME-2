// cl: /O1 /DNDEBUG /MD
//
// ?rva0033B634@@YAPBVImage@@PAVThingTemplate@@PAURva0033B634In@@@Z
// @0x0033B634 67B.
//
// Hero-image fallback: when the +0x74 key resolves through the
// CreateAHeroManager (g_00DFE344) entry scan 0x002197A6 to an entry whose
// +0x13c portrait is set, return it; otherwise tail-jump to the
// ThingTemplate button-image resolver 0x0033B580 (which the rowed
// ThingTemplateButtonImage.cpp names as this caller's fallback). A set
// 0x40 bit at +0x11f of the +0x04 link gates the lookup; a null template
// or input returns null. Callers pass (template, template->m_04) cdecl -
// the four 0x525xxx/0x526xxx UI call sites push exactly those two.
// The manager entry type is carried as CreateAHeroData for fleet
// consistency (MpGameSetupSlots.cpp); only its +0x13c portrait slot is
// read here, so the view is honest about what this body proves.

class Image;

class ThingTemplate
{
public:
	const Image *rva0033B580();
};

struct Rva0033B634In
{
	char m_pad00[4];
	void *m_04; // +0x04 (flag byte at +0x11f)
	char m_pad08[0x74 - 8];
	int m_74; // +0x74 (hero key)
};

class CreateAHeroData
{
public:
	char m_pad00[0x13c];
	const Image *m_portrait; // +0x13c
};

class Rva00219B9E
{
public:
	CreateAHeroData *rva002197A6(int key);
};
extern Rva00219B9E *g_00DFE344;

const Image *rva0033B634(ThingTemplate *tmpl, Rva0033B634In *y)
{
	if (!tmpl || !y)
		return 0;

	void *z = y->m_04;
	if (*(unsigned char *)((char *)z + 0x11f) & 0x40)
	{
		CreateAHeroData *w = g_00DFE344->rva002197A6(y->m_74);
		if (w)
		{
			const Image *v = w->m_portrait;
			if (v)
				return v;
		}
	}
	return tmpl->rva0033B580();
}
