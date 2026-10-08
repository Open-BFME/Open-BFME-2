// cl: /DNDEBUG /MD /EHsc
// Native0x000A8B37..0x000A8B4B forwards a float and an integer to10FE6D.
// The callee allocates a20-byte event and calls the rowed float/int ctor
// Rva0010EF61. Target bytes and that ctor establish the argument domains.
// The old BFME1 donor (revision6d9434269164392c5ba62aaa7c15a86b5b020d76,
// Rva000059EDBezierSegmentThunk.cpp) supplied this instruction shape, but
// its Bezier identity was an unsupported inference and is now refuted.
// The original owner and event purpose remain unknown.
class Rva0010FE6D
{
public:
	void rva0010FE6D(float value, int tag);
};

class Rva000A8B37
{
public:
	void rva000A8B37(float value, int tag);
};

void Rva000A8B37::rva000A8B37(float value, int tag)
{
	reinterpret_cast<Rva0010FE6D *>(this)->rva0010FE6D(value, tag);
}
