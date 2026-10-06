// cl: /MD
// ?rva005C6599@Rva005C6599@@QAEXMM@Z 0x005C6599 88B setPos via MoveButtonFlash when x or y differs plus store; caller 0x005C694F; callee MoveButtonFlash 0x003FED66
void __cdecl Rva003FED66MoveButtonFlash(void **pp, float f1, float f2);
class Rva005C6599 {
public:
    void rva005C6599(float x, float y);
private:
    char _p0[8];
    void *m_8;
    float m_C;
    float m_10;
};
void Rva005C6599::rva005C6599(float x, float y)
{
    if (x != m_C || y != m_10) {
        Rva003FED66MoveButtonFlash(&m_8, x, y);
        m_C = x;
        m_10 = y;
    }
}
