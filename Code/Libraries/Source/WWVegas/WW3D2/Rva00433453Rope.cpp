// cl: /MD
// ?rva00433453@Rva00433453@@QAEXM@Z @0x00433453 23B: or dword [ecx+0xC4],8 then direct call rowed W3DRopeDraw::setRopeCurLen 0x00101CDA; caller 0x004339E9
class W3DRopeDraw
{
public:
	virtual void setRopeCurLen(float length);
};
class Rva00433453
{
public:
	void rva00433453(float len);
private:
	char _pad[0xC4];
	int m_flags;
};
void Rva00433453::rva00433453(float len)
{
	m_flags |= 8;
	((W3DRopeDraw *)this)->W3DRopeDraw::setRopeCurLen(len);
}
