// cl: /O1 /MD
// ?Rva0033B634Get@@YAPBVImage@@PAVThingTemplate@@PAVRva0028F2F8Host@@@Z @0x0033B634 67B linkbody
// Evidence: LINK 2 files wait via 0x00525CC5; tail-jmp row rva0033B580 ThingTemplateButtonImage; pin rva002197A6 via g_00DFE344 same pattern as Rva0028F2F8; 8 callers; prev next same Thing dir
struct Rva0028F2F8Aux {
	unsigned char m_pad[0x11F];
	unsigned char m_11F;
};
class Rva002197A6Host {
public:
	void *rva002197A6(int v);
};
extern Rva002197A6Host *g_00DFE344;
class Rva0028F2F8Host {
public:
	unsigned char m_pad00[4];
	Rva0028F2F8Aux *m_04;
	unsigned char m_pad08[0x74 - 0x8];
	int m_74;
};
class Image;
class ThingTemplate {
public:
	const Image *rva0033B580();
};
const Image *Rva0033B634Get(ThingTemplate *tmpl, Rva0028F2F8Host *h)
{
	if (tmpl == 0 || h == 0)
		return 0;
	if ((h->m_04->m_11F & 0x40) == 0)
		goto fallback;
	{
		void *r = g_00DFE344->rva002197A6(h->m_74);
		if (r == 0)
			goto fallback;
		void *img = *(void **)((char *)r + 0x13c);
		if (img != 0)
			return (const Image *)img;
	}
fallback:
	return tmpl->rva0033B580();
}
