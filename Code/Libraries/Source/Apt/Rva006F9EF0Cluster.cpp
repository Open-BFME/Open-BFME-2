// cl: /O2 /MD
// ?Rva006F9EF0@Rva006FB860@@QAEXXZ @0x006F9EF0 194B
// Member of Rva006FB860 (caller 0x006FB910 in Rva006FB910Cluster.cpp).
// Computes x=(float)m74-m58 y=(float)m78-m5C clamps x by m48/m50 and y by
// m4C/m54 against the -9999.0f sentinel then checked-casts mValue via rowed
// 0x006DCF60 and sets properties 0/1 via pinned factorySetProperty.
class BfmeAptValue006DCD20
{
public:
    BfmeAptValue006DCD20 *rva006DCF60(bool bUndefOK);
};
class AptCIH
{
public:
    void factorySetProperty(int prop, float value, bool flag);
};
class Rva006FB860
{
public:
    char m_pad[0x44];
    BfmeAptValue006DCD20 *mValue; // +0x44
    float m48; // +0x48
    float m4C; // +0x4C
    float m50; // +0x50
    float m54; // +0x54
    float m58; // +0x58
    float m5C; // +0x5C
    char m_pad2[0x14]; // +0x60..0x73
    int m74; // +0x74
    int m78; // +0x78
    void Rva006F9EF0();
};
void Rva006FB860::Rva006F9EF0()
{
    float x = (float)m74 - m58;
    float y = (float)m78 - m5C;
    if (m48 != -9999.0f) {
        if (x < m48)
            x = m48;
    }
    if (m50 != -9999.0f) {
        if (x > m50)
            x = m50;
    }
    if (m4C != -9999.0f) {
        if (y < m4C)
            y = m4C;
    }
    if (m54 != -9999.0f) {
        if (y > m54)
            y = m54;
    }
    ((AptCIH *)mValue->rva006DCF60(false))->factorySetProperty(0, x, true);
    ((AptCIH *)mValue->rva006DCF60(false))->factorySetProperty(1, y, true);
}
