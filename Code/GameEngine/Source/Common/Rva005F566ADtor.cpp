// cl: /O1 /DNDEBUG /MD
// ??1Rva005F566A@@UAE@XZ @0x005F566A 14B: dtor sets vptr then tail-jmps to rowed clear 0x005F55FA; caller deleting dtor 0x005F5678
class Rva005F55FA {
public:
    void clear();
};

class Rva005F566A {
public:
    virtual ~Rva005F566A();
    Rva005F55FA m_holder;
};

Rva005F566A::~Rva005F566A()
{
    m_holder.clear();
}
