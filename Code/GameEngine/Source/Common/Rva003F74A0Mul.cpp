// cl: /MD
// ?rva003F74A0@Rva003F74A0@@QAEXM@Z @0x003F74A0 19B.
// Float multiply-assign of the +0x28 member.
// Evidence: retail movss xmm0,[esp+4]; mulss xmm0,[ecx+0x28];
// movss [ecx+0x28],xmm0; ret 4. Callers at 0x002BCB05 0x003F221B.
class Rva003F74A0
{
	char m_pad[0x28];
	float m_float28;
public:
	void rva003F74A0(float f);
};

void Rva003F74A0::rva003F74A0(float f)
{
	m_float28 *= f;
}
