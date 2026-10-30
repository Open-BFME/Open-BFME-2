// cl: /DNDEBUG /MD
// ?rva00514B66@Rva00514B66@@QAEEXZ @0x00514B66 39B unlock lane bool guard via BfmeThingTTD.
// Evidence: reads ecx+0x298 and 0x29a then add 0x290 call rowed rva005B7032 0x005B7032; callers 0x00515FBD 0x005160F0.
class BfmeThingTTD
{
public:
	BfmeThingTTD();
	~BfmeThingTTD();
	bool rva005B7032();
	const unsigned short *m_name; // +0x00
	const unsigned short *m_imageFileName; // +0x04
	bool m_initialized; // +0x08
	bool m_enabled; // +0x09
	bool m_added; // +0x0A
	char m_pad0B[0x1];
	long m_comResult; // +0x0C
	void *m_profile; // +0x10
};

class Rva00514B66
{
public:
	unsigned char rva00514B66();
	char m_pad00[0x290];
private:
	BfmeThingTTD m_ttd; // +0x290
};

unsigned char Rva00514B66::rva00514B66()
{
    return m_ttd.m_initialized && m_ttd.m_added && !m_ttd.rva005B7032();
}
