// cl: /O1 /MD /EHsc
// Native 5E66A4..5E66DF is the destructor of the independently rowed
// Rva005E663C constructor's owning wrapper: vptr C77E04, owned slot +8,
// member cleanup5E6253 and base cleanup5E6810. The base provider is the
// existing MemberBaseDtorsB01.cpp ABI view and pin; no new alias is added.
// This view covers the same twelve-byte prefix as the constructor unit,
// with inherited vptr, the +4 held word and the +8 owning slot. Full class
// identity remains unresolved. BF1 FileSystem destructor supplies the
// member-then-base algorithm only; its tree member / class name are refuted.
// Donor revision9cbfb551fe20dae985f91f2319d8997287b6a705.
class Rva005E6810 {public:virtual ~Rva005E6810();};
class Rva005E6253 {public:void clear();};
class Rva005E663C : public Rva005E6810 {public:virtual ~Rva005E663C();private:void *held;void *owned;};
Rva005E663C::~Rva005E663C() { ((Rva005E6253*)&owned)->clear(); }
