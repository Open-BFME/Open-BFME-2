// ??0Rva004FBC4D@@QAE@ABV?$StringBase@G@@0H@Z
// partial score=0.9297850821744627 date=2026-10-10
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// ??0Rva004FBC4D@@QAE@ABV?$StringBase@G@@0H@Z
// partial score=0.92 date=2026-10-03
// ??0Rva004FBC4D@@QAE@ABV?$StringBase@G@@0H@Z
// partial score=0.92 date=2026-10-03
// ??0Rva004FBC4D@@QAE@ABV?$StringBase@G@@0H@Z
// partial score=0.92 date=2026-09-29
// ??0Rva004FBC4D@@QAE@ABV?$StringBase@G@@0H@Z
// partial score=0.92 date=2026-09-29
// cl: /O1 /EHsc /arch:SSE /DNDEBUG /MD
// ??0Rva004FBC4D@@QAE@ABV?$StringBase@G@@0H@Z, retail 0x004FBC4D, 113 bytes.
// Ctor with vtable 0x008634E4, two Wide strings at +8/+0xC, int/flag/float tail.
// Evidence: EH states 0/1 around two StringBase copy pins 0x37050; movss zero floats; callers 5 incl 951B/1050B; unblocks 5.
template <typename T> class StringBase {
public:
    StringBase(const StringBase &other);
    ~StringBase();
private:
    void *m_data;
};
struct Rva004FBC4DEmptyBase {
    Rva004FBC4DEmptyBase() : m04(0) {}
    ~Rva004FBC4DEmptyBase();
    int m04;
};
struct Rva004FBC4D : public Rva004FBC4DEmptyBase {
    virtual ~Rva004FBC4D();
    Rva004FBC4D(const StringBase<unsigned short> &a1, const StringBase<unsigned short> &a2, int a3);
private:
    StringBase<unsigned short> m08;
    StringBase<unsigned short> m0C;
    int m10;
    int m14;
    float m18;
    float m1C;
    float m20;
    unsigned char m24;
    unsigned char m25;
    unsigned char m26;
};
inline Rva004FBC4D::~Rva004FBC4D() {}
// ??0Rva004FBC4D@@QAE@ABV?$StringBase@G@@0H@Z present-unmatched
Rva004FBC4D::Rva004FBC4D(const StringBase<unsigned short> &a1, const StringBase<unsigned short> &a2, int a3)
    : m08(a1), m0C(a2), m10(a3), m14(-1), m18(0.0f), m1C(0.0f), m20(0.0f)
{
 (this?_ReadWriteBarrier():_ReadWriteBarrier());
    m24 = 0;
    m25 = 0;
    m26 = 0;
}