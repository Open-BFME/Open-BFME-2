// cl: /O1 /arch:SSE /DNDEBUG /MD
// Retail 004AC135/19 is slot 1 of the secondary vtable VA 00C54BA0.
// The byte-verified RainOfFireUpdate ctor 004AC0A8 installs that table at
// complete-object +20; its name getter 004AC12F returns RainOfFireUpdate.
// The preceding body ends with RET at 004AC134; this complete body ends
// with RET 4 at 004AC145 before the next boundary 004AC148.
// Native SSE adds the by-value float argument to secondary-relative +0C
// (complete-object +2C). This is an opaque view of that proven subobject;
// neither an original interface name nor the state's purpose is claimed.
// The W3D donor's Matrix3D::Adjust_X_Translation emitted these same bytes,
// but its identity is refuted by the RainOfFireUpdate secondary vtable.
class Rva004AC135RainOfFireSecondary20
{
public:
    void addState(float delta);
private:
    unsigned char opaque00[0x0C];
    float state0C;
};

void Rva004AC135RainOfFireSecondary20::addState(float delta)
{
    state0C += delta;
}
