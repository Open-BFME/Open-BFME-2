// cl: /MD
// ?rva0043346A@Rva0043346A@@QAEXM@Z @0x0043346A 23B: or dword [ecx+0xC4],0x10 then call rowed Anim2D::setAlpha 0x003ACA08; caller 0x004339BF
class Anim2D
{
public:
  void setAlpha(float alpha);
};
class Rva0043346A
{
public:
	void rva0043346A(float alpha);
private:
	char _pad[0xC4];
	int m_flags;
};
void Rva0043346A::rva0043346A(float alpha)
{
	m_flags |= 0x10;
	((Anim2D *)this)->Anim2D::setAlpha(alpha);
}
