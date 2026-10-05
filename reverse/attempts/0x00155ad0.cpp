// ?visit@Rva00155AD0@@QAEXXZ
// partial score=0.92 date=2026-10-06
// cl: /O1 /G7 /MD
struct Rva00155AD0Item {void visit();};
struct Rva00155AD0Entry {Rva00155AD0Item*item;unsigned word;};
void __cdecl Rva00118810Begin();void __cdecl Rva001188A0End();
class Rva00155AD0 {char prefix[0x38];Rva00155AD0Entry*entries;char gap[8];int count;public:void prepare();void visit();};
void Rva00155AD0::visit() {int i=0;prepare();Rva00118810Begin();for(;i<count;++i)entries[i].item->visit();Rva001188A0End();}
