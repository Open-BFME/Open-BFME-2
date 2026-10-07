// ?compose@Rva0015FC20TransformPrefix@@QAEXABU1@@Z
// partial score=0.769 date=2026-10-07
// cl: /O2 /G7 /arch:SSE /MD /DNDEBUG
// BF1 ba7 quat.h Rotate_Vector supplies the reference algorithm. Native
// 15FC20..15FE7F is a complete607B RET4 leaf: rotate/add the other prefix
// position10..18 using receiver rotation0..C, then incrementally multiply
// receiver rotation by the other rotation. Only this consumed28B prefix is
// modeled; the owner name and enclosing allocation remain unproven.
// Native evidence supports the explicit subtraction order. The O2/G7
// trial emits600B, first differing at+34; O1 emits578B. It remains unverified.
// The saved receiver rotation plus incremental writes preserve native
// alias behavior; no pointers, dumps or callee pins are introduced.
namespace {
struct Rva0015FC20Point {
    float X,Y,Z;
    Rva0015FC20Point(float x,float y,float z) : X(x),Y(y),Z(z) {}
    __forceinline Rva0015FC20Point &operator+=(const Rva0015FC20Point &v) {X+=v.X;Y+=v.Y;Z+=v.Z;return *this;}
};
struct Rva0015FC20Rotation {
    float x,y,z,w;
    __forceinline Rva0015FC20Point rotate(const Rva0015FC20Point &v) const {
        float a = (y*v.Z-v.Y*z)+w*v.X;
        float b = w*v.Y-(x*v.Z-v.X*z);
        float c = (x*v.Y-v.X*y)+w*v.Z;
        float d = 0.0f-(z*v.Z+y*v.Y+x*v.X);
        return Rva0015FC20Point((y*c-z*b)+(w*a-x*d),w*b-y*d-(x*c-z*a),(x*b-y*a)+(w*c-z*d));
    }
    __forceinline void multiply(const Rva0015FC20Rotation &other) {
        Rva0015FC20Rotation saved=*this;
        x=(saved.y*other.z-other.y*saved.z)+other.w*saved.x+saved.w*other.x;
        y=other.w*saved.y+saved.w*other.y-(saved.x*other.z-other.x*saved.z);
        z=(saved.x*other.y-other.x*saved.y)+other.w*saved.z+saved.w*other.z;
        w=other.w*saved.w-(other.z*saved.z+other.y*saved.y+other.x*saved.x);
    }
};
}
struct Rva0015FC20TransformPrefix {
    Rva0015FC20Rotation Rotation;
    Rva0015FC20Point Position;
    void compose(const Rva0015FC20TransformPrefix &other);
};
void Rva0015FC20TransformPrefix::compose(const Rva0015FC20TransformPrefix &other) {
    Position+=Rotation.rotate(other.Position);
    Rotation.multiply(other.Rotation);
}
