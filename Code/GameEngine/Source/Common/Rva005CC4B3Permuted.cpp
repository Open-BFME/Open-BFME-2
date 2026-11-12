// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??0Rva005CC656@@QAE@PAX00ABUPageContext@@@Z, retail 0x005cc4b3, 39 bytes. Banked partial (score 0.98) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Complete native factory237 and WB15BF010/936; opaque arguments and
// private virtual declarations are trial ABI views, not admitted contracts.
#include "../../Include/Common/PageContext.h"
class PageBase { public: virtual ~PageBase(); int refs; char state; char padding[3]; };
class Rva005E1FBC : public PageBase {
public:Rva005E1FBC(void *,void *,const PageContext &); virtual ~Rva005E1FBC();
private:void *impl;
};
class Rva005CC656 : public Rva005E1FBC {
public:Rva005CC656(void *,void *,void *,const PageContext &);virtual ~Rva005CC656();
private:void *owner;
};
Rva005CC656::Rva005CC656(void *p,void *a,void *b,const PageContext &pageContext):Rva005E1FBC(a,b,pageContext),owner(p){}
// Exact Rva005CC677 constructor owned by Rva005CC4FBPermuted.cpp.

