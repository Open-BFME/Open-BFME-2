// cl: /MD
// ?rva0043852C@Rva0043852C@@QAE_NPAVRva00406F9C@@@Z @0x0043852C 13B: swapped intersect.
// Forwards to rowed 0x00406F9C with roles swapped: this as other (void*)
// and mask param as this. Symmetric intersect makes it equal. Chain from
// 0x00406F9C. Tiny forwarder sibling of mask checks.
class Rva00406F9C
{
public:
	bool rva00406F9C(const void *other);
};

class Rva0043852C
{
public:
	bool rva0043852C(Rva00406F9C *mask);
};

bool Rva0043852C::rva0043852C(Rva00406F9C *mask)
{
	return mask->rva00406F9C(this);
}
