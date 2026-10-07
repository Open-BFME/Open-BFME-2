// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii
// ?rva001FD19E@Rva001FD19E@@QAEPBDH@Z @0x001FD19E 25B bounds-checked slot getter stride 4 offset 0x48 OOB empty string caller 0x00241ECC
class Rva001FD19E
{
public:
	const char *rva001FD19E(int index);
private:
	char m_pad[0x48];
	char m_slots[10][4];
};

const char *Rva001FD19E::rva001FD19E(int index)
{
	if (index < 0 || index >= 10)
		return "";
	return m_slots[index];
}
