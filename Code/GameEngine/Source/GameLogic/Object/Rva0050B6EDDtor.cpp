// cl: /DNDEBUG /MD
// ??1Rva0050B6ED@@UAE@XZ, retail 0x0050B6ED, 11 bytes.
// Evidence: vtable 0x00864D80 plus tail-jmp to rowed base
// ??1Rva00507823@@UAE@XZ 0x00507823; caller 0x0050B6D4 unblocks 0x0050B6D1.
class Rva00507823
{
public:
	virtual ~Rva00507823();
};

class Rva0050B6ED : public Rva00507823
{
public:
	virtual ~Rva0050B6ED();
};

Rva0050B6ED::~Rva0050B6ED()
{
}
