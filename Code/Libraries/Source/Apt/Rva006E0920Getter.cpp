// cl: /MD
// ?rva006E0920@Rva006E0920@@QBEMH@Z, retail 0x006E0920, 13 bytes.
// Float-array indexed getter at +0x44.
// Evidence: leaf with 3 callers at 0x006F2716/0x006F2729/0x006F273C;
// same /O2 shape as Apt neighbours.
class Rva006E0920 {
    unsigned char _pad[0x44];
    float *m_44;
public:
    float rva006E0920(int i) const;
};
float Rva006E0920::rva006E0920(int i) const
{
    return m_44[i];
}
