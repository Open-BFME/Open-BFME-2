// cl: /EHs /MD /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva004E3CD0@@UAE@XZ @ 0x004E3CD0 (72B). Virtual dtor: vtable 0x00862054,
// cleanup this->rva004E2199 (row Code/.../Rva003EF14ADtor.cpp), then vector
// at +0x14 (row 0x004E3C32) and RvaVec at +4 (pin 0x002B80CE). Callers
// 0x004E3E09 and derived tail-jmps 0x004E3D30/0x004E3D47 prove base. Layout
// mirrors Rva004E2E58Value (unknown04 = RvaVec, begin/end/storage = vector,
// flag20) which is why the cleanup call uses ecx=this.
#include <vector>

class RvaVec002B80CE
{
public:
    ~RvaVec002B80CE();
private:
    char m_pad[16];
};

class Rva004E2382
{
public:
    ~Rva004E2382();
private:
    char m_pad[32];
};

typedef _STL::vector<Rva004E2382, _STL::allocator<Rva004E2382> > Rva004E2382Vec;

class Rva004E2E58Value
{
public:
    void rva004E2199();
};

#include "ascii_string.h"

class Rva002D3627Host;
extern Rva002D3627Host *g_00DFEF18;
class Rva0021294A;
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;


class Rva003EEC63
{
public:
    void rva003EEC63(void *p, AsciiString s, int a, int b);
};

class Rva0021294A
{
public:
    char m_pad[0x268];
    Rva003EEC63 *m_268;
};

static __forceinline Rva003EEC63 *treePayloadContext() {
    return reinterpret_cast<Rva0021294A *>(TheLivingWorldManager)->m_268;
}

#include "Lib/Coord3D.h"

class Rva000C0513
{
public:
    void rva004E38B9(unsigned int n);
    void rva000C0513(unsigned int n, Coord3D val);
};

class Rva004E3A6EObj
{
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22();
    virtual void slot5c(int a, float b);
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual unsigned slot70();
    virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
    virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38();
    virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48();
    virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53();
    virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58();
    virtual void v59(); virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
    virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67(); virtual void v68();
    virtual void v69(); virtual void v70(); virtual void v71(); virtual void v72(); virtual void v73();
    virtual void v74(); virtual void v75(); virtual void v76(); virtual void v77(); virtual void v78();
    virtual void v79(); virtual void v80(); virtual void v81(); virtual void v82(); virtual void v83();
    virtual void v84(); virtual void v85(); virtual void v86(); virtual void v87(); virtual void v88();
    virtual void v89(); virtual void v90(); virtual void v91(); virtual void v92(); virtual void v93();
    virtual void v94(); virtual void v95(); virtual void v96(); virtual void v97(); virtual void v98();
    virtual void v99(); virtual void v100(); virtual void v101(); virtual void v102(); virtual void v103();
    virtual void v104(); virtual void v105(); virtual void v106(); virtual void v107(); virtual void v108();
    virtual void slot1b4(int a);
    virtual void v110();
    virtual void slot1bc(int a);
};

struct Rva004E3A6EInnerVec
{
    Coord3D *m_start;
    Coord3D *m_finish;
    Coord3D *m_end;
};

struct Rva004E3A6ERec
{
    AsciiString m_00;
    Rva004E3A6EObj *m_04;
    char m_08[12];
    Rva004E3A6EInnerVec m_inner;
};

struct Rva004E3A6EOuterVec
{
    Rva004E3A6ERec *m_start;
    Rva004E3A6ERec *m_finish;
    Rva004E3A6ERec *m_end;
};


class Rva004E3CD0
{
public:
    virtual ~Rva004E3CD0();
    void rva004E3A6E();
private:
    RvaVec002B80CE m_04;
    Rva004E2382Vec m_14;
    bool m_20;
    bool m_21;
    bool m_22;
    char m_pad23;
    float m_24;
};

Rva004E3CD0::~Rva004E3CD0()
{
    ((Rva004E2E58Value *)this)->rva004E2199();
}

// Native266B reset4E3A6E..4E3B78; fields+21/+22/+24 from the existing ctor
// and retail accesses. Record and owner types remain address-derived.
void Rva004E3CD0::rva004E3A6E()
{
    Rva004E3A6EOuterVec &entries=reinterpret_cast<Rva004E3A6EOuterVec &>(m_14);
    if (!m_22) {
        void *host = g_00DFEF18;
        if (host && ((char *)host)[0x19])
            return;
    }
    ((Rva004E2E58Value *)this)->rva004E2199();
    for (Rva004E3A6ERec *rec = entries.m_start; rec != entries.m_finish; ++rec) {
        if (TheLivingWorldManager)
            treePayloadContext()->rva003EEC63(&rec->m_04, rec->m_00, 0, 1);
        if (rec->m_04) {
            rec->m_04->slot1bc(1);
            rec->m_04->slot1b4(1);
            rec->m_04->slot5c(1, m_24);
            Rva004E3A6EInnerVec *inner = &rec->m_inner;
            unsigned n = rec->m_04->slot70();
            ((Rva000C0513 *)inner)->rva004E38B9(n);
            unsigned i = 0;
            Coord3D one;
            one.x = 1.0f;
            one.y = 1.0f;
            one.z = 1.0f;
            for (; i < (unsigned)(rec->m_inner.m_finish - inner->m_start); ++i)
                rec->m_inner.m_start[i] = one;
        }
    }
}
