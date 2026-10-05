// cl: /O1 /DNDEBUG /MD
// ?rva00514B66@Rva00514B66@@QAEEXZ @0x00514B66 39B unlock lane bool guard via BfmeThingTTD.
// Evidence: reads ecx+0x298 and 0x29a then add 0x290 call rowed rva005B7032 0x005B7032; callers 0x00515FBD 0x005160F0.
class BfmeThingTTD
{
public:
    bool rva005B7032();
    const unsigned short *m_name;
    const unsigned short *m_imageFileName;
    bool m_initialized;
    bool m_enabled;
    bool m_added;
    char m_pad0b;
    long m_comResult;
    void *m_profile;
};

class Rva00514B66
{
public:
    unsigned char rva00514B66();
private:
    char m_pad[0x290];
    BfmeThingTTD m_ttd;
};

unsigned char Rva00514B66::rva00514B66()
{
    return m_ttd.m_initialized && m_ttd.m_added && !m_ttd.rva005B7032();
}
