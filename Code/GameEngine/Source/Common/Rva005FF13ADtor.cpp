// cl: /O1 /MD /EHsc
// ??1Rva005FF13A@@UAE@XZ @0x005FF13A 11B
// Virtual dtor: stores vtable 0x0087A478 then tail-jmps to rowed base dtor 0x005FEF65.
// Evidence: pin names the dtor; deleting dtor 0x005FF145 calls it; vtable 0x00C7A478 slot0; base vtable 0x00C7A464.
class Rva005FEF65
{
public:
	virtual ~Rva005FEF65();
};

class Rva005FF13A : public Rva005FEF65
{
public:
	virtual ~Rva005FF13A();
};

Rva005FF13A::~Rva005FF13A()
{
}
