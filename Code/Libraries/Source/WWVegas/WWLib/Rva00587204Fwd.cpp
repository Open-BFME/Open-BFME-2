// cl: /MD
// ?rva00587204@Rva00587204@@QAEAAURva0046247DPair@@AAU2@@Z, retail 0x00587204 19B.
// Forwarder: pointer at +4 to rowed rva0046247D 0x0046247D; returns arg. Caller 0x00587AB8 passes stack Pair.
struct Rva0046247DPair { void *first; void *second; };
class Rva0046247D { public: void rva0046247D(Rva0046247DPair &result); };
class Rva00587204
{
public:
	Rva0046247DPair &rva00587204(Rva0046247DPair &p);
private:
	int m_00;
	Rva0046247D *m_04;
};
Rva0046247DPair &Rva00587204::rva00587204(Rva0046247DPair &p)
{
	m_04->rva0046247D(p);
	return p;
}
