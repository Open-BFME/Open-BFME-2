// cl: /MD
// Statistics texture-handle shutdown, RVA 0x007B7040 (10 bytes).
// Target facts: the initializer at 0x007ACCCA registers this callback;
// it passes global VA 0x00DEE918 to the rowed RefCountPtr<TextureClass>
// destructor at 0x0017098D. The matched recording routines independently
// identify that global as latest_texture. Keep the destructor opaque here
// so MSVC emits retail's out-of-line tail jump.
class TextureClass;

template<class T>
class RefCountPtr
{
public:
    ~RefCountPtr();
private:
    T *Referent;
};

extern RefCountPtr<TextureClass> g_Va00DEE918;

void __cdecl rva007B7040()
{
    g_Va00DEE918.~RefCountPtr();
}
