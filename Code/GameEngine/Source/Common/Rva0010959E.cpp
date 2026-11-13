// cl: /DNDEBUG /MD
// ?rva0010959E@Rva0010959E@@QAEXXZ @0x0010959E 20B
// Calls rowed W3DProjectedShadow::rva00108951 at +0x58 then tail-jmps it at
// +0x5C; caller at 0x0010BA18; chain from 0x00108951.
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DProjectedShadowClass.h"
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/Rva0010959E.h"
void Rva0010959E::rva0010959E()
{
	m_58->rva00108951();
	return m_5c->rva00108951();
}

struct Node : public Rva0010959E
{
	Node *m_next64;
};
class Rva0010B9E5
{
public:
	void rva0010B9E5(Node *arg);
private:
	char m_pad[0x14];
	Node *m_head14;
	Node *m_tail18;
};
void Rva0010B9E5::rva0010B9E5(Node *node)
{
	Node *cur = m_head14;
	Node *prev = 0;
	while (cur != 0) {
		if (cur == node) {
			if (prev != 0)
				prev->m_next64 = node->m_next64;
			else
				m_head14 = node->m_next64;
			Node *tail = m_tail18;
			node->m_next64 = tail;
			m_tail18 = node;
			node->rva0010959E();
		}
		prev = cur;
		cur = cur->m_next64;
	}
}
