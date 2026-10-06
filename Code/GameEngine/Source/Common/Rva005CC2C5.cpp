// cl: /MD
// ?rva005CC2C5@Rva005CC2C5@@QAEXH@Z @0x005CC2C5 23B unregister calls rowed 0x002B7250 erase with this then clears holder.
// Evidence: callee rowed 0x002B7250; holder at +8 with list at +4; ret 4 one int param; no callers.
class CreateAHeroData;
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};
struct Holder002B7250
{
	char m_pad[4];
	Rva002B7250 m_list04;
};
class Rva005CC2C5
{
public:
	void rva005CC2C5(int dummy);
private:
	char m_pad[8];
	Holder002B7250 *m_holder08;
};
void Rva005CC2C5::rva005CC2C5(int /*dummy*/)
{
	m_holder08->m_list04.rva002B7250((CreateAHeroData *)this);
	m_holder08 = 0;
}
