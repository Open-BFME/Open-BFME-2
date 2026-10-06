// cl: /DNDEBUG /EHsc /MD
// ??1Rva005F5BF2@@UAE@XZ @0x005F5BF2 97B: dtor via rowed erase 0x002B7250 plus pinned 0x005E12D1; caller deleting dtor 0x005F5C5B
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

class Rva005F5BF2Base0 {
public:
    virtual ~Rva005F5BF2Base0() {}
    int m_b;
};

class Rva005F5BF2Mid {
public:
    virtual ~Rva005F5BF2Mid() {}
    int m_c;
};

class Rva005F5BF2 : public Rva005F5BF2Base0, public Rva005E12D1, public Rva005F5BF2Mid {
public:
    virtual ~Rva005F5BF2();
    Rva002B7250 *m_list;
};

Rva005F5BF2::~Rva005F5BF2()
{
    m_list->rva002B7250((CreateAHeroData *)((char *)this + 0x1c));
}
