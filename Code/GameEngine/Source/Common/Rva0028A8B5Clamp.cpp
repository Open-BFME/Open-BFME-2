// cl: /O1 /arch:SSE
// ?rva0028A8B5@Rva0028A8B5@@QBEXPAM@Z @0x0028A8B5 45B: clamp float* between members +0x4C0 (max) and +0x4C4 (min) via SSE comiss.
// Evidence: called from Object::getVisionRange 0x0028DDE0 with this=[esi+4] and arg=stack float; retail movss lea comiss mov add movss comiss mov; callers 2.
class Rva0028A8B5
{
public:
	void rva0028A8B5(float *v) const;
private:
	char m_pad[0x4C0];
	float m_max4C0;
	float m_min4C4;
};
void Rva0028A8B5::rva0028A8B5(float *v) const
{
	if (*v > m_max4C0)
		*v = m_max4C0;
	if (m_min4C4 > *v)
		*v = m_min4C4;
}
