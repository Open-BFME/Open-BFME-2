// ?rva001F54C5@Rva001F54C5@@QAE?AURva003AFA0BVector@@PAX@Z
// partial score=0.65 date=2026-10-07
// cl: /O1 /DNDEBUG /MD /EHs-c- /G7 /arch:SSE
// Native 0x001F54C5..0x001F553F, RET 8 including a three-float hidden
// return pointer. Calls the verified vector producer at 0x003AFA0B.
// Receiver, optional-pointer type and scalar meanings remain unknown.

struct Rva003AFA0BVector
{
    Rva003AFA0BVector() {}
    __forceinline Rva003AFA0BVector(const Rva003AFA0BVector &that)
        : x(that.x), y(that.y), z(that.z) {}
    float x, y, z;
};

class Rva003AFA0B
{
public:
    Rva003AFA0BVector rva003AFA0B(void *a, const Rva003AFA0BVector *source,
                                float scale, void *b);
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct Rva001F54C5Global
{
    char m_pad00[0x9EC];
    float m_value9ec;
};

struct Rva001F54C5Head { char m_pad00[0x18]; };
struct Rva001F54C5Base18 { char m_unmodelled18; };
struct Rva001F54C5Optional : Rva001F54C5Head, Rva001F54C5Base18 {};

struct Rva001F54C5Handle
{
    Rva001F54C5Optional *m_pointer;
    operator bool() const { return m_pointer != 0; }
    Rva001F54C5Optional *operator->() const { return m_pointer; }
};

class Rva001F54C5
{
public:
    Rva003AFA0BVector rva001F54C5(void *a);
private:
    char m_pad00[0x130];
    Rva003AFA0BVector m_source130;
    char m_pad13c[0x1BC - 0x13C];
    Rva003AFA0B *m_producer1bc;
    Rva001F54C5Handle m_optional1c0;
};

Rva003AFA0BVector Rva001F54C5::rva001F54C5(void *a)
{
    if (m_producer1bc && m_optional1c0)
    {
        return m_producer1bc->rva003AFA0B(a, &m_source130,
            (reinterpret_cast<Rva001F54C5Global *>(TheWritableGlobalData)->m_value9ec
                + 1.0f) * 0.5f,
            static_cast<Rva001F54C5Base18 *>(m_optional1c0.operator->()));
    }
    Rva003AFA0BVector result;
    result.x = result.y = result.z = 0.0f;
    return result;
}
