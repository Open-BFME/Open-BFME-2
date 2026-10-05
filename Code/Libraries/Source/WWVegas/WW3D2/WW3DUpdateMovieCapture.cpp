// cl: /O2 /G7 /DNDEBUG /MD
// Semantic donor: ZH ww3d.cpp via BFME1 6583b3c1ff21db4a561285717028fdafc780b7db.
// Native117AD0..117BAB (219B); Begin_Render118170 calls this capture helper.
// Donor carries the WW3D movie-copy purpose and class spellings. Native calls
// prove GetBuffer-first ordering and no trailing Grab; native loop proves
// flipped RGB rows, hoisted row offsets, and four-byte source pixels.
// Movie DEC3DC and g_WW3D_Hwnd DEC408 use existing global providers.
// Target gets FrameGrab buffer first, uses D3D9 surface slots12/13,
// and releases the surface after copying RGB bytes with a flipped row order.
typedef unsigned int UInt;
typedef long HRESULT;
struct RECT { long left,top,right,bottom; };
struct D3DSURFACE_DESC { char bytes[32]; };
struct D3DLOCKED_RECT { int Pitch; void *pBits; };
class IDirect3DSurface9 {
public:
    virtual void __stdcall s0(); virtual void __stdcall s1();
    virtual UInt __stdcall Release();
    virtual void __stdcall s3(); virtual void __stdcall s4();
    virtual void __stdcall s5(); virtual void __stdcall s6();
    virtual void __stdcall s7(); virtual void __stdcall s8();
    virtual void __stdcall s9(); virtual void __stdcall s10();
    virtual void __stdcall s11();
    virtual HRESULT __stdcall GetDesc(D3DSURFACE_DESC *);
    virtual HRESULT __stdcall LockRect(D3DLOCKED_RECT *,const RECT *,UInt);
};
class DX8Wrapper { public: static IDirect3DSurface9 *_Get_DX8_Front_Buffer(); };
class FrameGrabClass { public: long *GetBuffer(); };
extern "C" __declspec(dllimport) int __stdcall GetWindowRect(void *,RECT *);
void Log_DX8_ErrorCode(UInt);
extern void *g_WW3D_Hwnd;
class WW3D { public: static FrameGrabClass *Movie; static void Update_Movie_Capture(); };
void WW3D::Update_Movie_Capture()
{
    char *image=(char *)Movie->GetBuffer();
    IDirect3DSurface9 *fb=DX8Wrapper::_Get_DX8_Front_Buffer();
    D3DSURFACE_DESC desc;
    fb->GetDesc(&desc);
    RECT bounds;
    GetWindowRect(g_WW3D_Hwnd,&bounds);
    D3DLOCKED_RECT lrect;
    HRESULT hr=fb->LockRect(&lrect,&bounds,0x10);
    if (hr) Log_DX8_ErrorCode((UInt)hr);
    UInt x,y,index,index2,width,height;
    width=bounds.right-bounds.left;
    height=bounds.bottom-bounds.top;
    for (y=0;y<height;y++) {
        index=3*((height-y-1)*width);
        index2=y*lrect.Pitch;
        for (x=0;x<width;x++) {
            image[index]=*((char *)lrect.pBits+index2);
            image[index+1]=*((char *)lrect.pBits+index2+1);
            image[index+2]=*((char *)lrect.pBits+index2+2);
            index+=3;
            index2+=4;
        }
    }
    fb->Release();
}

