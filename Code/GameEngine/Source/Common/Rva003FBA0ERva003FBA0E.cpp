// cl: /DNDEBUG /MD /Op
//
// ?rva003FBA0E@Rva003FBA0E@@QAEXHHHHHM@Z, retail 0x003fba0e, 74 bytes. Banked partial (score 0.9) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Unlock init with 5 ints plus float. Evidence: clears +0x4c +0x38 stores e b c
// b-a d sets +0x2c=3 float to +0x54 then slot3 virtual.
class Rva003FBA0E {
public:
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void slot03();
    void rva003FBA0E(int a, int b, int c, int d, int e, float f);
private:
    unsigned char pad04[0x28];
    int m_2c;
    unsigned char pad30[0x04];
    int m_34;
    int m_38;
    int m_3c;
    int m_40;
    int m_44;
    int m_48;
    int m_4c;
    int m_50;
    float m_54;
};
void Rva003FBA0E::rva003FBA0E(int a, int b, int c, int d, int e, float f)
{
    m_4c = 0;
    m_50 = e;
    m_2c = 3;
    m_38 = 0;
    m_40 = b;
    m_3c = a;
    m_44 = c;
    m_48 = d;
    m_54 = f;
    m_34 = b - a;
    slot03();
}
