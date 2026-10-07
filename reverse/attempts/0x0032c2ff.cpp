// ?rva0032C2FF@Rva0032C2FF@@QAEXABVAsciiString@@@Z
// partial score=0.93 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /EHs /MD
// ?rva0032C2FF@Rva0032C2FF@@QAEXABVAsciiString@@@Z @0x0032C2FF 108 bytes.
// Target evidence: thiscall receiver owns a list at +0x20; each node's
// AsciiString is at +0x08. It compares every existing value and appends the
// argument only when no equal value is found. Class identity is unproven.

#include "ascii_string.h"

namespace _STL
{
template <class T> class list
{
public:
	struct node
	{
		node *next;
		node *previous;
		T value;
	};

	void push_back(const T &value);
	node *m_head;
};
}

class Rva0032C2FF
{
public:
	void rva0032C2FF(const AsciiString &value);

private:
	char m_unknown[0x20];
	_STL::list<AsciiString> m_values;
};

void Rva0032C2FF::rva0032C2FF(const AsciiString &value)
{
	_STL::list<AsciiString>::node *head = m_values.m_head;
	_STL::list<AsciiString>::node *node = head->next;
	if (node != head)
	{
		do
		{
			AsciiString current(node->value);
			if (value.compare(current) == 0)
				goto append;
			node = node->next;
		} while (node != m_values.m_head);
	}

append:
	m_values.push_back(value);
}
