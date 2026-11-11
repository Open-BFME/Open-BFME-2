// cl: /O1 /arch:SSE /G7 /GX /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /DBFME_SNAPSHOT_NAME_SLOT
// stlport
// CastleBehaviorModuleData: native factory24AA99, ctor39A027 and table C1A858.
// The address-named member/base types are structural views; their original
// source names remain unknown. See reverse/attempt_support/castle-39a027-link-20261019.md.
class INI;
class MultiIniFieldParse;
#include <vector>
#include <map>
#include "ascii_string.h"

class Rva002618A2
{
public:
    Rva002618A2 *rva002618FA(int, int, int, int, int, int);
protected:
    unsigned m_words[7];
};
#include "../../../../Include/GameLogic/Module/Rva00045411BitSet.h"
#include "../../../../Include/Common/BfmeFixedStorage0004543D.h"
template <int N> class BitFlags;
// Existing seven-dword zero-mask provider at native DFEFA4.
extern BitFlags<116> KINDOFMASK_NONE;
#include "../../../../Include/GameLogic/Module/Rva003623E5Member.h"
struct RvaPair0039973B { AsciiString m_key; int m_value; ~RvaPair0039973B() {} };
struct Rva00395D77 { unsigned char m_bytes[12]; ~Rva00395D77(); };
struct FXBoneInfo { AsciiString m_boneName; const void *m_particleSystemTemplate; };
class Rva0039597C;
#include "../../../../../Libraries/Source/WWVegas/WWLib/Rva00399800.h"
namespace _STL {
template <> vector<FXBoneInfo>::iterator vector<FXBoneInfo>::erase(iterator, iterator);
template <> inline void vector<RvaPair0039973B>::clear()
{
    ((vector<FXBoneInfo> *)this)->erase((FXBoneInfo *)this->_M_start, (FXBoneInfo *)this->_M_finish);
}
template <> inline void vector<Rva00395D77>::clear()
{
    ((Rva00399800 *)this)->rva003997CD((Rva0039597C *)this->_M_start, (Rva0039597C *)this->_M_finish);
}
}
struct BfmeStringRecord004071F7 { AsciiString m_templateName; unsigned m_count1, m_count2; };
class Rva00397C94 : public _STL::map<int, BfmeStringRecord004071F7>
{ public: ~Rva00397C94(); void rva00398257(); };
#include "Common/Snapshot.h"
class __declspec(novtable) Rva0039A027Base : public Snapshot
{
public:
    __forceinline Rva0039A027Base() : m_f08(0.0f), m_n0c(0)
    {}
    virtual ~Rva0039A027Base() {}
    virtual void loadPostProcess() {}
    virtual const char *GetSnapshotName() const { return "ModuleData"; }
    virtual void xfer(Xfer *) {}
    virtual bool slot04() const { return false; }
    virtual bool slot05() const { return false; }
    virtual bool slot06() const { return false; }
    virtual bool slot07() const { return false; }
    virtual bool slot08() const { return false; }
    virtual bool slot09() const { return false; }
    virtual bool slot10() const { return false; }
    virtual bool slot11() const { return false; }
    virtual bool slot12() const { return false; }
    virtual bool slot13() const { return false; }
    virtual AsciiString slot14(int) const { return AsciiString::TheEmptyString; }
    virtual bool slot15() const { return false; }
    virtual const void *slot16() const { return 0; }
    virtual const void *slot17() const { return 0; }
    virtual const void *slot18() const { return 0; }
    virtual const void *slot19() const { return 0; }
    virtual const void *slot20() const { return 0; }
    virtual const void *slot21() const { return 0; }
    virtual const void *slot22() const { return 0; }
    virtual const void *slot23() const { return 0; }
    virtual const void *slot24() const { return 0; }
    virtual const void *slot25() const { return 0; }
    virtual const void *slot26() const { return 0; }
    virtual const void *slot27() const { return 0; }
    virtual const void *slot28() const { return 0; }
    virtual const void *slot29() const { return 0; }
    virtual bool slot30() const { return true; }
private:
    unsigned m_unknown04;
    float m_f08;
    unsigned m_n0c;
};
class __declspec(novtable) CastleBehaviorModuleData : public Rva0039A027Base
{
public:
    CastleBehaviorModuleData();
    static void buildFieldParse(MultiIniFieldParse &parse);
    static void rva0039981E(INI *, void *, void *, const void *);
    virtual ~CastleBehaviorModuleData();
    virtual bool slot05() const { return true; }
    virtual const void *slot27() const { return this; }
private:
    AsciiString m_str10, m_str14;
    float m_f18, m_f1c, m_f20, m_f24, m_f28, m_f2c;
    Rva003623E5Member m_filter30, m_filter34;
    int m_n38;
    bool m_b3c, m_b3d, m_b3e;
    int m_n40, m_n44, m_n48, m_n4c;
    _STL::vector<RvaPair0039973B> m_vec50;
    _STL::vector<Rva00395D77> m_vec5c;
    Rva00397C94 m_map68;
    bool m_b74, m_b75;
};
// Native 39A1CA has no derived-vptr installation; the constructor TU
// emits the complete C1A858 table. Both views have the same fields and slots.
CastleBehaviorModuleData::~CastleBehaviorModuleData() {}

typedef char CastleDataSize[(sizeof(CastleBehaviorModuleData) == 0x78) ? 1 : -1];
