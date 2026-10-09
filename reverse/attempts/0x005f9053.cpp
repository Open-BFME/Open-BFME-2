// ?loaded@Rva005F8FEE@@QAEXPBD@Z
// partial score=0.96 date=2026-10-10
// cl: /O1 /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
struct TargetRef00217D4C { virtual void *destroy(unsigned); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct Rva005FEAAFSourceRef {
 TargetRef00217D4C *m_ptr;
 ~Rva005FEAAFSourceRef() { if(m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
struct TreeHintRef00217D4C {
 TargetRef00217D4C *m_ptr;
 TreeHintRef00217D4C() : m_ptr(0) {}
 TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &);
 TreeHintRef00217D4C(const Rva005FEAAFSourceRef &value) : m_ptr(value.m_ptr) { if(m_ptr) ++m_ptr->references; }
 ~TreeHintRef00217D4C() { if(m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
class Rva005FEAAFHost {
public:
 virtual void v0(); virtual void v1();
 virtual Rva005FEAAFSourceRef createRaw(int level, const AsciiString &name);
 TreeHintRef00217D4C create(int level, const AsciiString &name);
};
class Rva002BED91 { public: void clear(); };
namespace AptUtils { const char *SkipLevelN(const char *); int LevelIndexFromTarget(const char *); }
struct Rva0052413E { char storage[12]; ~Rva0052413E(); };
class Rva005F8FEEBase { public: virtual ~Rva005F8FEEBase() {} };
class Rva005F8FEE : public Rva005F8FEEBase {
public: virtual ~Rva005F8FEE(); void loaded(const char *);
 int m_04,m_08; AsciiString m_str0C; int m_10,m_14;
 TreeHintRef00217D4C m_holder18;
 Rva0052413E m_vec1C;
 int m_28;
 TreeHintRef00217D4C m_holder2C;
};
Rva005F8FEE::~Rva005F8FEE() {}
void Rva005F8FEE::loaded(const char *path)
{
 if (!m_28 && !m_holder2C.m_ptr && m_holder18.m_ptr) {
  { AsciiString name(AptUtils::SkipLevelN(path));
  Rva005FEAAFHost *host = (Rva005FEAAFHost *)m_holder18.m_ptr;
  m_holder2C = host->create(AptUtils::LevelIndexFromTarget(path), name);
  }
  ((Rva002BED91 *)&m_holder18)->clear();
  m_28 = 1;
 }
}
