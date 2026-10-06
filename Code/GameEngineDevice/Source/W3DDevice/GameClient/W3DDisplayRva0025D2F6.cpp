// cl: /DNDEBUG /MD /EHsc
// ?rva0025D2F6@W3DDisplay@@QAEXXZ @0x0025D2F6 69B: W3DDisplay clear helper.
// Retail xorps plus push-3 countdown loop zeroes 3x0x18 array at +0x68 then
// two floats at +0xC8/+0xCC then add ecx 0xB0 plus jmp to wide releaseBuffer.
// Evidence: TheDisplay global 0x00DFE9D8 as this in 12 callers incl 0x002396C4
// and 0x00239721 and 0x0025D642 and 0x0025D874 and 0x0025DA0C; ctor 0x0025D489
// with vtable 0x7F5DA0 calls it at the end; element ctor 0x0025C07D proves
// the 0x18 int plus 4 floats plus int layout; wide clear folds to rowed
// releaseBuffer 0x00036E70.
template <typename T> class StringBase
{
public:
    void clear() { releaseBuffer(); }
private:
    void releaseBuffer();
    T *m_data;
};
struct DisplayRva0025D2F6Elem
{
    int m_a;
    float m_b;
    float m_c;
    float m_d;
    float m_e;
    int m_f;
};
class W3DDisplay
{
public:
    void rva0025D2F6();
private:
    unsigned char m_pad00[0x68];
    DisplayRva0025D2F6Elem m_arr[3];
    StringBase<unsigned short> m_str;
    unsigned char m_padB4[0x14];
    float m_f1;
    float m_f2;
};
void W3DDisplay::rva0025D2F6()
{
    for (int i = 0; i < 3; i++)
    {
        m_arr[i].m_b = 0.0f;
        m_arr[i].m_c = 0.0f;
        m_arr[i].m_d = 0.0f;
        m_arr[i].m_e = 0.0f;
        m_arr[i].m_a = 0;
        m_arr[i].m_f = 0;
    }
    m_f1 = 0.0f;
    m_f2 = 0.0f;
    m_str.clear();
}
