// cl: /O2 /G7 /DNDEBUG /MD
// ZH ww3d.cpp through BFME1 6583b3c1 semantic donor.
// Native116F90 tail-jumps to the rowed DX8 descriptor query120140 (55B);
// native117000 tail-jumps to rowed DX8 resolution query11CDF0 (48B).
// Each is a complete5-byte thunk with the callee's cdecl argument/return ABI.
// WW3D wrapper names are donor-carried; target callee identities are rowed.
class RenderDeviceDescClass;
class WW3D;
class DX8Wrapper {
    friend class WW3D;
protected:
    static const RenderDeviceDescClass &Get_Render_Device_Desc(int);
    static void Get_Device_Resolution(int &,int &,int &,bool &);
};
class WW3D {
public:
    static const RenderDeviceDescClass &Get_Render_Device_Desc(int);
    static void Get_Device_Resolution(int &,int &,int &,bool &);
};
const RenderDeviceDescClass &WW3D::Get_Render_Device_Desc(int index)
{
    return DX8Wrapper::Get_Render_Device_Desc(index);
}
void WW3D::Get_Device_Resolution(int &width,int &height,int &bits,bool &windowed)
{
    DX8Wrapper::Get_Device_Resolution(width,height,bits,windowed);
}
