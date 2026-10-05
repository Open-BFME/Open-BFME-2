// cl: /O1 /DNDEBUG /MD
// ?rva0027756D@Drawable@@QAE?AVRva002390CB@@H@Z @0x0027756D 92B
// Evidence: LINK 3 files; chain via rowed 0x00275D9F 0x0027682F 0x00276848 0x00276861 0x0027687A; sel!=3 plus Get plus 1-2-3 dec chain; neighbours DrawableRva00276B95 Drawable_rva00278689.
class Rva002390CB
{
public:
	Rva002390CB(const Rva002390CB &other);
	~Rva002390CB();
private:
	char m_pad[8];
};
class Rva00263546;
bool __cdecl Rva00275D9FGet(const Rva00263546 *a);
class Drawable
{
public:
	Rva002390CB rva0027756D(int sel);
	Rva002390CB rva0027682F();
	Rva002390CB rva00276848();
	Rva002390CB rva00276861();
	Rva002390CB rva0027687A();
private:
	unsigned char m_pad[0x258];
	Rva00263546 *m_statePtr();
};
Rva002390CB Drawable::rva0027756D(int sel)
{
	if (sel != 3)
	{
		const Rva00263546 *st = (const Rva00263546 *)((const unsigned char *)this + 0x258);
		if (Rva00275D9FGet(st))
			return rva0027682F();
	}
	switch (sel)
	{
	case 1:
		return rva00276848();
	case 2:
		return rva00276861();
	case 3:
		return rva0027687A();
	default:
		return rva0027682F();
	}
}
