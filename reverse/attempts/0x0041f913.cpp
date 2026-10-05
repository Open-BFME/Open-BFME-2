// ??0Rva0041F94A@@QAE@XZ
// partial score=0.99 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /EHsc
struct Rva0041F720HashTag {Rva0041F720HashTag(){}};
struct Rva0041F720EqualTag {Rva0041F720EqualTag(){}};
struct Rva0041F720AllocTag {Rva0041F720AllocTag(){}};
class Rva0041F720TablePrefix {
public:
 Rva0041F720TablePrefix(unsigned int,const Rva0041F720HashTag&,const Rva0041F720EqualTag&,const Rva0041F720AllocTag&);
 ~Rva0041F720TablePrefix();
private: char unknown[20];
};
class Rva0041F8F4Table:public Rva0041F720TablePrefix {
public: Rva0041F8F4Table();
};

class Rva001B4E63CtorPrefix {
public:Rva001B4E63CtorPrefix();virtual ~Rva001B4E63CtorPrefix();
private:char unknown04[8];
};
class Rva0041F94A:public Rva001B4E63CtorPrefix {
public:Rva0041F94A();virtual ~Rva0041F94A();
private:Rva0041F8F4Table table;
};
Rva0041F94A::Rva0041F94A() {}
