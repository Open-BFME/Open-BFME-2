// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva002B4280@Rva002B4280@@QAEXXZ @0x002B4280 140B.
// Unlock lane; sibling of 0x002B41F4 with flag +0x177 state +0x98->0x2C0 message 0x6BB.
// Counts array at +0x8C/0x90 whose elements have +0x44==0 and +0x3C4==0,
// then posts GameMessage 0x6BB with arg 1 unless (flag or state==1) and count>1.
// Callees rowed 0x0030F936; unblocks 0x002B4FEB. Sets flag +0x177.
// TU-local honest-address class; shape from Rva002B41F4.cpp.
extern class MessageStream *TheMessageStream;

#include <vector>
class GameMessage {
public:
    void appendIntegerArgument(int arg);
};
class Rva002B4280Factory {
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17();
    virtual GameMessage *newMessage(int type);
};
#define TheMsgFactory002B4280 (*(Rva002B4280Factory **)&TheMessageStream)
struct Rva002B4280Elem {
    char m_pad[0x44];
    int m_44;
    char m_pad2[0x3C4 - 0x44 - 4];
    unsigned char m_3C4;
};
struct Rva002B4280State {
    char m_pad[0x2C0];
    int m_2C0;
};
class Rva002B4280 {
    char m_pad0[0x8C];
    _STL::vector<Rva002B4280Elem *> m_vec;
    Rva002B4280State *m_state98;
    char m_pad1[0x177 - 0x9C];
    unsigned char m_flag177;
public:
    void rva002B4280();
};
void Rva002B4280::rva002B4280()
{
    int count = 0;
    for (unsigned int i = 0; i < m_vec.size(); ++i) {
        Rva002B4280Elem *e = m_vec[i];
        if (e != 0 && e->m_44 == 0 && e->m_3C4 == 0)
            ++count;
    }
    if ((m_flag177 != 0 || m_state98->m_2C0 == 1) && count > 1) {
    } else {
        Rva002B4280Factory *factory = TheMsgFactory002B4280;
        GameMessage *msg = factory->newMessage(0x6BB);
        msg->appendIntegerArgument(1);
    }
    m_flag177 = 1;
}
