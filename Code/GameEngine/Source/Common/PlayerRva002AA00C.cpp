// cl: /O1 /DNDEBUG /MD
// ?rva002AA00C@Player@@QAEEPAVThingTemplate@@H@Z RVA 0x002AA00C size 37
// Evidence: unlock lane; caller 0x003BCF2F passes Player in ecx with ThingTemplate void eax plus int 0; callee 0x0033A69A ThingTemplate const method pin-only; reads ecx+0x94 ret8 sbb-inc uchar.
class Object;
class ThingTemplate
{
public:
	int rva0033A69A(Object *obj, int a, int b) const;
};
class Player
{
public:
	unsigned char rva002AA00C(ThingTemplate *tmpl, int extra);
private:
	char m_pad[0x94];
	int m_0094;
};
unsigned char Player::rva002AA00C(ThingTemplate *tmpl, int extra)
{
	int base = m_0094;
	int v = tmpl->rva0033A69A((Object *)this, 0, -1);
	return (unsigned char)((unsigned)(base + extra) >= (unsigned)v);
}
