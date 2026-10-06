// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /Oi /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// ?rva0005516F@Rva0005516F@@QAEXPAUHolder@@H@Z @0x0005516F 83B.
// Outer array at +0x12C stride 0x1C4 of Rva00699180Owner; first calls elem[key] then if key==2 fans out to elems 0,1 with key 2.
// Evidence: same +0x12C/0x1C4 array as MilesAudioManagerRva00053CE1.cpp and Rva00059A25Method.cpp; callee row 0x000550F7; caller 0x0005FDCA.
struct Holder;
class Rva00699180Owner
{
public:
    void rva000550F7(Holder *o, int key);
};
struct Elem1C4
{
    char data[0x1C4];
};
class Rva0005516F
{
public:
    void rva0005516F(Holder *o, int key);
private:
    char m_pad[0x12C];
    Elem1C4 m_arr[3];
};
void Rva0005516F::rva0005516F(Holder *o, int key)
{
    ((Rva00699180Owner *)&m_arr[key])->rva000550F7(o, key);
    if (key == 2)
    {
        for (int i = 0; i < 3; ++i)
        {
            if (i != 2)
                ((Rva00699180Owner *)&m_arr[i])->rva000550F7(o, 2);
        }
    }
}
