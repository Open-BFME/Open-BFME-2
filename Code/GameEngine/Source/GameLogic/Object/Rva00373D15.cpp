// cl: /EHsc
// ?rva00373D15@Rva00373D15@@QAEHXZ @0x00373D15 14B
// evidence: __thiscall leaf between StealthUpdate name getter and Object forwarder; callers at 0x00373F70 0x003744C4; LINK 4 files 122B
struct Rva00373D15Inner
{
	int m_pad[3];
	int m_val;
};
class Rva00373D15
{
public:
	int rva00373D15();
private:
	void *m_00;
	Rva00373D15Inner *m_04;
	char m_pad08[0x24];
	int m_2C;
};
int Rva00373D15::rva00373D15()
{
	int v = m_2C;
	if (v < 0)
		v = m_04->m_val;
	return v;
}
