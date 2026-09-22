// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: SList<TagBlockIndex>::Remove_All retail bucket cleanup.

class TagBlockIndex;

class StringBase
{
public:
	~StringBase();
};

template <class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/SLIST.H
class SList
{
private:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/LISTNODE.H
	// Retail proves the payload: the Node dtor at 0x6204D0 adjusts this+8
	// and tail-jumps to the StringBase dtor, so the string lives at +8
	// behind the link pointer and an int slot.
	struct Node
	{
		Node *next;
		int m_index;
		StringBase m_name;
		~Node();
	};

public:
	virtual void Remove_All();

private:
	Node *m_buckets[45007];
};

// ??1Node@?$SList@VTagBlockIndex@@@@QAE@XZ
template <>
SList<TagBlockIndex>::Node::~Node()
{
}

// ?Remove_All@?$SList@VTagBlockIndex@@@@UAEXXZ
template <>
void SList<TagBlockIndex>::Remove_All()
{
	for (int i = 0; i < 45007; ++i)
	{
		Node *node = m_buckets[i];
		while (node)
		{
			Node *next = node->next;
			delete node;
			node = next;
		}
		m_buckets[i] = 0;
	}
}
