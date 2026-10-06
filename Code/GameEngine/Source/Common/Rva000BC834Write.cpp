// cl: /MD
//
// ?write@Rva000BC834@@QAEHPAD@Z retail 0x000BC834 37B
// Narrow concat node "Rva000BBD66 + AsciiStringRef": first slice write via
// 0x000BBD66 then second AsciiStringRef write 0x0002C5B1, summing lengths.
// Evidence: chain from 0x000BBD66 plus caller 0x000BD268 plus 37B shape
// matching Rva0002C9C2 in RegistryAsciiPath.cpp.
class AsciiString;

class Rva000B980E
{
public:
	void rva000B980E(char *dst, int off, int size);
private:
	AsciiString *m_str;
};

class Rva000BBD66 : public Rva000B980E
{
public:
	int rva000BBD66(char *dst);
private:
	int m_off;
	int m_len;
};

struct AsciiStringRef
{
	int write(char *dst);

	const AsciiString *m_string;
};

struct Rva000BC834
{
	int write(char *dst);

	Rva000BBD66 m_first;
	AsciiStringRef m_second;
};

int Rva000BC834::write(char *dst)
{
	int n = m_first.rva000BBD66(dst);
	return n + m_second.write(dst + n);
}

// ?write@Rva000BD268@@QAEHPAD@Z retail 0x000BD268 37B
// Narrow concat node "Rva000BC834 + Rva000BBD66": first composite write via
// 0x000BC834 then second slice write via 0x000BBD66, summing lengths.
// Evidence: chain from 0x000BC834 plus caller 0x000BDC6D plus 37B shape
// matching 0x000BC834.
struct Rva000BD268
{
	int write(char *dst);

	Rva000BC834 m_first;
	Rva000BBD66 m_second;
};

int Rva000BD268::write(char *dst)
{
	int n = m_first.write(dst);
	return n + m_second.rva000BBD66(dst + n);
}
