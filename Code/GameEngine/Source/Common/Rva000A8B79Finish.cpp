// cl: /MD
// ?rva000A8B6D@Rva000A8B6D@@QAEXXZ @0x000A8B6D 12B.
// ?rva000A8B79@Rva000A8B6D@@QAEXPAVRva000A8C2BObj@@@Z @0x000A8B79 178B chain.
// 0x000A8B6D null-guarded forward to rowed ?rva0010F110@Rva0010F110@@QAEXXZ.
// 0x000A8B79 calls 0x000A8B6D with same this then reads Rva0010F110 stream.
// Evidence: mov ecx esi call 0xa8b6d with no pushes; [esi] deref with +0x08
// stream and +0x1C matching Rva0010F110 layout; slots 0x28 0x70 0x7C matching
// Rva000A8C2BObj width; IAT ms_position 0x00BBAAC8 loop_count 0x00BBABB0.
// Honest address names sharing Rva000A8B6D class proven by same-this call.
extern "C" __declspec(dllimport) void __stdcall AIL_stream_ms_position(
    void *stream, long *total_milliseconds, long *current_milliseconds);
extern "C" __declspec(dllimport) int __stdcall AIL_stream_loop_count(void *stream);

typedef void *HSTREAM;

class Rva0010F110
{
public:
    void rva0010F110();
    HSTREAM volatile_stream08() { return *(HSTREAM volatile *)&m_stream08; }
public:
    char m_pad0[8];
    HSTREAM m_stream08;
    char m_pad0C[0x0C];
    void *m_handle18;
    int m_field1C;
};

struct TwoBytes
{
    unsigned char a;
    unsigned char b;
};

class Rva000A8C2BObj
{
public:
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10(TwoBytes *t);
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28(int *p);
    virtual void s29();
    virtual void s30();
    virtual void s31(int *p);
};

class Rva000A8B6D
{
public:
    void rva000A8B6D();
    void rva000A8B79(Rva000A8C2BObj *obj);
private:
    Rva0010F110 *m_ptr;
};

void Rva000A8B6D::rva000A8B6D()
{
    if (m_ptr != 0)
        m_ptr->rva0010F110();
}

void Rva000A8B6D::rva000A8B79(Rva000A8C2BObj *obj)
{
    TwoBytes t;
    t.a = 1;
    t.b = 1;
    obj->s10(&t);
    rva000A8B6D();
    float ratio;
    int loops;
    int field;
    if (m_ptr != 0 && m_ptr->m_stream08 != 0) {
        HSTREAM stream = m_ptr->volatile_stream08();
        long total;
        long current;
        AIL_stream_ms_position(stream, &total, &current);
        if (total <= 0)
            ratio = 0.0f;
        else
            ratio = (float)current / (float)total;
        loops = AIL_stream_loop_count(m_ptr->m_stream08);
        field = m_ptr->m_field1C;
    } else {
        ratio = 0.0f;
        loops = 0;
        field = 0;
    }
    obj->s28((int *)&ratio);
    obj->s31(&loops);
    obj->s31(&field);
}
