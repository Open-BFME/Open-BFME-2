// cl: /EHsc /MD
// ??0Rva000B6A67@@QAE@XZ, retail 0x000B6A67, 66 bytes.
// __thiscall ctor with EH frame: implicit StringBase<char> default at +0x10,
// m4=-1 via or, set("") via rowed 0x000055F5, then m0=0 m8=0 mc=0, returns
// this. Callers 0x000B9AA1 0x000B9AB5 0x000C48F1 0x000C4A53. Honest address
// name; member roles unproven.
template <typename T>
class StringBase
{
private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;

public:
	StringBase() : m_data(0) {}
	~StringBase();
	void set(const T *str);
};

class Rva000B6A67
{
public:
	Rva000B6A67();

private:
	int m0;
	int m4;
	int m8;
	unsigned char mc;
	char m_pad[3];
	StringBase<char> m_str;
};

Rva000B6A67::Rva000B6A67()
{
	m4 = -1;
	m_str.set("");
	m0 = 0;
	m8 = 0;
	mc = 0;
}
