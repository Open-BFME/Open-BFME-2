#ifndef BFME_RVA0028C6D6_H
#define BFME_RVA0028C6D6_H

// Anonymous target type: copy constructor 0x0028C6D6 and default constructor
// 0x00262093 both store vftable VA 0x00BF91AC. Its complete single entry is
// the method at RVA 0x004D70D5, not a destructor. The original name and
// transfer protocol are unknown. The default constructor zeros two floats
// and a byte; the copy constructor preserves their two dwords and byte.
// BFME 1 ActiveBody_Constructor.cpp at 34f59164f6d1 supplies the clean
// DamageInfoOutput initializer lead, but that donor name is not target proof.
class Rva0028C6D6
{
public:
    Rva0028C6D6() throw();
    Rva0028C6D6(const Rva0028C6D6 &other) throw();
    virtual void rva004D70D5(void *arg);

    union { int m_field04; float m_real04; };
    union { int m_field08; float m_real08; };
    char m_field0C;
};

#endif
