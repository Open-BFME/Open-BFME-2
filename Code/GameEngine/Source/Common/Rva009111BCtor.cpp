// cl: /O1 /MD
// ??0Rva009111B@@QAE@HHH@Z retail 0x00090781 32B
// Derived ctor forwards 3 ints to rowed base ??0Rva00689320@@QAE@HHH@Z then sets vtable 0x007C7EA8.
// Evidence: vtable store matches dtor 0x0009111B; base call 0x00689320 rowed; ret 0xc; unblocks 0x0004C585.
class Rva00689320
{
public:
	virtual ~Rva00689320();
	Rva00689320(int a1, int a2, int a3);
};

class Rva009111B : public Rva00689320
{
public:
	virtual ~Rva009111B();
	Rva009111B(int a1, int a2, int a3);
};

Rva009111B::Rva009111B(int a1, int a2, int a3) : Rva00689320(a1, a2, a3)
{
}
