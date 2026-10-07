// ?multiply@Rva0015F810QuaternionPrefix@@QAEXABU1@@Z
// partial score=0.91 date=2026-10-07
// cl: /O2 /G7 /arch:SSE /MD /DNDEBUG
// Target15F810 has16B of receiver state but its enclosing object size is unknown.
struct Rva0015F810QuaternionPrefix {
    float x,y,z,w;
    void multiply(const Rva0015F810QuaternionPrefix &other);
};
void Rva0015F810QuaternionPrefix::multiply(const Rva0015F810QuaternionPrefix &other)
{
    Rva0015F810QuaternionPrefix saved=*this;
    x=(saved.y*other.z-other.y*saved.z)+other.w*saved.x+saved.w*other.x;
    y=other.w*saved.y+saved.w*other.y-(saved.x*other.z-other.x*saved.z);
    z=(saved.x*other.y-other.x*saved.y)+other.w*saved.z+saved.w*other.z;
    w=other.w*saved.w-(other.z*saved.z+other.y*saved.y+other.x*saved.x);
}
