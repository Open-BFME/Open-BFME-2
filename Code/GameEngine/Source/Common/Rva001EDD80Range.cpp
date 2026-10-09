// cl: /MD
// ?rva001EDD80@Mouse@@QAE_NPBURva001EDD80Pair@@0@Z
// Receiver identity: retail LookAt translation 0x0042E9EC/2087 loads TheMouse
// at VA 0x00DFDCA0 and calls this body at 0x0042EBDF with two pixel pairs.
// The original method name and pair type spelling remain unknown.
// Range check via abs dx/dy vs +0x12E8. Evidence: callees pinned _abs at 0x00629952(x2); callers in 0043/0042 bodies.
extern "C" int __cdecl abs(int value);

struct Rva001EDD80Pair
{
	int x;
	int y;
};

class Mouse
{
public:
	bool rva001EDD80(const Rva001EDD80Pair *a, const Rva001EDD80Pair *b);
private:
	char m_pad[0x12E8];
	unsigned int m_thresh;
};

bool Mouse::rva001EDD80(const Rva001EDD80Pair *a, const Rva001EDD80Pair *b)
{
	int dx = a->x - b->x;
	int dy = a->y - b->y;
	if (abs(dx) > m_thresh || abs(dy) > m_thresh)
		return true;
	return false;
}
