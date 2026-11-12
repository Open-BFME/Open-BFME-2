// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??0Rva005CC677@@QAE@PAX00ABUPageContext@@@Z, retail 0x005cc4fb, 39 bytes. Banked partial (score 0.98) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Complete native factory237 and WB15BF010/936; opaque arguments and
// private virtual declarations are trial ABI views, not admitted contracts.
#include "../../Include/Common/PageContext.h"
class PageBase { public: virtual ~PageBase(); int refs; char state; char padding[3]; };
class Rva005E21EB : public PageBase {
public:Rva005E21EB(void *,void *,const PageContext &);virtual ~Rva005E21EB();
private:void *impl;
};
class Rva005CC677 : public Rva005E21EB {
public:Rva005CC677(void *,void *,void *,const PageContext &);virtual ~Rva005CC677();
private:void *owner;
};
// Exact Rva005CC656 constructor owned by Rva005CC4B3Permuted.cpp.
Rva005CC677::Rva005CC677(void *p,void *a,void *b,const PageContext &pageContext):Rva005E21EB(a,b,pageContext),owner(p){}

