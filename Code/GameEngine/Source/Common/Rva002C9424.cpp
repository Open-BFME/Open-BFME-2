// cl: /DNDEBUG /MD
// ?rva002C9424@Rva002C9424@@QAEPAV1@XZ, RVA 0x002C9424, 23 bytes.
// Zeroes +0 +4 +C +10 and sets +8 to 6 via this in eax with xor-zeroed ecx.
// Evidence: no callees; caller 0x002C8CE2; neighbours 0x002C941C 0x002C943B same flags.
class Rva002C9424
{
public:
	Rva002C9424 *rva002C9424();
private:
	int m_0;
	int m_4;
	int m_8;
	int m_c;
	int m_10;
};
Rva002C9424 *Rva002C9424::rva002C9424()
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 6;
	m_c = 0;
	m_10 = 0;
	return this;
}
