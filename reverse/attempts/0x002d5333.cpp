// ??1Rva002D5333@@UAE@XZ
// partial score=0.94 date=2026-10-05
// cl: /O1 /Ob2 /EHsc /DNDEBUG /MD
// Ghidra boundary2D5333/72 and rowed deletingwrapper2D579A establish dtor.
// Native string10 releases through verified133B36410; byte15 gates native
// cleanup2D4BA5/54, which invokes unrowed99B2D4531 with globalDFE4CC.
// Model consumed prefix only; original identity and remaining size unknown.
extern "C" const void* const vtbl_00C02A84[];
#pragma comment(linker, "/alternatename:_vtbl_00C02A84=??_7Rva002D3556@@6B@")
class __declspec(novtable) Rva002D5333Base {
public: virtual __forceinline ~Rva002D5333Base(){*(const void**)this=vtbl_00C02A84;}
private: unsigned char unknown[12];
};
template<class T> class StringBase {public: ~StringBase();private: void* data;};
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")
class Rva002D5333 : public Rva002D5333Base {
public: virtual ~Rva002D5333();void cleanup2D4BA5();
private: StringBase<char> str10;unsigned char unknown14;bool done15;
};
Rva002D5333::~Rva002D5333(){if(!done15)cleanup2D4BA5();}
