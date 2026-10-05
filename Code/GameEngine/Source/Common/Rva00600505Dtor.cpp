// cl: /O1 /MD /EHsc
// ??1Rva00600505@@UAE@XZ @0x00600505 11B
// Virtual dtor: stores vtable 0x0087A64C then tail-jmps to pinned base dtor 0x005FEF65.
// Evidence: pin names the dtor; deleting dtor 0x00600510 calls it; vtable 0x00C7A64C slot0; base vtable 0x00C7A464.
class Rva005FEF65
{
public:
	virtual ~Rva005FEF65();
};

class Rva00600505 : public Rva005FEF65
{
public:
	virtual ~Rva00600505();
};

Rva00600505::~Rva00600505()
{
}
