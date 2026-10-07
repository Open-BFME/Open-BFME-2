// cl: /DNDEBUG /MD /EHsc /Ireference/shims/moduledata
// ??1Rva003FAFB9@@UAE@XZ @0x003FAFB9 82B chain from 0x003FAC3F
// Dtor: stores 0x00C37A08, calls rowed rva003FAC3F, holder Release_Ref at +0x14,
// StringBase releaseBuffer at +4, restores 0x00BBB554. Evidence: EH prolog,
// states 2/1/0, Release_Ref row, StringBase row, base BBB554.
#include "Common/Snapshot.h"
class Rva003FAC3F {
public:
    void rva003FAC3F();
};
class OpaqueRefCounted {
public:
    void Release_Ref();
};
struct RvaHolder14 {
    OpaqueRefCounted *m_ptr;
    ~RvaHolder14() { if (m_ptr != 0) m_ptr->Release_Ref(); }
};
template <typename T> class StringBase {
    void releaseBuffer();
public:
    ~StringBase() { releaseBuffer(); }
private:
    char m_pad[16];
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

struct Rva003FADB5Version {
    unsigned char m_version;
    unsigned char m_currentVersion;
};

class Xfer {
public:
    virtual ~Xfer();
    virtual bool IsLoading() const;
    virtual void slot02(); virtual void slot03(); virtual void slot04();
    virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09();
    virtual Xfer &xferVersion(Rva003FADB5Version *version);
    virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14();
    virtual void slot15(); virtual void slot16(); virtual void slot17();
    virtual void slot18(); virtual void slot19(); virtual void slot20();
    virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void slot24(); virtual void slot25(); virtual void slot26();
    virtual void slot27(); virtual void slot28(); virtual void slot29();
    virtual void slot30(); virtual void slot31(); virtual void slot32();
    virtual void slot33(); virtual void slot34(); virtual void slot35();
    virtual Xfer &xferByte(unsigned char *value);
};

class AudioManager {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual void slot03(); virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07(); virtual void slot08();
    virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14();
    virtual void slot15(); virtual void slot16(); virtual void slot17();
    virtual void slot18(); virtual void slot19(); virtual void slot20();
    virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void slot24(); virtual void slot25(); virtual void slot26();
    virtual void slot27(); virtual void slot28(); virtual void slot29();
    virtual void slot30(); virtual void slot31(); virtual void slot32();
    virtual void slot33(); virtual void slot34(); virtual void slot35();
    virtual void slot36(); virtual void slot37(); virtual void slot38();
    virtual void slot39();
    virtual unsigned int slot40();
    virtual void slot41(); virtual void slot42(); virtual void slot43();
    virtual void slot44(); virtual void slot45(); virtual void slot46();
    virtual void slot47(); virtual void slot48(); virtual void slot49();
    virtual void slot50(); virtual void slot51(); virtual void slot52();
    virtual void slot53(); virtual void slot54(); virtual void slot55();
    virtual void slot56(); virtual void slot57(); virtual void slot58();
    virtual void slot59(); virtual void slot60(); virtual void slot61();
    virtual void slot62(); virtual void slot63(); virtual void slot64();
    virtual void slot65(); virtual void slot66(); virtual void slot67();
    virtual void slot68(); virtual void slot69(); virtual void slot70();
    virtual void slot71(); virtual void slot72(); virtual void slot73();
    virtual void slot74(); virtual void slot75(); virtual void slot76();
    virtual void slot77(); virtual void slot78(); virtual void slot79();
    virtual void slot80(); virtual void slot81(); virtual void slot82();
    virtual void slot83(); virtual void slot84(); virtual void slot85();
    virtual void slot86(); virtual void slot87();
    virtual void xferAudioEvent(Xfer *xfer, unsigned int *event);
};
extern AudioManager *g_00DFE6E8;

class Rva003FAFB9 : public Snapshot {
public:
    virtual ~Rva003FAFB9();
protected:
    virtual void xfer(Xfer *xfer);
private:
    StringBase<char> m_str04;
    RvaHolder14 m_14;
    unsigned char pad18[0x14];
    unsigned int m_2c;
    unsigned char m_30;
    unsigned char m_31;
    unsigned char m_32;
};
Rva003FAFB9::~Rva003FAFB9()
{
    ((Rva003FAC3F *)this)->rva003FAC3F();
}

// ?xfer@Rva003FAFB9@@MAEXPAVXfer@@@Z @0x003FADB5 179B
// The matched copy constructor and destructor establish this object's 0x2c
// event index and trailing bytes. The body serializes those target-observed
// fields through Xfer, calls the rowed 0x003FAC3F helper on this, and uses
// TheAudio at 0x00DFE6E8. Slot indices and argument shapes below follow the
// retail indirect calls; their AudioManager method names remain opaque.
void Rva003FAFB9::xfer(Xfer *xfer)
{
    Rva003FADB5Version version = {1, 1};
    xfer->xferVersion(&version);
    if (xfer->IsLoading())
        ((Rva003FAC3F *)this)->rva003FAC3F();

    g_00DFE6E8->xferAudioEvent(xfer, &m_2c);
    xfer->xferByte(&m_30);
    xfer->xferByte(&m_31);
    xfer->xferByte(&m_32);

    unsigned char emitIndex = (unsigned char)(m_2c < 5 ? 0 : 1);
    xfer->xferByte(&emitIndex);
    if (xfer->IsLoading() && emitIndex != 0 && m_2c < 5)
        m_2c = g_00DFE6E8->slot40();
}
