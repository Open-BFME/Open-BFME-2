// cl: /O1 /DNDEBUG /MD
// ??1Rva0043DABD@@UAE@XZ @0x0043DABD 11B
// Evidence: chain dtor stores vtable 0x0083D954 then tail-jmps to rowed base 0x0057EE5C. Callers 0x0043DAEE plus unwind funclets. Prev 0x0043DA65 next 0x0043DAE0.
class Rva0057EE5C
{
public:
	virtual ~Rva0057EE5C();
};

class Rva0043DABD : public Rva0057EE5C
{
public:
	virtual ~Rva0043DABD();
};

Rva0043DABD::~Rva0043DABD()
{
}
