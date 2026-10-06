// cl: /EHsc /MD
// ?findControlBarScheme@ControlBarSchemeManager@@QAEPAUEntry@@V?$StringBase@D@@@Z @0x0031FC08 98B unlock: case-insensitive find by lowered name over list at +0xC
// Evidence: EH_prolog with stack StringBase<char> lowered via rowed toLower 0x36A70 then walked against rowed compareNoCase 0x6A00; callers at 0x31FC8E 0x31FE1A 0x31FFFD 0x320562; prev Rva0031FA40Create /O1 /EHsc /MD next ControlBarList.
template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

template <typename T> class StringBase
{
public:
	void toLower();
	int compareNoCase(const StringBase<T> &other) const;
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	BfmeStringData<T> *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


struct Entry
{
	StringBase<char> m_name;
	int m_4;
	int m_8;
};

struct Node
{
	Node *m_next;
	Node *m_prev;
	Entry *m_data;
};

class ControlBarSchemeManager
{
public:
	Entry *findControlBarScheme(StringBase<char> name);
private:
	char m_pad[0xC];
	Node *m_list;
};

Entry *ControlBarSchemeManager::findControlBarScheme(StringBase<char> name)
{
	name.toLower();
	Node *cur = m_list->m_next;
	Entry *res;
	for (;;)
	{
		if (cur == m_list)
		{
			res = 0;
			break;
		}
		Entry *e = cur->m_data;
		if (!e)
		{
			res = 0;
			break;
		}
		if (e->m_name.compareNoCase(name) == 0)
		{
			res = e;
			break;
		}
		cur = cur->m_next;
	}
	return res;
}
