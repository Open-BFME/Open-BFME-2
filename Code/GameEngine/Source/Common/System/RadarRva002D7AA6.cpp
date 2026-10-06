// cl: /DNDEBUG /MD
// ?rva002D7AA6@Radar@@QAEXH@Z @0x002D7AA6 10B clearer.
// Retail and [ecx+0x1460],0 then ret 4. Evidence: leaf lane; neighbours
// Radar_findDrawPositions and RadarNewMap; and-mem-zero needs /O1;
// ret 4 via single dummy int param.
class Radar {
public: void rva002D7AA6(int dummy);
private: char m_pad[0x1460]; int m_1460;
};
void Radar::rva002D7AA6(int dummy)
{
	(void)dummy;
	m_1460 = 0;
}
