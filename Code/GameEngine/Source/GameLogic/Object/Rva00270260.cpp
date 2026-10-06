// cl: /MD
// ?rva00270260@Rva00270260@@QAE_NXZ @0x00270260 22B
// Returns byte at +0x43d OR byte at +0x43e.
// Evidence: callers test al at 0x000CE0A9 0x0007896B 0x000B6EFA; no donor; honest Rva name.
class Rva00270260
{
public:
	bool rva00270260();
private:
	unsigned char m_pad[0x43d];
	bool m_43d;
	bool m_43e;
};

bool Rva00270260::rva00270260()
{
	return m_43d || m_43e;
}
