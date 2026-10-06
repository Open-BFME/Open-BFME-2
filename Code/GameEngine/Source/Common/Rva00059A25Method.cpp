// cl: /EHsc /MD
// ?rva00059A25@Rva00059A25@@QAEXABVAsciiString@@H@Z @ 0x00059A25 87B: thiscall
// locks MilesMutexGuard over +0x9D4 then calls row 0x000591A3 on array elem
// at +0x12C stride 0x1C4 with idx and AsciiString; chain from 0x000591A3.
class AsciiString;

class Rva000591A3
{
public:
    void rva000591A3(const AsciiString &name);
    void rva000591EF();
};

class MilesMutexGuard
{
public:
    MilesMutexGuard(void *obj, int flags);
    ~MilesMutexGuard();
private:
    void *m_obj;
    int m_flags;
};

struct Elem1C4
{
    char data[0x1C4];
};

class Rva00059A25
{
public:
    void rva00059A25(const AsciiString &name, int idx);
    void rva00059A7C(int idx);
private:
    char m_pad[0x12C];
    Elem1C4 m_arr[1];
    char m_padAfter[0x9D4 - 0x12C - 0x1C4];
    int m_9D4;
};

void Rva00059A25::rva00059A25(const AsciiString &name, int idx)
{
    MilesMutexGuard guard(&m_9D4, 0);
    ((Rva000591A3 *)&m_arr[idx])->rva000591A3(name);
}

void Rva00059A25::rva00059A7C(int idx)
{
    MilesMutexGuard guard(&m_9D4, 0);
    ((Rva000591A3 *)&m_arr[idx])->rva000591EF();
}
