// cl: /MD /EHsc
// ??1Rva005F6A58@@UAE@XZ retail 0x005F6A58 56 bytes.
// Evidence: chain lane calls helper 0x005F697C then base dtor 0x005F6941 plus vtable at this plus caller 0x005F6B3C.
// Model: virtual dtor over rowed base Rva005F6941 with helper call via cast.
class Rva005F697C
{
public:
	void rva005F697C();
};

class Rva005F6941
{
public:
	virtual ~Rva005F6941();
};

class Rva005F6A58 : public Rva005F6941
{
public:
	virtual ~Rva005F6A58();
};

Rva005F6A58::~Rva005F6A58()
{
	((Rva005F697C *)this)->rva005F697C();
}
