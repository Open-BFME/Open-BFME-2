// cl: /DNDEBUG /MD /EHsc
// ?rva005C9AB4@Rva005C9B76@@QAEXXZ @ 0x005C9AB4 41B
// Evidence: layout from Rva005C9B76Ctor +0x4 list +0x14 arg +0x18 flag +0x1C int; rowed forEach 0x005C9A64 and forwarder 0x005CB260; caller 0x00575038.
class Rva005C9A64Listener
{
public:
	virtual void notify(void *, int);
};

class Rva005C9A64List
{
public:
	void forEach(void (Rva005C9A64Listener::*notify)(void *, int), void *arg, int value);
private:
	Rva005C9A64Listener **m_begin;
	Rva005C9A64Listener **m_end;
	Rva005C9A64Listener **m_capacity;
	unsigned int m_index;
};

class Rva005CB260
{
public:
	void rva005CB260();
};

class Rva005C98C0
{
public:
	void *rva005C98C0(int id);
};

class Rva005C9B76
{
public:
	void rva005C9AB4();
	int rva005C9ADD(int v, int);
	void rva005C9B56(int v);
	virtual ~Rva005C9B76();
private:
	Rva005C9A64List m_list;
	void *m_arg14;
	unsigned char m_b18;
	char m_pad19[3];
	int m_i1C;
};

void Rva005C9B76::rva005C9AB4()
{
	if (m_b18 == 0) {
		int v = m_i1C;
		if (v != 0) {
			m_i1C = 0;
			m_list.forEach(
				reinterpret_cast<void (Rva005C9A64Listener::*)(void *, int)>(&Rva005CB260::rva005CB260),
				this,
				v);
		}
	}
	m_b18 = 0;
}
int Rva005C9B76::rva005C9ADD(int v, int)
{
	m_b18 = 1;
	int r = reinterpret_cast<int>(reinterpret_cast<Rva005C98C0 *>(this)->rva005C98C0(v));
	int cur = m_i1C;
	if (r != cur) {
		m_i1C = r;
		m_list.forEach(
			reinterpret_cast<void (Rva005C9A64Listener::*)(void *, int)>(&Rva005CB260::rva005CB260),
			this,
			cur);
	}
	return 0;
}
void Rva005C9B76::rva005C9B56(int v)
{
	int cur = m_i1C;
	if (v != cur) {
		m_i1C = v;
		m_list.forEach(
			reinterpret_cast<void (Rva005C9A64Listener::*)(void *, int)>(&Rva005CB260::rva005CB260),
			this,
			cur);
	}
}
