// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Reference semantics: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// WW3D2/segline.cpp bounding-box kernel and WWMath/vector3.h/aabox.h helpers.
// Native16825D..1683A7 is a330B RET4 leaf. The word at rdata7D42D8 places it
// beside RenderObj bounding accessors. It reads pointsC8/countD0/widthEC,
// computes extrema, expands by half-width, and writes center plus extent.
// Count below two gives zero center and unit extent. Native typed width and
// all float constants are independently checked. Original owner is unknown;
// only the consumed prefix is represented, with no complete-object size claim.
// Local math helpers preserve the donor's inline copy/assignment and expression
// shape without emitting competing definitions of the shared library helpers.
// Their unused out-of-line copies are implementation details, never recovery rows.
namespace {
struct Rva0016825DPoint {
    float X,Y,Z;
    Rva0016825DPoint() {}
    __forceinline Rva0016825DPoint(const Rva0016825DPoint &v) {X=v.X;Y=v.Y;Z=v.Z;}
    __forceinline Rva0016825DPoint &operator=(const Rva0016825DPoint &v) {X=v.X;Y=v.Y;Z=v.Z;return *this;}
    __forceinline Rva0016825DPoint(float x,float y,float z) { X=x;Y=y;Z=z; }
    __forceinline Rva0016825DPoint &operator+=(const Rva0016825DPoint &v) { X+=v.X;Y+=v.Y;Z+=v.Z;return *this; }
    __forceinline Rva0016825DPoint &operator-=(const Rva0016825DPoint &v) { X-=v.X;Y-=v.Y;Z-=v.Z;return *this; }
    __forceinline void Update_Max(const Rva0016825DPoint &a) { if(a.X>X)X=a.X; if(a.Y>Y)Y=a.Y; if(a.Z>Z)Z=a.Z; }
    __forceinline void Update_Min(const Rva0016825DPoint &a) { if(a.X<X)X=a.X; if(a.Y<Y)Y=a.Y; if(a.Z<Z)Z=a.Z; }
};
static __forceinline Rva0016825DPoint operator+(const Rva0016825DPoint &a,const Rva0016825DPoint &b) {return Rva0016825DPoint(a.X+b.X,a.Y+b.Y,a.Z+b.Z);}
static __forceinline Rva0016825DPoint operator-(const Rva0016825DPoint &a,const Rva0016825DPoint &b) {return Rva0016825DPoint(a.X-b.X,a.Y-b.Y,a.Z-b.Z);}
static __forceinline Rva0016825DPoint operator*(const Rva0016825DPoint &a,float b) {return Rva0016825DPoint(a.X*b,a.Y*b,a.Z*b);}
}
struct Rva0016825DBox {
    Rva0016825DPoint Center,Extent;
    __forceinline void Init(const Rva0016825DPoint &center,const Rva0016825DPoint &extent) {Center=center;Extent=extent;}
    __forceinline void Init_Min_Max(const Rva0016825DPoint &minimum,const Rva0016825DPoint &maximum) {
        Center=(maximum+minimum)*0.5f;
        Extent=(maximum-minimum)*0.5f;
    }
};
struct Rva0016825DLineView {
    char unknown00[0xc8];
    const Rva0016825DPoint *points;
    unsigned unknownCC;
    unsigned count;
    char unknownD4[0x18];
    float width;
    void bounds(Rva0016825DBox &box) const;
    void sphere(struct Rva001681EDSphere &sphere) const;
};
void Rva0016825DLineView::bounds(Rva0016825DBox &box) const
{
    unsigned num=count;
    if (num>=2) {
        Rva0016825DPoint maximum=points[0];
        Rva0016825DPoint minimum=points[0];
        for (unsigned i=1;i<num;++i) {
            maximum.Update_Max(points[i]);
            minimum.Update_Min(points[i]);
        }
        float enlarge=width*0.5f;
        Rva0016825DPoint offset(enlarge,enlarge,enlarge);
        maximum+=offset;
        minimum-=offset;
        box.Init_Min_Max(minimum,maximum);
    } else {
        box.Init(Rva0016825DPoint(0,0,0),Rva0016825DPoint(1,1,1));
    }
}

// The donor WWMath::Sqrt x87 helper is retained only for this proven codegen
// blocker: ordinary C++ sqrt and a float wrapper both emitted 81B, while this
// preserves the native single-precision argument/result spills and fsqrt.
static __forceinline float rva001681EDSqrt(float value) { float result; __asm {
        fld [value]
        fsqrt
        fstp [result]
    } return result; }
struct Rva001681EDSphere {
    Rva0016825DPoint Center;
    float Radius;
};
// Native1681ED..16825D: 112B RET4, vtable word7D42D4 next to bounds.
// The complete body dispatches the box accessor through slot110, copies its
// center, and takes the length of its extent. BF1 ba7 segline.cpp supplies
// the same algorithm; it does not establish the original owner name.
void Rva0016825DLineView::sphere(Rva001681EDSphere &sphere) const
{
    Rva0016825DBox box;
    typedef void (Rva0016825DLineView::*BoundsFn)(Rva0016825DBox &) const;
    union { void *address; BoundsFn member; } fn;
    fn.address=(*reinterpret_cast<void *const *const *>(this))[0x110/4];
    (this->*fn.member)(box);
    sphere.Center=box.Center;
    sphere.Radius=rva001681EDSqrt(box.Extent.X*box.Extent.X+box.Extent.Y*box.Extent.Y+box.Extent.Z*box.Extent.Z);
}
