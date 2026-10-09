// cl: /O1 /DNDEBUG /MD
// WB B76309 names the subclass mask BitFlags<7,enum FactionType>; native
// constructor21E793 initializes its one-word storage at68 through3B31AD.
// The target default mask constructor clears four bytes through memset;
// every byte and relocation must equal the existing BitFlags<11> owner.
enum FactionType { FACTION_UNKNOWN = -1 };
extern "C" void *memset(void *, int, unsigned int);
template<int NUM_BITS, class BitTag> class BitFlags {
public:
    BitFlags() throw();
private:
    unsigned words[(NUM_BITS+31)/32];
};
template<int NUM_BITS, class BitTag>
BitFlags<NUM_BITS,BitTag>::BitFlags() throw() { memset(words,0,sizeof(words)); }
template BitFlags<7,FactionType>::BitFlags();
