// cl: /O1 /MD
// ??1Rva003ABC0B@@UAE@XZ @0x003ABC0B 22B
// Leaf dtor restoring one vptr at +0x1c with null-guarded store then tail-jmp
// to rowed base ??1Rva003AEEB3 0x003A5817. Evidence: neg sbb and idiom matches
// sibling Rva003A5817Dtor plus V3InlineTemplateDtor; caller ??_G deleting dtor.
extern const void *const g_00BBB554[];
class Rva003AEEB3
{
public:
	virtual ~Rva003AEEB3();
};
class __declspec(novtable) Rva003ABC0B : public Rva003AEEB3
{
public:
	virtual ~Rva003ABC0B();
};
Rva003ABC0B::~Rva003ABC0B()
{
	unsigned char *b1C = this ? (unsigned char *)this + 0x1C : 0;
	*(volatile unsigned int *)b1C = (unsigned int)g_00BBB554;
}
