// cl: /O1 /G7 /DNDEBUG /MD /EHsc
// WB00ED2460 names ObjectFilter::isForbidden and218-bit KindOfType test.
// Native00361817..003618B9 RET4 is162B including lazy default-record scope.
// The existing148-byte record providers and pool index/stride establish the
// lifetime; the forbidden mask is the28-byte field64, copied through4543D.
// BFME1 ObjectFilterResolveNames.cpp is the record/collection semantic lead.
enum KindOfType { RVA_KIND_ZERO=0 };
class BfmeFixedStorage0004543D {
public:
    __declspec(nothrow) BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &);
    unsigned char bytes[28];
};
class Rva00360F55 {
public:
    Rva00360F55(); ~Rva00360F55();
    unsigned char vectors[0x48];
    BfmeFixedStorage0004543D first,second;
    int value80,value84; unsigned char flag88,pad89[3]; int useCount,word90;
};
extern unsigned char *g_validityBegin;
extern unsigned char *g_validityEnd;
static __forceinline int validityCount() { return (g_validityEnd-g_validityBegin)/static_cast<int>(sizeof(Rva00360F55)); }
int Rva00361790(Rva00360F55 *);
class ObjectFilter {
public:
    bool isForbidden(KindOfType);
    int index;
};
bool ObjectFilter::isForbidden(KindOfType kind)
{
    if (index>=validityCount()) return true;
    if (index==-1) {
        index=Rva00361790(&Rva00360F55());
    }
    BfmeFixedStorage0004543D forbidden(reinterpret_cast<Rva00360F55 *>(g_validityBegin)[index].second);
    unsigned bit=static_cast<unsigned>(kind);
    return (reinterpret_cast<const unsigned *>(forbidden.bytes)[bit>>5]&(1U<<(bit&31)))!=0;
}
