// ??0Rva005CC656@@QAE@PAX00ABUPageContext@@@Z
// partial score=0.98 date=2026-10-08
// cl: /O1 /DNDEBUG /MD /EHsc
// Complete native factory237 and WB15BF010/936; opaque arguments and
// private virtual declarations are trial ABI views, not admitted contracts.
struct PageContext {
 void *region; void *page; void *owner;
 PageContext(void *r,void *p,void *o):region(r),page(p),owner(o){}
};
class PageBase { public: virtual ~PageBase(); int refs; char state; char padding[3]; };
class Rva005E1FBC : public PageBase {
public:Rva005E1FBC(void *,void *,const PageContext &); virtual ~Rva005E1FBC();
private:void *impl;
};
class Rva005E21EB : public PageBase {
public:Rva005E21EB(void *,void *,const PageContext &);virtual ~Rva005E21EB();
private:void *impl;
};
class Rva005E362F : public PageBase {
public:Rva005E362F(void *,void *,void *);virtual ~Rva005E362F();
private:void *impl;
};
class Rva005CC656 : public Rva005E1FBC {
public:Rva005CC656(void *,void *,void *,const PageContext &);virtual ~Rva005CC656();
private:void *owner;
};
class Rva005CC677 : public Rva005E21EB {
public:Rva005CC677(void *,void *,void *,const PageContext &);virtual ~Rva005CC677();
private:void *owner;
};
Rva005CC656::Rva005CC656(void *p,void *a,void *b,const PageContext &c):Rva005E1FBC(a,b,c),owner(p){}
Rva005CC677::Rva005CC677(void *p,void *a,void *b,const PageContext &c):Rva005E21EB(a,b,c),owner(p){}

