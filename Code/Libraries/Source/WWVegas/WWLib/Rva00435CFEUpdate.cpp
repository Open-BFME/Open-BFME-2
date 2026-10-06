// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /O1 /arch:SSE /G7
// ?rva00435CFE@Rva00435CFE@@QAEXG@Z at 0x00435CFE (24 bytes). The retail
// body sign-extends its 16-bit argument, calls the rowed Hook with that value
// twice, and stores the result at this+4. The class and field meaning remain
// address-based; adjacent STL tree-hint units are context only.
int Rva004353E8Hook(int, int);

class Rva00435CFE
{
public:
    void rva00435CFE(unsigned short value);

private:
    int m_unknown0;
    int m_value;
};

void Rva00435CFE::rva00435CFE(unsigned short value)
{
    int widened = static_cast<short>(value);
    m_value = Rva004353E8Hook(widened, widened);
}
