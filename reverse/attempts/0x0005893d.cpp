// ??0Rva0005893D@@QAE@H@Z
// partial score=0.86 date=2026-10-07
#include <vector>

typedef _STL::vector<unsigned int> Rva0005893DVector;
typedef _STL::allocator<unsigned int> Rva0005893DAllocator;

namespace _STL {
template<> vector<unsigned int, allocator<unsigned int> >::vector(
    const allocator<unsigned int> &allocator);
}

class Rva0005893D {
public:
    Rva0005893D(int bucketHint);
    void rva00057E6A(int bucketHint);
private:
    int m_at00;
    Rva0005893DVector m_buckets; // +0x04
    int m_count;                 // +0x10
};

Rva0005893D::Rva0005893D(int bucketHint)
    : m_buckets(Rva0005893DAllocator())
{
    m_count = 0;
    rva00057E6A(bucketHint);
}
