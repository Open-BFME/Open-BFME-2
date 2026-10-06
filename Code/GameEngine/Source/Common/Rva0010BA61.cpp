// cl: /DNDEBUG /MD
// ?rva0010BA61@Rva0010BA61@@QAEXXZ
// recovered from packet 0x0010BA61 16B lane=unlock
// Evidence: rowed call 0x00109D64 ?rva00109D64@Rva007B1380@@QAEXXZ; pin 0x00108895 ?rva00108895@Rva0010BA2COwner@@QAEXXZ; caller 0x0010BB4F; prev/next // cl: /O1 /DNDEBUG /MD
class Rva007B1380
{
public:
	void rva00109D64();
};

class Rva0010BA2COwner
{
public:
	void rva00108895();
};

class Rva0010BA61
{
public:
	void rva0010BA61();
};

void Rva0010BA61::rva0010BA61()
{
	((Rva007B1380 *)this)->rva00109D64();
	((Rva0010BA2COwner *)this)->rva00108895();
}
