// cl: /O1 /MD
// ??1Rva0046468D@@QAE@XZ @0x0046468D 5B: novtable empty dtor tail-jmp to rowed base ??1Rva00463782; evidence jmp-only plus Unwind callers plus neighbour OpenContainDtor.
class Rva00463782
{
public:
	~Rva00463782();
};

class __declspec(novtable) Rva0046468D : public Rva00463782
{
public:
	~Rva0046468D();
};

Rva0046468D::~Rva0046468D()
{
}
