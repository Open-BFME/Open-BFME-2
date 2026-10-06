// cl: /DNDEBUG /MD /EHsc /Oy-
// ?rva00275376@Rva00275376@@QAE_NHHHHHH@Z @0x00275376 168B evidence: caller 0x0028E1EB 0x002C9F94; callee 0x00271C8A rowed; next Drawable TU

class Rva00271C8A
{
public:
    void rva00271C8A(const int *a, const int *b);
private:
    int m_vals[19];
};

struct Slot00Holder
{
    virtual void slot00(Rva00271C8A *a, int b, int c);
};

struct SlotA8Holder
{
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
    virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
    virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
    virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
    virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
    virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6C();
    virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
    virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8C();
    virtual void slot90(); virtual void slot94(); virtual void slot98(); virtual void slot9C();
    virtual void slotA0(); virtual void slotA4();
    virtual void *slotA8();
};

struct Slot18Holder
{
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
    virtual void slot10(); virtual void slot14();
    virtual bool slot18(Rva00271C8A *a, int b, int c, int d, int e, int f, int g);
};

class Rva00270644
{
public:
    void rva00270644(float a, float b);
};

class Drawable
{
public:
    void rva00272BE7();
};

class Rva00275376
{
public:
    bool rva00275376(int a0, int a1, int a2, int a3, int a4, int a5);
    void rva002752F8();
private:
    char m_pad0[0x14C];
    SlotA8Holder **m_14C;
    char m_pad150[0x8];
    Slot00Holder **m_158;
    Slot00Holder **m_15C;
    char m_pad160[0xF8];
    Rva00271C8A m_258;
    int m_2A4[19];
    int m_2F0[19];
    char m_pad33C[0x107];
    bool m_443;
    char m_pad444;
    bool m_445;
    bool m_446;
};

bool Rva00275376::rva00275376(int a0, int a1, int a2, int a3, int a4, int a5)
{
    if (m_443) {
        m_258.rva00271C8A(m_2A4, m_2F0);
        Slot00Holder **end = m_15C;
        Slot00Holder **it = m_158;
        if (it != end) {
            do {
                (*it)->slot00(&m_258, 0, 0);
                ++it;
            } while (it != end);
        }
        m_443 = false;
    }
    SlotA8Holder **arr = m_14C;
    for (;;) {
        SlotA8Holder *obj = *arr;
        if (obj != 0) {
            void *p = obj->slotA8();
            if (p != 0) {
                Slot18Holder *h = (Slot18Holder *)p;
                if (h->slot18(&m_258, a0, a1, a2, a3, a4, a5))
                    return true;
            }
            ++arr;
        } else {
            return false;
        }
    }
}

void Rva00275376::rva002752F8()
{
    ((Rva00270644 *)this)->rva00270644(0.0f, -0.03f);
    ((Drawable *)this)->rva00272BE7();
    if (m_445) {
        m_445 = false;
        m_446 = true;
    }
}
