// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Ghidra 00174BA6..00174C17, 113B, RET0. The existing caller 001173F0
// establishes the DF6F94 receiver identity and its address-derived method.
// Retail compares three pointer ranges at +0/+4, +C/+10, +18/+1C, calls
// each range worker, then invalidates textures and clears both D3D shaders.
// Range-worker original names and element types are not established.
struct IDirect3DDevice8;
class Rva00DF6F94GapFillerContext;
class DX8Wrapper
{
    friend class Rva00DF6F94GapFillerContext;
protected:
    static IDirect3DDevice8 *D3DDevice;
};
struct DX8WrapperStageHelper
{
    static void Rva0011CC60InvalidateTextureStages();
};
void Rva00125430(bool enable);
extern unsigned int number_of_DX8_calls;
class Rva00174A57
{
public:
    void rva00174A57();
};
class Rva00DF6F94GapFillerContext
{
public:
    void rva174ba6();
    void rva001748B3();
    void rva001748E8();
private:
    void *first0, *last0, *limit0;
    void *first1, *last1, *limit1;
    void *first2, *last2, *limit2;
};
void Rva00DF6F94GapFillerContext::rva174ba6()
{
    if (first0 != last0 || first1 != last1 || first2 != last2)
    {
        Rva00125430(true);
        rva001748B3();
        rva001748E8();
        reinterpret_cast<Rva00174A57 *>(this)->rva00174A57();
        Rva00125430(false);
        DX8WrapperStageHelper::Rva0011CC60InvalidateTextureStages();
        typedef long (__stdcall *ClearShader)(IDirect3DDevice8 *, void *);
        IDirect3DDevice8 *device = DX8Wrapper::D3DDevice;
        reinterpret_cast<ClearShader>((*reinterpret_cast<void ***>(device))[0x170/4])(device, 0);
        ++number_of_DX8_calls;
        device = DX8Wrapper::D3DDevice;
        reinterpret_cast<ClearShader>((*reinterpret_cast<void ***>(device))[0x1AC/4])(device, 0);
        ++number_of_DX8_calls;
    }
}
