// cl: /MD /EHsc
// ?rva00201A33@Rva00201A33@@QAEPAXV?$StringBase@D@@@Z 0x00201A33 81B: list find by string.
// Evidence: unlock lane (unblocks 0x00201A84 0x00201CAF); callers 0x00201AA7 0x00201CEB; StringBase compare 0x69D6 release 0x36410; slot compare; head at +0.
template <typename T>
class StringBase
{
public:
	int compare(const StringBase &other) const throw();
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	void *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


struct Rva00201A33Data
{
	char m_pad[4];
	StringBase<char> m_name;
};

struct Rva00201A33Node
{
	Rva00201A33Node *m_next;
	int m_pad;
	Rva00201A33Data *m_data;
};

class Rva00201A33
{
public:
	void *rva00201A33(StringBase<char> name);
	Rva00201A33Node *m_head;
};

void *Rva00201A33::rva00201A33(StringBase<char> name)
{
	Rva00201A33Node *node = m_head->m_next;
	while (node != m_head)
	{
		Rva00201A33Data *data = node->m_data;
		if (data->m_name.compare(name) == 0)
			return data;
		node = node->m_next;
	}
	return 0;
}
