// cl: /O1 /G7 /arch:SSE /EHsc /MD
// Native 4D9750..4D977D RET8; caller supplies hidden 8-byte result and index.
// The return construction flag at EBP-4 proves a C++ value result rather than
// the prior bank's explicit output pointer. Copy/default providers are the
// same 2390CB/4CEE6E pair independently verified for native35B456 siblings.
class Rva002390CB {
public:
    Rva002390CB();
    Rva002390CB(const Rva002390CB &other);
    ~Rva002390CB();
    void *m_00;
    void *m_04;
};
class Rva004D9750 {
public:
    Rva002390CB rva004D9750(int index);
    Rva002390CB items[1];
};
Rva002390CB Rva004D9750::rva004D9750(int index)
{
    if (index == -1)
        return Rva002390CB();
    return items[index];
}
