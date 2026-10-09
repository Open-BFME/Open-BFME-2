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
