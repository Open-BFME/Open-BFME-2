// cl: /O1
class Rva00203B08
{
	char m_pad[0x1A4D9];
	bool m_flag;
public:
	bool rva00203B08();
	bool rva00203AE5();
	bool rva0020424FF();
};

bool Rva00203B08::rva0020424FF()
{
	return rva00203AE5() || rva00203B08();
}
