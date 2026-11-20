// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// EH dtor at 0x00502D03 destroys its three members in reverse declaration
// order: +0x1C, +0x10, then +0x04. Their destructor bodies are rowed elsewhere.
class Rva004FF408
{
public:
    ~Rva004FF408();
private:
    unsigned char m_pad[4];
};

class Rva00502D48
{
public:
    Rva00502D48();
    ~Rva00502D48();
private:
    char m_opaque[0x0C];
};

class Rva004FFE96
{
public:
    Rva004FFE96();
    ~Rva004FFE96();
private:
    char m_opaque[0x0C];
};

class Rva00502D03
{
public:
    ~Rva00502D03();
private:
    unsigned char m_pad00[0x04];
    Rva00502D48 m_member04;
    Rva004FFE96 m_member10;
    Rva004FF408 m_member1C;
};

Rva00502D03::~Rva00502D03()
{
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x005029CA reads ??1?$_Rb_tree@HU?$pair@$$CBHURva00501776@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva00501776@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva00501776@@@_STL@@@2@@_STL@@QAE@XZ
#pragma comment(linker, "/alternatename:??1Rva00502D48@@QAE@XZ=??1?$_Rb_tree@HU?$pair@$$CBHURva00501776@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva00501776@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva00501776@@@_STL@@@2@@_STL@@QAE@XZ")
//   0x0050298D reads ??1?$_Rb_tree@HU?$pair@$$CBHURva00501656@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva00501656@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva00501656@@@_STL@@@2@@_STL@@QAE@XZ
#pragma comment(linker, "/alternatename:??1Rva004FFE96@@QAE@XZ=??1?$_Rb_tree@HU?$pair@$$CBHURva00501656@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva00501656@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva00501656@@@_STL@@@2@@_STL@@QAE@XZ")
//   0x004FF630 reads ??1Rva004FF408@@QAE@XZ
