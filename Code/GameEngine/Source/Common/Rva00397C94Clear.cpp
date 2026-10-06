// cl: /DNDEBUG /MD
//
// ?rva00397C94@Rva00397C94@@QAEXPAURva00397C94Node@@@Z, retail 0x00397C94, 53 bytes.
// Recursive tree-node clear with an inline CameraMarker at +0x10.
// Evidence: self-call at 0x00397CA6 plus rowed CameraMarker dtor at
// 0x0029D7C2 and rowed _free at 0x00030830; caller 0x00398257 resets an
// STL-list-like head after the call; node links are next at +0x08 and
// child at +0x0C with the value at +0x10.

class CameraMarker
{
public:
	~CameraMarker();
};

extern "C" void __cdecl free(void *p);

struct Rva00397C94Node
{
	void *m_pad00;
	void *m_pad04;
	Rva00397C94Node *m_next;
	Rva00397C94Node *m_child;
	CameraMarker m_marker;
};

class Rva00397C94
{
public:
	void rva00397C94(Rva00397C94Node *node);
};

void Rva00397C94::rva00397C94(Rva00397C94Node *node)
{
	while (node != 0)
	{
		rva00397C94(node->m_child);
		Rva00397C94Node *next = node->m_next;
		node->m_marker.~CameraMarker();
		free(node);
		node = next;
	}
}
