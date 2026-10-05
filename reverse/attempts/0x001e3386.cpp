// ??0Rva001E3386Map@@QAE@XZ
// partial score=0.9 date=2026-10-05
// cl: /O1 /MD /GX /DNDEBUG
// [1E3386,1E33A5),31B. Native construction takes100 buckets and
// three references to the same empty policy object. Full64B1E2F8E
// reads only bucket count; the three empty policies carry no state.
struct H{H(){}};struct E{E(){}};struct A{A(){}};
class Rva001E3386Map {
 unsigned words[5];
public:
 Rva001E3386Map();
 void initialize(unsigned,const H&,const E&,const A&);
};
Rva001E3386Map::Rva001E3386Map() {
 initialize(100,H(),E(),A());
}
