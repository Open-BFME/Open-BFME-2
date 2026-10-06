// cl: /MD
// ??1Rva00257464@@QAE@XZ @0x00257464 5B
// Novtable empty dtor tail-jumping to the pinned base dtor at 0x002572D7.
// Evidence: 5B jmp; callers are Unwind funclets; neighbours are record/blog.
struct Rva002572D7Member
{
public:
	~Rva002572D7Member();
};
struct __declspec(novtable) Rva00257464 : public Rva002572D7Member
{
	~Rva00257464();
};
Rva00257464::~Rva00257464()
{
}
