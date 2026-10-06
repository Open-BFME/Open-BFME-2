// cl: /DNDEBUG /MD /EHsc

class Rva00142BA0
{
public:
	void add(void *object);

private:
	char m_pad[0x30];
	void *m_items[0x20];
	unsigned int m_count;
	unsigned int m_overflow;
};

void Rva00142BA0::add(void *object)
{
	if (m_count < 0x1f) {
		if (object != 0) {
			++*(int *)((char *)object + 4);
		}
		m_items[m_count] = object;
		++m_count;
	} else {
		++m_overflow;
	}
}
