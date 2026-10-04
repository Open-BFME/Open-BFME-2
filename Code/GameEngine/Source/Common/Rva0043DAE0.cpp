// cl: /O1 /DNDEBUG /MD
// ??1Rva0043DAE0@@UAE@XZ @0x0043DAE0 11B
// Evidence: chain from 0x0057F2DE, stores vtable 0x00C3D95C then jmp to ??1Rva0057F2DE@@UAE@XZ; callers 0x0043DB0A 0x00788C09 0x00788CA7.
class Rva0057F2DE
{
public:
	virtual ~Rva0057F2DE();
};

class Rva0043DAE0 : public Rva0057F2DE
{
public:
	virtual ~Rva0043DAE0();
};

Rva0043DAE0::~Rva0043DAE0()
{
}
