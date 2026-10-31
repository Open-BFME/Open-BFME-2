// cl: /DNDEBUG /MD
// Semantic donor: ZH ww3d.cpp via BFME1 6583b3c1ff21db4a561285717028fdafc780b7db.
// Native117AD0..117BAB (219B); Begin_Render118170 calls this capture helper.
// Donor carries the WW3D movie-copy purpose and class spellings. Native calls
// prove GetBuffer-first ordering and no trailing Grab; native loop proves
// flipped RGB rows, hoisted row offsets, and four-byte source pixels.
// Movie DEC3DC (ww3d.cpp's private static) and g_WW3D_Hwnd DEC408 use
// existing global providers.
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
class WW3D;
struct IDirect3DDevice8;
struct _D3DVIEWPORT8;
class Vector3;
class LightEnvironmentClass;
class DX8Wrapper
{
private:
	friend class WW3D;
protected:
	static IDirect3DDevice8 *D3DDevice;
	// dx8wrapper.cpp's protected static at VA 0x00DEDC70.
	static Vector3 Ambient_Color;
public:
	static bool Reset_Device(bool reload_assets);
	static IDirect3DSurface9 *_Get_DX8_Front_Buffer();
	static void Shutdown();
private:
	static void Get_Render_Target_Resolution(int &,int &,int &,bool &);
public:
	static void Set_Viewport(const _D3DVIEWPORT8 *viewport);
	static void Clear(bool clear_color, bool clear_z_stencil, bool clear_stencil, const Vector3 &color, float dest_alpha, float z, unsigned int stencil);
	static void Begin_Scene_Inner(void);
	static void Set_DX8_Render_State(unsigned long state, unsigned value);
	// dllimport: inlined at every use, so no out-of-line copy competes with retail's
	// Convert_Color (0x0006E1C0) or Set_Ambient (0x00117F50, DX8SetAmbient.cpp).
	__declspec(dllimport) static unsigned Convert_Color(const Vector3 &color, float alpha);
	__declspec(dllimport) static void Set_Ambient(const Vector3 &color);
	static void Set_Light_Environment(LightEnvironmentClass *light_env);
};
class FrameGrabClass
{
public:
	long *GetBuffer();
	virtual ~FrameGrabClass();
};
extern "C" __declspec(dllimport) int __stdcall GetWindowRect(void *,RECT *);
void Log_DX8_ErrorCode(UInt);
extern void *g_WW3D_Hwnd;
class WW3D { static FrameGrabClass *Movie; public: static void Update_Movie_Capture(); };
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

