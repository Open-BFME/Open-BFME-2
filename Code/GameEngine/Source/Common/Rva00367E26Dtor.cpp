// cl: /O1 /DNDEBUG /MD
// ??1Rva00367E26@@UAE@XZ @0x00367E26 11B
// Virtual dtor stores vtable 0x00C17600 then tail-jmps to pinned base dtor
// 0x003516F3. Evidence: deleting dtor 0x00367E0A calls this address with
// vtable 0x00C17600 slot 0; base pinned from deleting dtor 0x00352B25.
class Rva003516F3
{
public:
	virtual ~Rva003516F3();
};
class Rva00367E26 : public Rva003516F3
{
public:
	virtual ~Rva00367E26();
};
Rva00367E26::~Rva00367E26()
{
}
