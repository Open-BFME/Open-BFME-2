// cl: /EHsc /MD
//
// ?rva00108DBC@Rva00108DBC@@QAE_NXZ @0x00108DBC 108B. Init method allocating
// Rva00108A0B at +0x24C via rowed new and CameraClass(0x3FC) at +0x20,
// returning true. Caller at 0x0009A29A. Honest address name.
class HashableClass;

class HashTableClass
{
public:
	HashTableClass(int size);
private:
	int m_size;
	HashableClass **m_table;
};

class Rva00108A0B
{
public:
	Rva00108A0B();
private:
	HashTableClass *m_a;
	HashTableClass *m_b;
};

class CameraClass
{
public:
	CameraClass();
private:
	char m_pad[0x3FC];
};

class Rva00108DBC
{
public:
	bool rva00108DBC();
private:
	char m_pad00[0x20];
	CameraClass *m_cam;
	char m_pad24[0x24C - 0x24];
	Rva00108A0B *m_tbl;
};

bool Rva00108DBC::rva00108DBC()
{
	m_tbl = new Rva00108A0B();
	m_cam = new CameraClass();
	return true;
}
