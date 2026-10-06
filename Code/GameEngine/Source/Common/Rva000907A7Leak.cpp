// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva000907A7@Rva009111B@@QAEXXZ @0x000907A7 16B
// Gap between ConstIntGetters 0x000907A1 and Disp8FloatChase 0x000910C0.
// Calls rowed StringBase<G> debugIgnoreLeaks 0x0069E440 twice on same this
// with second tail-jumped. Caller is dtor 0x0009111B.
#include "unicode_string.h"

class Rva009111B
{
public:
	void rva000907A7();
};

void Rva009111B::rva000907A7()
{
	((StringBase<unsigned short> *)this)->debugIgnoreLeaks();
	((StringBase<unsigned short> *)this)->debugIgnoreLeaks();
}
