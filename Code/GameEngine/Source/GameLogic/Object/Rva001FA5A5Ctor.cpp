// cl: /O1 /MD
// ??0Rva001FA5A5@@QAE@XZ @0x001FA5A5 22B and its ctor chain, same shape as
// Rva001FA584Ctor.cpp (zeroed ints then an embedded member ctor). Member ctor
// callees by REL32: 001FA5A5 -> rowed Rva001F9060 at +8; 001FB8A9 ->
// 001FA5A5 at +4; 001FBA45 -> 001FA5A5 at +8; 001FBBE4 -> 001FBA45 at +4;
// 001F9B52 -> rowed ObjectCreationList at +4. Original names unknown so
// address-derived Rva names are used.
class ObjectCreationList
{
public:
    ObjectCreationList();
};

class Rva001F9060
{
public:
    Rva001F9060();
};

class Rva001FA5A5
{
public:
    int m_00;
    int m_04;
    Rva001F9060 m_08;
    Rva001FA5A5();
};

Rva001FA5A5::Rva001FA5A5() : m_00(0), m_04(0), m_08()
{
}

class Rva001FB8A9
{
public:
    int m_00;
    Rva001FA5A5 m_04;
    Rva001FB8A9();
};

Rva001FB8A9::Rva001FB8A9() : m_00(0), m_04()
{
}

class Rva001FBA45
{
public:
    int m_00;
    int m_04;
    Rva001FA5A5 m_08;
    Rva001FBA45();
};

Rva001FBA45::Rva001FBA45() : m_00(0), m_04(0), m_08()
{
}

class Rva001FBBE4
{
public:
    int m_00;
    Rva001FBA45 m_04;
    Rva001FBBE4();
};

Rva001FBBE4::Rva001FBBE4() : m_00(0), m_04()
{
}

class Rva001F9B52
{
public:
    int m_00;
    ObjectCreationList m_04;
    Rva001F9B52();
};

Rva001F9B52::Rva001F9B52() : m_00(0), m_04()
{
}
