// cl: /O1 /G7 /arch:SSE /MD /EHsc

// ?rva00504E6D@Rva00504DF8@@QAE?AURva00504E6DResult@@PBX@Z 64B @0x00504E6D.
// Target facts: the body calls 0x005049C6 with its value pointer, compares
// the returned node to this+4, compares the first floats when the node is not
// the end, and conditionally calls 0x00504D57. The 8-byte return writes a
// node pointer and an inserted byte to the caller's result object.
// Structural inference: this view has a 16-byte range at offsets 0/4/8; the
// node value starts with a float. The class and value meanings stay unknown.
struct Rva00504DF8Value
{
	float m_key;
	char m_pad04[0x0c];
};

struct Rva00504E6DResult
{
	Rva00504E6DResult(void *node, bool inserted)
		: m_node(node), m_inserted(inserted) {}

	void *m_node;
	bool m_inserted;
};

class Rva00504DF8
{
public:
	void *rva005049C6(const void *value);
	void *rva00504D57(void *position, const void *value);
	Rva00504E6DResult rva00504E6D(const void *value);

private:
	void *m_begin;
	void *m_finish;
	void *m_capacity;
};

Rva00504E6DResult Rva00504DF8::rva00504E6D(const void *value)
{
	bool notInserted = true;
	void *position = rva005049C6(value);
	if (position == m_finish ||
		((Rva00504DF8Value *)position)->m_key > ((Rva00504DF8Value *)value)->m_key)
	{
		position = rva00504D57(position, value);
		notInserted = false;
	}

	return Rva00504E6DResult(position, !notInserted);
}
