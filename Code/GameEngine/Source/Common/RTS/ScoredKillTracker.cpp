// cl: /ICode/Libraries/Include /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// WB14162D0 names ScoredKillTracker::DoXfer and the tracked-kills count.
// Native55AA68..55AB41/217 proves the scalar offsets and Xfer slots, the
// four-byte ObjectFilter index at+8, and list<int> at+18 followed by count1C.
// Existing friend_update proves list elements are frame values and +4 is
// their lifetime window; the purpose of the scalar at+C remains unknown.
// The version is1/1. CRC returns before transfer; load rebuilds the list,
// save walks to a captured end iterator. No reference source identity is
// claimed: WB and retail supply this reconstruction. ObjectFilter::DoXfer
// is the independently rowed362255 provider; list clear/push are23DAA5/5548F.
#include <list>
#include "Lib/Coord3D.h"
class AsciiString;
// Retail Version stores minimum/current bytes and has an inline constructor;
// that constructor form also reproduces the independent stack homes in DoXfer.
struct TrackerVersion
{
    TrackerVersion(unsigned char min, unsigned char cur) : minimum(min), current(cur) {}
    unsigned char minimum, current;
};
class Xfer{public:virtual~Xfer();virtual bool IsLoading() const;
virtual bool IsStoring() const;
virtual bool IsCRC() const;
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual Xfer &xferVersion(TrackerVersion *);
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual Xfer &xferCoord3D(struct Coord3D *);
virtual void slot25();
virtual void slot26();
virtual Xfer& xferAsciiString(AsciiString*);
virtual void slot28();
virtual void slot29();
virtual Xfer &xferUnsignedInt(unsigned int *);
virtual Xfer& xferInt(int*);
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual Xfer &xferBool(bool *);
};

namespace _STL {
template<>void _List_base<int, allocator<int> >::clear();
template<>void list<int>::push_back(const int&);
}

class ObjectFilter { public: void DoXfer(Xfer *); int m_id; };
class ScoredKillTracker {
public:
    virtual ~ScoredKillTracker();
    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(Xfer *);
private:
    unsigned int m_lifetime;
    ObjectFilter m_filter;
    unsigned int m_value0c;
    void *m_keeper;
    int m_playerIndex;
    _STL::list<int> m_trackedKills;
    int m_trackedKillsCount;
    Coord3D m_position;
};
void ScoredKillTracker::DoXfer(Xfer *xfer) {
    if (xfer->IsCRC()) return;
    TrackerVersion version(1,1);
    xfer->xferVersion(&version);
    xfer->xferUnsignedInt(&m_lifetime);
    m_filter.DoXfer(xfer);
    xfer->xferUnsignedInt(&m_value0c);
    xfer->xferInt(&m_playerIndex);
    xfer->xferInt(&m_trackedKillsCount);
    if (xfer->IsLoading()) {
        m_trackedKills.clear();
        for (int i=0; i<m_trackedKillsCount; ++i) {
            int kill;
            xfer->xferUnsignedInt(reinterpret_cast<unsigned int*>(&kill));
            m_trackedKills.push_back(kill);
        }
    } else {
        _STL::list<int>::iterator end=m_trackedKills.end();
        for (_STL::list<int>::iterator it=m_trackedKills.begin(); it._M_node != end._M_node; ++it) {
            unsigned int kill=*it;
            xfer->xferUnsignedInt(&kill);
        }
    }
    xfer->xferCoord3D(&m_position);
}
