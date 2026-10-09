// cl: /O2 /G6 /arch:SSE /MD
// ?rva006FA7E0@Rva006FB860@@QAEX_N0H@Z retail 0x006FA7E0..0x006FAA20 (576 bytes)
// thiscall ret 0xC. Focus/press state transition on the Apt input object
// shared with 0x006FB860/0x006FB910/0x006FAA20 (Rva006FB910Cluster.cpp):
// +0x44 current value and the +0x60/+0x64/+0x68 AptValue slots are tested
// with AptValue::isUndefined (0x006DC010) and dispatched through the checked
// CIH cast 0x006DCF60 to 0x006E2010 with event masks 0x400..0x10000; the
// coordinate hit test is 0x006F9FC0. Cleared slots take gpUndefinedValue.
// Only caller: 0x006FB120 (passes the two flags and the packed position).
// Owner class and method name remain address-derived. Bank
// reverse/attempts/0x006fa7e0.cpp was the starting point; region flags
// /O2 /G6 /arch:SSE make it exact.

class AptCIH;
class Rva006E1E30;

class BfmeAptValue006DCD20
{
public:
    bool isUndefined() const;                         // rowed, 0x006DC010
    BfmeAptValue006DCD20 *rva006DCF60(bool bUndefOK); // rowed, 0x006DCF60
};

class Rva006F9FC0
{
public:
    bool rva006F9FC0(Rva006E1E30 *object, int unused); // rowed, 0x006F9FC0
};

class Rva006E2010Dispatcher
{
public:
    void dispatch(int eventMask, int value, int enabled); // pinned, 0x006E2010
};

class AptValue;
extern AptValue *gpUndefinedValue; // 0x00E18078

class Rva006FB860
{
public:
    unsigned char _unread[0x44];
    BfmeAptValue006DCD20 *mValue;     // +0x44
    unsigned char _unread48[0x18];
    BfmeAptValue006DCD20 *m60;
    BfmeAptValue006DCD20 *m64;
    BfmeAptValue006DCD20 *m68;
    void rva006FA7E0(bool first, bool enabled, int value);
};

void Rva006FB860::rva006FA7E0(bool first, bool enabled, int value)
{
    if (enabled) {
        if (m60->isUndefined())
            return;
        if (!mValue->isUndefined()) {
            if (mValue == m60) {
                ((Rva006E2010Dispatcher *)m60->rva006DCF60(false))
                    ->dispatch(0x800, value, 1);
            } else {
                ((Rva006E2010Dispatcher *)m60->rva006DCF60(false))
                    ->dispatch(0x1000, value, 1);
            }
        } else {
            if (((Rva006F9FC0 *)this)->rva006F9FC0(
                    (Rva006E1E30 *)m60->rva006DCF60(false), value) && m68 == m60) {
                ((Rva006E2010Dispatcher *)m60->rva006DCF60(false))
                    ->dispatch(0x800, value, 1);
            } else {
                ((Rva006E2010Dispatcher *)m60->rva006DCF60(false))
                    ->dispatch(0x1000, value, 1);
            }
        }
        m60 = (BfmeAptValue006DCD20 *)gpUndefinedValue;
        return;
    }

    if (first) {
        if (m68->isUndefined())
            return;
        ((Rva006E2010Dispatcher *)m68->rva006DCF60(false))
            ->dispatch(0x400, value, 1);
        m60 = m68;
        return;
    }

    if (!m60->isUndefined()) {
        bool inside = ((Rva006F9FC0 *)this)->rva006F9FC0(
            (Rva006E1E30 *)m60->rva006DCF60(false), value);
        if (!m64->isUndefined() && !inside) {
            ((Rva006E2010Dispatcher *)m60->rva006DCF60(false))
                ->dispatch(0x10000, value, 1);
            m64 = (BfmeAptValue006DCD20 *)gpUndefinedValue;
            return;
        }
        if (m64->isUndefined() && inside) {
            ((Rva006E2010Dispatcher *)m60->rva006DCF60(false))
                ->dispatch(0x8000, value, 1);
            m64 = m60;
        }
    } else {
        if (!m68->isUndefined() && m68 != m64) {
            if (!m64->isUndefined() && m64 != m60) {
                ((Rva006E2010Dispatcher *)m64->rva006DCF60(false))
                    ->dispatch(0x4000, value, 1);
            }
            m64 = m68;
            ((Rva006E2010Dispatcher *)m68->rva006DCF60(false))
                ->dispatch(0x2000, value, 1);
        } else {
            if (m64->isUndefined() || m68 == m64 || !m60->isUndefined())
                return;
            if (((Rva006F9FC0 *)this)->rva006F9FC0(
                    (Rva006E1E30 *)m64->rva006DCF60(false), value))
                return;
            ((Rva006E2010Dispatcher *)m64->rva006DCF60(false))
                ->dispatch(0x4000, value, 1);
            m64 = (BfmeAptValue006DCD20 *)gpUndefinedValue;
            return;
        }
    }
}
