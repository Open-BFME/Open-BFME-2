// cl: /MD
// ?rva000A8A6C@Rva000A8A6C@@QAEXXZ @0x000A8A6C 19B unlock.
// Guarded release then null; callee ?release@Gen0002857E@@QAEXXZ pin-only.
// Evidence: push esi mov esi ecx mov ecx [esi] test je call 0x10ece4 and [esi] 0.
// Honest address name; owner unknown so class Rva000A8A6C.
class Gen0002857E
{
public:
    void release();
};

class Rva000A8A6C
{
public:
    void rva000A8A6C();
private:
    Gen0002857E *m_ptr;
};

void Rva000A8A6C::rva000A8A6C()
{
    if (m_ptr != 0)
        m_ptr->release();
    m_ptr = 0;
}
