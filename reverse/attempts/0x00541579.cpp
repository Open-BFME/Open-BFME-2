// ?rva00541579@Rva00541579@@QAE_NH@Z
// partial score=0.65 date=2026-10-09
// cl: /O1 /Oy- /G7 /arch:SSE /MD /DNDEBUG /EHsc
struct BfmePod28 { int m_00; char frame[24]; };
class Rva00541579 { public: bool rva00541579(int); private: char listener00[16]; BfmePod28 *m_begin10,*m_end14,*capacity18; int m_hint1C; };
BfmePod28 *rva005414C2(BfmePod28 *,BfmePod28 *,const BfmePod28 &);
bool Rva00541579::rva00541579(int key)
{
    if(m_hint1C>=0 && (unsigned)m_hint1C<(unsigned)(m_end14-m_begin10)) {
        int current=m_begin10[m_hint1C].m_00;
        if(key>=current && ((unsigned)(m_hint1C+1)>=(unsigned)(m_end14-m_begin10) || key<m_begin10[m_hint1C+1].m_00))
            return current==key;
    }
    if(m_begin10==m_end14) { m_hint1C=-1; return false; }
    m_hint1C=rva005414C2(m_begin10,m_end14,*reinterpret_cast<const BfmePod28 *>(&key))-m_begin10;
    if((unsigned)m_hint1C>=(unsigned)(m_end14-m_begin10) || (m_hint1C>0 && m_begin10[m_hint1C].m_00!=key))
        --m_hint1C;
    return m_begin10[m_hint1C].m_00==key;
}

