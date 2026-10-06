// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?rva00595A9F@Rva00595A9F@@QAE_NXZ @0x00595A9F 248B evidence: calls rowed 0x00594E07 0x0059534A 0x0059517F plus IAT timeGetTime; offsets 0x54 0x68 0x6a 0x78 0x88 0x17c 0x180 0x184 match Rva00594E07 layout; caller 0x00595D2D
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

class Rva00594E07
{
public:
    unsigned short rva00594E07(unsigned short a, int b);
};

class Rva0059534A
{
public:
    void rva0059534A(unsigned short key);
};

class Rva0059517F
{
public:
    bool rva0059517F(unsigned long a1, unsigned short a2, unsigned short a3, unsigned short a4, bool a5);
};

class Rva00595A9F
{
public:
    bool rva00595A9F();
    bool rva00595B97();
    bool rva0059573C();
    bool rva00595685();
private:
    char m_pad0[4];
    union
    {
        unsigned char m_04;
        unsigned long m_04d;
    };
    char m_pad08[0x0c - 0x08];
    unsigned long m_0c;
    char m_pad10[0x54 - 0x10];
    unsigned long m_54;
    unsigned long m_58;
    char m_pad5c[0x68 - 0x5c];
    unsigned short m_68;
    unsigned short m_6a;
    char m_pad6c[0x78 - 0x6c];
    unsigned short m_78;
    unsigned short m_7a;
    char m_pad7c[0x88 - 0x7c];
    unsigned short m_88;
    char m_pad8a[0x17c - 0x8a];
    unsigned long m_17c;
    unsigned long m_180;
    unsigned long m_184;
    char m_pad188[0x18c - 0x188];
    unsigned long m_18c;
};

bool Rva00595A9F::rva00595A9F()
{
    unsigned short r = ((Rva00594E07 *)this)->rva00594E07(m_88, 0);
    m_78 = r;
    if (r == 0) {
        unsigned long now = timeGetTime();
        if (now - m_180 > m_184) {
            ((Rva0059534A *)this)->rva0059534A(m_68);
            ((Rva0059534A *)this)->rva0059534A(m_6a);
            m_17c = 9;
            return true;
        }
        return false;
    } else {
        unsigned long addr = m_54;
        ((Rva0059517F *)this)->rva0059517F(addr, m_68, m_88, 0x10e2, false);
        ((Rva0059517F *)this)->rva0059517F(addr, m_68, m_88, 0x10e2, false);
        ((Rva0059517F *)this)->rva0059517F(addr, m_68, m_88, 0x10e2, false);
        ++m_88;
        m_180 = timeGetTime();
        m_184 = 0xfa0;
        ((Rva0059517F *)this)->rva0059517F(m_54, m_6a, m_88, 0x10e1, false);
        m_17c = 7;
        return false;
    }
}

bool Rva00595A9F::rva00595B97()
{
    unsigned short r = ((Rva00594E07 *)this)->rva00594E07(m_88, 0);
    m_7a = r;
    if (r == 0) {
        unsigned long now = timeGetTime();
        if (now - m_180 > m_184) {
            ((Rva0059534A *)this)->rva0059534A(m_68);
            ((Rva0059534A *)this)->rva0059534A(m_6a);
        } else {
            return false;
        }
    } else {
        unsigned int combined = (unsigned int)m_78 + m_0c;
        if ((unsigned int)r != combined)
            m_04 |= 0x80;
    }
    m_17c = 9;
    return true;
}

bool Rva00595A9F::rva0059573C()
{
    unsigned short r = ((Rva00594E07 *)this)->rva00594E07((unsigned short)(m_88 + 1), 0);
    m_7a = r;
    if (r == 0) {
        unsigned long now = timeGetTime();
        if (now - m_180 > m_184) {
            m_17c = 9;
            return true;
        }
        return false;
    }
    ((Rva0059534A *)this)->rva0059534A(m_68);
    if (m_7a == m_68) {
        m_04d |= 1;
        m_17c = 9;
        return true;
    }
    m_04d &= ~1u;
    unsigned long f = m_04d;
    if (m_78 == m_7a)
        f |= 2;
    else
        f |= 4;
    m_18c = 0;
    m_88 += 10;
    m_04d = f;
    m_17c = 4;
    return false;
}

bool Rva00595A9F::rva00595685()
{
    unsigned short r = ((Rva00594E07 *)this)->rva00594E07(m_88, 0);
    m_78 = r;
    if (r == 0 || r == m_68)
        goto L_check;
    {
        unsigned long now = timeGetTime();
        m_180 = now;
        m_184 = 0x1770;
        m_7a = 0;
        ((Rva0059517F *)this)->rva0059517F(m_58, m_68, (unsigned short)(m_88 + 1), 0x10e1, false);
        m_17c = 3;
        return false;
    }
L_check:
    if (r == m_68)
        m_0c = 0;
    if (r != 0)
        goto L_cleanup;
    {
        unsigned long now = timeGetTime();
        if (now - m_180 < m_184)
            return false;
    }
L_cleanup:
    if (m_78 == 0)
        timeGetTime();
    ((Rva0059534A *)this)->rva0059534A(m_68);
    m_17c = 9;
    return true;
}
