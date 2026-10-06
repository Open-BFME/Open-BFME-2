// cl: /O1 /MD /EHsc
// class-gate: allow StringBase private validate for row ?validate@?$StringBase@G@@ABEXXZ at 0x000B3FD0
// Twelve 17B member forwarders of one shape (see Rva005E21EBDtor.cpp's
// rva005E25CD): call a folded base helper on this then tail-jump into a
// member call on the object pointer held at +8 or +0xC. Base helpers by REL32:
// 0x000B3FD0 ?init@SmudgeManager@@UAEXXZ and 0x00248D08
// ?markAsOverride@Overridable@@QAEXXZ and 0x00420B2A
// ?disable@Rva00420B2AZeroSetter@@QAEXXZ (all rowed and folded). The jump
// targets are unrowed and arrive as address-derived pins. Original names are
// unknown so address-derived Rva names are used throughout.
class SmudgeManager
{
public:
    virtual void init();
};
class Overridable
{
public:
    void markAsOverride();
};
class Rva00420B2AZeroSetter
{
public:
    void disable();
};
class Rva005D13C2
{
public:
    void rva005D13C2();
};
class Rva005D1516
{
public:
    void rva005D1516();
private:
    char m_pad[0x8];
    Rva005D13C2 *m_08;
};
void Rva005D1516::rva005D1516()
{
    ((SmudgeManager *)this)->SmudgeManager::init();
    m_08->rva005D13C2();
}
class Rva005E18D0
{
public:
    void rva005E18D0();
};
class Rva005E1906
{
public:
    void rva005E1906();
private:
    char m_pad[0xC];
    Rva005E18D0 *m_0C;
};
void Rva005E1906::rva005E1906()
{
    ((Overridable *)this)->markAsOverride();
    m_0C->rva005E18D0();
}
class Rva005E18DC
{
public:
    void rva005E18DC();
};
class Rva005E1917
{
public:
    void rva005E1917();
private:
    char m_pad[0xC];
    Rva005E18DC *m_0C;
};
void Rva005E1917::rva005E1917()
{
    ((Rva00420B2AZeroSetter *)this)->disable();
    m_0C->rva005E18DC();
}
class Rva005E1B9A
{
public:
    void rva005E1B9A();
};
class Rva005E1BC4
{
public:
    void rva005E1BC4();
private:
    char m_pad[0xC];
    Rva005E1B9A *m_0C;
};
void Rva005E1BC4::rva005E1BC4()
{
    ((SmudgeManager *)this)->SmudgeManager::init();
    m_0C->rva005E1B9A();
}
class Rva005E2180
{
public:
    void rva005E2180();
};
class Rva005E2226
{
public:
    void rva005E2226();
private:
    char m_pad[0xC];
    Rva005E2180 *m_0C;
};
void Rva005E2226::rva005E2226()
{
    ((Rva00420B2AZeroSetter *)this)->disable();
    m_0C->rva005E2180();
}
class Rva005E254C
{
public:
    void rva005E254C();
};
class Rva005E25DE
{
public:
    void rva005E25DE();
private:
    char m_pad[0xC];
    Rva005E254C *m_0C;
};
void Rva005E25DE::rva005E25DE()
{
    ((SmudgeManager *)this)->SmudgeManager::init();
    m_0C->rva005E254C();
}
class Rva005F1B51
{
public:
    void rva005F1B51();
};
class Rva005E35C9
{
public:
    void rva005E35C9();
private:
    char m_pad[0xC];
    Rva005F1B51 *m_0C;
};
void Rva005E35C9::rva005E35C9()
{
    ((SmudgeManager *)this)->SmudgeManager::init();
    m_0C->rva005F1B51();
}
class Rva005E69AC
{
public:
    void rva005E69AC();
};
class Rva005E6A00
{
public:
    void rva005E6A00();
private:
    char m_pad[0x20];
    Rva005E69AC *m_20;
};
void Rva005E6A00::rva005E6A00()
{
    ((SmudgeManager *)this)->SmudgeManager::init();
    m_20->rva005E69AC();
}
class Rva005E6A9D
{
public:
    void rva005E6A9D();
};
class Rva005E6BA3
{
public:
    void rva005E6BA3();
private:
    char m_pad[0x20];
    Rva005E6A9D *m_20;
};
void Rva005E6BA3::rva005E6BA3()
{
    ((SmudgeManager *)this)->SmudgeManager::init();
    m_20->rva005E6A9D();
}
class Rva005E6AD8
{
public:
    void rva005E6AD8();
};
class Rva005E6BB4
{
public:
    void rva005E6BB4();
private:
    char m_pad[0x20];
    Rva005E6AD8 *m_20;
};
void Rva005E6BB4::rva005E6BB4()
{
    ((SmudgeManager *)this)->SmudgeManager::init();
    m_20->rva005E6AD8();
}
// 0x005E590F is rowed as ?step@Rva005E590F@@QAEXXZ (RvaHelperMemberSteps.cpp).
class Rva005E590F
{
public:
	void step();
};
template <typename T> class StringBase
{
	friend class Rva005CDDF0;
	void validate() const;
};
class Rva005CDDF0
{
public:
	void rva005CDDF0();
};
void Rva005CDDF0::rva005CDDF0()
{
	((Rva005E590F *)this)->step();
	((StringBase<unsigned short> *)((char *)this + 0xc))->validate();
}
