// cl: /MD
// ?rva001EDD80@Rva001EDD80@@QAE_NPBU Rva001EDD80Pair@@0@Z -- placeholder, see below
// Range check via abs dx/dy vs +0x12E8. Evidence: callees pinned _abs at 0x00629952(x2); callers in 0043/0042 bodies.
extern "C" int __cdecl abs(int value);

struct Rva001EDD80Pair
{
	int x;
	int y;
};

class Rva001EDD80
{
public:
	bool rva001EDD80(const Rva001EDD80Pair *a, const Rva001EDD80Pair *b);
private:
	char m_pad[0x12E8];
	unsigned int m_thresh;
};

bool Rva001EDD80::rva001EDD80(const Rva001EDD80Pair *a, const Rva001EDD80Pair *b)
{
	int dx = a->x - b->x;
	int dy = a->y - b->y;
	if (abs(dx) > m_thresh || abs(dy) > m_thresh)
		return true;
	return false;
}
