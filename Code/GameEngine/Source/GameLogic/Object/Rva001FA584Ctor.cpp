// cl: /MD
// ??0Rva001FA584@@QAE@XZ @0x001FA584 19B
// ??0Rva001FA94B@@QAE@XZ @0x001FA94B 15B
// ??0Rva001FBAD8@@QAE@XZ @0x001FBAD8 22B
// ??0Rva001FBC8F@@QAE@XZ @0x001FBC8F 18B
// ??0Rva001FB93D@@QAE@XZ @0x001FB93D 18B
// ??0Rva001FC0A0@@QAE@XZ @0x001FC0A0 22B
// Unnamed ctor initializing int at +4 to 0 and inline ObjectCreationList at +8.
// Evidence: ret with no stack args; callee ObjectCreationList ctor 0x001F81BF rowed;
// callers 0x001FA94B and 0x001FB93D and 0x001FBAD8 become ready; honest Rva name.
// Rva001FA94B wraps Rva001FA584 at +4; chain lane after landing 0x001FA584.
class ObjectCreationList
{
public:
    ObjectCreationList();
};

class Rva001FA584
{
public:
    int m_00;
    int m_04;
    ObjectCreationList m_08;
    Rva001FA584();
};

Rva001FA584::Rva001FA584() : m_04(0)
{
}

class Rva001FA94B
{
public:
    int m_00;
    Rva001FA584 m_04;
    Rva001FA94B();
};

Rva001FA94B::Rva001FA94B() : m_04()
{
}

class Rva001FBAD8
{
public:
    int m_00;
    int m_04;
    int m_08;
    Rva001FA584 m_0C;
    Rva001FBAD8();
};

Rva001FBAD8::Rva001FBAD8() : m_00(0), m_04(0), m_0C()
{
}

class Rva001FBC8F
{
public:
    int m_00;
    Rva001FBAD8 m_04;
    Rva001FBC8F();
};

Rva001FBC8F::Rva001FBC8F() : m_00(0), m_04()
{
}

class Rva001FB93D
{
public:
    int m_00;
    int m_04;
    Rva001FA584 m_08;
    Rva001FB93D();
};

Rva001FB93D::Rva001FB93D() : m_00(0), m_08()
{
}

class Rva001FC0A0
{
public:
    int m_00;
    int m_04;
    Rva001FBAD8 m_08;
    Rva001FC0A0();
};

Rva001FC0A0::Rva001FC0A0() : m_00(0), m_04(0), m_08()
{
}
