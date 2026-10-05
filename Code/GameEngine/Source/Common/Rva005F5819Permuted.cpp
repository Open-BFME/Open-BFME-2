// cl: /O1 /DNDEBUG /EHsc /MD
//
// ??1Rva005F5819@@UAE@XZ, retail 0x005f5819, 97 bytes. Banked partial (score 0.95) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
class CreateAHeroData;

class Rva002B7250 {
public:
    void rva002B7250(CreateAHeroData *v);
};

class Rva005E12D1 {
public:
    virtual ~Rva005E12D1();
    int m_pad[4];
};

class Rva005F5819Base0 {
public:
    virtual ~Rva005F5819Base0() {}
    int m_b;
};

class Rva005F5819Mid {
public:
    virtual ~Rva005F5819Mid() {}
    int m_c;
};

class Rva005F5819 : public Rva005F5819Base0, public Rva005E12D1, public Rva005F5819Mid {
public:
    virtual ~Rva005F5819();
    Rva002B7250 *m_list;
};

Rva005F5819::~Rva005F5819()
{
    m_list->rva002B7250((CreateAHeroData *)((char *)this + 0x1c));
}
