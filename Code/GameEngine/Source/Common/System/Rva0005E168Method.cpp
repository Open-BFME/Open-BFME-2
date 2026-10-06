// cl: /EHsc /MD
//
// ?rva0005E168@Rva0005E168@@QAEXABVAsciiString@@H@Z 0x0005E168 87B evidence: chain via 0x0005CE32 row; guard over +0x9D4 and array +0x12C stride 0x1C4 same as Rva00059A25 87B precedent; ctor/dtor rows 0x4120E/0x4122F; ret 8
class AsciiString;

class Rva0005CE32
{
public:
	void rva0005CE32(const AsciiString &s);
};

class MilesMutexGuard
{
public:
	MilesMutexGuard(void *obj, int flags);
	~MilesMutexGuard();
private:
	void *m_obj;
	int m_flags;
};

struct Elem1C4
{
	char data[0x1C4];
};

class Rva0005E168
{
public:
	void rva0005E168(const AsciiString &s, int idx);
private:
	char m_pad[0x12C];
	Elem1C4 m_arr[1];
	char m_padAfter[0x9D4 - 0x12C - 0x1C4];
	int m_9D4;
};

void Rva0005E168::rva0005E168(const AsciiString &s, int idx)
{
	MilesMutexGuard guard(&m_9D4, 0);
	((Rva0005CE32 *)&m_arr[idx])->rva0005CE32(s);
}
