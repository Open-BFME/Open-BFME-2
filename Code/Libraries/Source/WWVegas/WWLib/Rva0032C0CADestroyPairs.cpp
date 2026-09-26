// cl: /O1 /MD /DNDEBUG
//
// Rva0032C0CA 8-byte-pair range destroy, retail 0x0032C0CA, 25 bytes.
// Leaf _Destroy loop over contiguous 8-byte pairs (AsciiString key plus a
// 4-byte payload): each element's key is released through the rowed
// AsciiString scalar dtor at 0x0048BA39 (5-byte tail-jump to releaseBuffer).
// Called by the 8-byte vector erase at 0x00207F0D. Element payload type is
// unproven (any 4-byte POD produces these bytes); the Rva pair name claims
// only the address plus the 8-byte stride the retail add proves.

class AsciiString
{
public:
	~AsciiString();

private:
	char *m_text;
};

struct RvaPair0032C0CA
{
	AsciiString m_key;
	int m_value;
};

// Rva0032C0CADestroyPairs @0x0032C0CA
void Rva0032C0CADestroyPairs(RvaPair0032C0CA *first, RvaPair0032C0CA *last)
{
	for (; first != last; ++first)
		first->m_key.~AsciiString();
}
