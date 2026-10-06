// cl: /MD
// ?rva0060D4C9@Rva0060D4C9@@QAEEPAVXfer@@@Z @0x0060D4C9 49B
// Chain over rowed XferSave open 0x0060D10A. Evidence: same this for open call,
// slot-4 NOT via neg/sbb/inc, arg 1 plus NOT result, m_44 clear, caller 0x0023CB61.
class Xfer;
class Rva00BBB910Base { public: virtual ~Rva00BBB910Base() {} };
struct BfmePositionVector {
    int *m_begin;
    int *m_end;
    int *m_capacity;
};
struct Rva0060D031Member { unsigned int opaque[5]; };
struct Rva0060CC99Member { unsigned int opaque[5]; };
class XferSave : public Rva00BBB910Base {
public:
    virtual ~XferSave();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual unsigned char v4();
    unsigned char Open(Xfer *stream, int arg2, bool arg3);
private:
    void *volatile m_stream;
    bool m_flag;
    unsigned char m_pad[3];
    BfmePositionVector m_positions;
    Rva0060D031Member m_at18;
    Rva0060CC99Member m_at2c;
};
class Rva0060D4C9 : public XferSave {
public:
    unsigned char rva0060D4C9(Xfer *stream);
private:
    unsigned char _40[4];
    int m_44;
};
unsigned char Rva0060D4C9::rva0060D4C9(Xfer *stream)
{
    if (stream == 0) {
        m_44 = 0;
        return 1;
    }
    if (!Open(stream, 1, !v4()))
        return 0;
    m_44 = 0;
    return 1;
}
