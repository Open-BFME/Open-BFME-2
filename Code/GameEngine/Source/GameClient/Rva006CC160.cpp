// ??HRva006CC160@@QAE?AU0@ABU0@@Z
// cl: /MD
// Address-derived target identity: direct callers have not been located. The retail body performs eight 32-bit field-wise additions and returns a 32-byte value. The relationship to AptMemoryAllocationsT and the field meanings remain donor-based inferences.
// Whole body122 bytes and eight32-bit arithmetic fields match the donor.
struct Rva006CC160 {
    unsigned int m_00;
    unsigned int m_04;
    unsigned int m_08;
    unsigned int m_0C;
    unsigned int m_10;
    unsigned int m_14;
    unsigned int nAptUpdateAllocationGCSize;
    unsigned int m_1C;
    Rva006CC160 operator+(const Rva006CC160 &other);
};
Rva006CC160 Rva006CC160::operator+(const Rva006CC160 &other)
{
    Rva006CC160 sum;
    sum.m_00=m_00+other.m_00;
    sum.m_04=m_04+other.m_04;
    sum.m_10=m_10+other.m_10;
    sum.m_14=m_14+other.m_14;
    sum.m_08=m_08+other.m_08;
    sum.m_0C=m_0C+other.m_0C;
    sum.nAptUpdateAllocationGCSize=nAptUpdateAllocationGCSize+other.nAptUpdateAllocationGCSize;
    sum.m_1C=m_1C+other.m_1C;
    return sum;
}
