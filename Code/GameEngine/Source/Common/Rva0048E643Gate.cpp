// cl: /O1 /DNDEBUG /MD
//
// ?rva0048E643@Rva0048E643@@QAE_NXZ @0x0048E643 24B.
// If the rowed test at 0x0048E61F is true, return false. Otherwise tail-jump
// to the rowed status test at 0x002645FF.

class Rva0048E61F
{
public:
	int rva0048E61F();
};

class Rva002645FF
{
public:
	bool rva002645FF();
};

class Rva0048E643
{
public:
	bool rva0048E643();
};

bool Rva0048E643::rva0048E643()
{
	if ((unsigned char)((Rva0048E61F *)this)->rva0048E61F())
		return false;
	return ((Rva002645FF *)this)->rva002645FF();
}
