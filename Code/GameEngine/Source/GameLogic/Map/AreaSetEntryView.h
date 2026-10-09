#pragma once
// Target: constructors 30C95C (34B), insertion callers 30C61B/30CE66
// (135B each), and RiverAreasDataChunkParser 30C6C8 show an 8-byte entry
// {int id; retained pointer}. References count at object+4 and release via
// the rowed fastcall 7DEEF. The constructor receives its four-byte reference
// by value: each insertion caller constructs a retained stack argument,
// the constructor retains its member then destroys that incoming reference.
// WorldBuilder 5461E0/54A8A0 name AreaSet<RiverArea/StandingWaveArea>::insert.
// These names describe storage and ownership only; the original reference
// template and entry spelling are unidentified. All views remain 32-bit.
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct AreaRetainedObjectView { void *vptr; int references; };
struct AreaRefValueView {
    AreaRetainedObjectView *pointer;
    AreaRefValueView(const AreaRefValueView &other) : pointer(other.pointer) {
        if (pointer) ++pointer->references;
    }
    ~AreaRefValueView() {
        if (pointer) ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C *>(pointer));
    }
};
class Rva0030C95C {
public:
    int m_value;
    AreaRefValueView m_target;
    Rva0030C95C(int, AreaRefValueView);
};
