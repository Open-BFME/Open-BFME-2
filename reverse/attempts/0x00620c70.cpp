// ?contains@BfmeUnsignedKeyTree620C70@@QAE_NI@Z
// partial score=0.897 date=2026-10-05
// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// BFME1 clean whole-donor lead: Rva00241F10MemberAttackTarget.cpp at
// 6583b3c1ff21db4a561285717028fdafc780b7db, final /O2 override.
// Target establishes unsigned-key tree lookup via 4D7546 ->357180;
// donor TargetMap/HordeContain names and set<int> payload are unproven.
// This view records only native receiver header+0 and hidden-return iterator ABI.
class BfmeUnsignedKeyTree620C70 {
public:
    struct Iterator {
        void *node;
        Iterator() {}
        Iterator(const Iterator &other) : node(other.node) {}
    };
    Iterator lookup(const unsigned int &key);
    void *header;
    bool contains(unsigned int key);
};
bool BfmeUnsignedKeyTree620C70::contains(unsigned int key) {
    Iterator found=lookup(key);
    return found.node!=header;
}
