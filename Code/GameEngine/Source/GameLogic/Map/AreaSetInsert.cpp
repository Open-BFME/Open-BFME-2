// Native insert135 at 30C61B..30C6A2 and 30CE66..30CEED.
// WB 5461E0/54A8A0 name AreaSet<RiverArea/StandingWaveArea>::insert;
// both update nextID+10 then append {id; retained area} to vector+14,
// and notify the listener list at +0 through its slot+4 callback.
// Native parser30C6C8 supplies the RiverArea receiver; WB supplies the
// StandingWaveArea instantiation lead. Original template/reference names
// remain unasserted: both receivers and ownership types are storage views.
// Reuses the rowed 8-byte vector insert representation; no new aliases.
// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <vector>
#include "AreaSetEntryView.h"
struct Rva00308E2CElement { int a[2]; };
template <> void _STL::vector<Rva00308E2CElement>::push_back(const Rva00308E2CElement &);
class Rva00281A33Listener {
public:
    virtual void unused();
    virtual void notify(void *, int);
};
class Rva00281A33List {
public:
    void forEach(void (Rva00281A33Listener::*)(void *, int), void *, int);
    unsigned char storage[0x10];
};
struct AreaSetInsertStorage {
    Rva00281A33List listeners;
    int nextID;
    _STL::vector<Rva00308E2CElement> entries;
};
class RiverAreaSetView : public AreaSetInsertStorage { public: void insert(int, AreaRefValueView); };
void RiverAreaSetView::insert(int id, AreaRefValueView area) {
    if (id >= nextID) nextID = id + 1;
    entries.push_back(reinterpret_cast<const Rva00308E2CElement &>(Rva0030C95C(id, area)));
    listeners.forEach(&Rva00281A33Listener::notify, this, reinterpret_cast<int>(area.pointer));
}
class StandingWaveAreaSetView : public AreaSetInsertStorage { public: void insert(int, AreaRefValueView); };
void StandingWaveAreaSetView::insert(int id, AreaRefValueView area) {
    if (id >= nextID) nextID = id + 1;
    entries.push_back(reinterpret_cast<const Rva00308E2CElement &>(Rva0030C95C(id, area)));
    listeners.forEach(&Rva00281A33Listener::notify, this, reinterpret_cast<int>(area.pointer));
}

// Native 28343D..2834C4 RET8 shares the existing insertion algorithm and
// all seven call edges. The rowed 283C0F/283C40 WaterSlots callers prove the
// WaterHandleRef by-value ABI and retained WaterHandle at object+4. The
// listener callback is native slot+4 (vcall forwarder5CB260), passed to the
// now rowed two-argument listener walk281A33. No original AreaSet template
// name is asserted: the receiver keeps the existing address-derived name.
// Existing caller-proven WaterHandleRef ABI (Rva00283C0FWaterSlots.cpp).
class WaterHandle { public: virtual void w0(); int m_refs; };
class WaterHandleRef {
public:
    WaterHandleRef(WaterHandle *handle) : m_handle(handle) { if (handle) ++handle->m_refs; }
    WaterHandleRef(const WaterHandleRef &other) : m_handle(other.m_handle) { if (m_handle) ++m_handle->m_refs; }
    ~WaterHandleRef() { if (m_handle) ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C *>(m_handle)); }
private:
    WaterHandle *m_handle;
};
class Rva0028343D : public AreaSetInsertStorage { public: void rva0028343D(int, WaterHandleRef); };
void Rva0028343D::rva0028343D(int id, WaterHandleRef area) {
    if (id >= nextID) nextID = id + 1;
    entries.push_back(reinterpret_cast<const Rva00308E2CElement &>(Rva0030C95C(id, reinterpret_cast<const AreaRefValueView &>(area))));
    listeners.forEach(&Rva00281A33Listener::notify, this, reinterpret_cast<int>(reinterpret_cast<const AreaRefValueView &>(area).pointer));
}
