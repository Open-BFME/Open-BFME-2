// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// ?rva00528FE0@Rva00528FE0@@QAE_NXZ @0x00528FE0 6B evidence: ptr-chase byte at +0x2D caller 0x002D66A2 in 1260B body
class Rva00528FE0Inner
{
public:
	char m_pad[0x2D];
	bool m_2D;
};
class Rva00528FE0
{
public:
	bool rva00528FE0();
private:
	Rva00528FE0Inner *m_ptr;
};
bool Rva00528FE0::rva00528FE0()
{
	return m_ptr->m_2D;
}
