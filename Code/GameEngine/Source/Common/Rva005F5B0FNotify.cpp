// cl: /GX- /MD /DNDEBUG
// ?Rva005F5B0FNotify@@YAXPAURva005F5B0FA@@PAURva005F5B0FB@@@Z @0x005F5B0F 104B
// Iterates RB-tree map at second arg +0x10 keyed at node +0x10 via rowed _M_increment.
// Looks up each key with rowed IndexedField get at first arg +0x78 and checks result +0xBC.
// On hit builds GameMessage type 0x6C0 via MessageStreamSubsystem slot 0x48 and appends first arg +0x20 and key.
// Evidence: callees rowed get 0x0040CBB8 appendIntegerArgument 0x0030F936 increment 0x00024250; caller 0x005F5BAE passes +0x18 +0x1C cdecl.
namespace _STL
{
struct _Rb_tree_node_base
{
	char _M_color;
	char _M_pad[3];
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};
template <class Dummy>
struct _Rb_global
{
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *) throw();
};
}
class Rva0040CB3AIndexedField
{
public:
	int get(int key) const;
};
class GameMessage
{
public:
	void appendIntegerArgument(int arg);
};
class MessageStream
{
public:
	virtual void d0();
	virtual void d1();
	virtual void d2();
	virtual void d3();
	virtual void d4();
	virtual void d5();
	virtual void d6();
	virtual void d7();
	virtual void d8();
	virtual void d9();
	virtual void d10();
	virtual void d11();
	virtual void d12();
	virtual void d13();
	virtual void d14();
	virtual void d15();
	virtual void d16();
	virtual void d17();
	virtual GameMessage *CreateMessage(int type);
};
extern class MessageStream *TheMessageStream;
struct Rva005F5B0FA
{
	char _pad0[0x20];
	int m_20;
	char _pad1[0x78 - 0x20 - 4];
	class Rva0040CB3AIndexedField *m_78;
};
struct Rva005F5B0FB
{
	char _pad0[0x10];
	_STL::_Rb_tree_node_base *m_tree;
};
void __cdecl Rva005F5B0FNotify(Rva005F5B0FA *a, Rva005F5B0FB *b)
{
	Rva0040CB3AIndexedField *field = a->m_78;
	_STL::_Rb_tree_node_base *header = b->m_tree;
	_STL::_Rb_tree_node_base *node = header->_M_left;
	for (; node != header; node = _STL::_Rb_global<bool>::_M_increment(node))
	{
		if (*(int *)(field->get(*(int *)((char *)node + 16)) + 0xbc) != 0)
		{
			GameMessage *msg = TheMessageStream->CreateMessage(0x6c0);
			msg->appendIntegerArgument(a->m_20);
			msg->appendIntegerArgument(*(int *)((char *)node + 16));
		}
	}
}
