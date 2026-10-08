// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x0035A238, 90 bytes, RET 16. The owner is unresolved.
// Native fields: list at +14, argument key at +74, a 12-byte record with
// key/value/flag/zero at +0/+4/+8/+9. Existing footprint list callees supply
// the container ABI; BfmePod12 describes storage rather than target identity.

#include "../Common/GameLogicObjectLookupView.h"
#include "../Common/RTS/XYDistanceCallView.h"

extern GameLogic *TheGameLogic;

struct BfmePod12
{
	int key;
	float value;
	bool flag;
	bool zero;
	char padding[2];
};

namespace _STL
{
	template<class T> class allocator {};
	template<class T, class A = allocator<T> > class list
	{
	public:
		struct Node
		{
			Node *next;
			Node *previous;
			T data;
		};
		Node *begin() const { return head->next; }
		Node *end() const { return head; }
		void push_front(const T &);
		void push_back(const T &);
	private:
		Node *head;
	};
}

struct Rva0035A238Argument
{
	char unknown00[0x74];
	int key;
};

class Rva0035A238
{
public:
	void rva0035A238(Rva0035A238Argument *argument, float value, bool flag, bool front);
	void rva00359E93(Rva0035A238Argument *argument, float value, bool front, bool extra);
	void rva00359D99(Rva000CBA20 *center, float radius);
	void rva0035A14F(Rva0035A238Argument *argument);
private:
	char unknown00[0x14];
	_STL::list<BfmePod12> records;
};

void Rva0035A238::rva0035A238(Rva0035A238Argument *argument, float value, bool flag, bool front)
{
	BfmePod12 record;
	record.key = argument->key;
	record.value = value;
	record.flag = flag;
	record.zero = false;
	if (front)
		records.push_front(record);
	else
		records.push_back(record);
	rva00359E93(argument, value, front, false);
}

// Native 0x00359D99, 107 bytes, RET 8. Shares the +14 list and callback
// with 0x0035A238. Key lookup establishes Object identity; the distance
// call view and +38 position are target evidence, not an asserted layout.
void Rva0035A238::rva00359D99(Rva000CBA20 *center, float radius)
{
	radius *= radius;
	for (_STL::list<BfmePod12>::Node *item = records.begin(); item != records.end(); item = item->next)
	{
		Object *object = TheGameLogic->findObjectByID(static_cast<ObjectID>(item->data.key));
		if (object && center->distSq(reinterpret_cast<const Rva000CBA20Point *>(reinterpret_cast<char *>(object) + 0x38)) <= radius)
			rva00359E93(reinterpret_cast<Rva0035A238Argument *>(object), item->data.value, false, item->data.zero);
	}
}

// Native 0x0035A14F, 62 bytes, RET 4. Called by 0x00482172 on the same
// manager as the recovered insertion; matches all records for key +74,
// dispatches the existing callback and sets the node's +11 flag.
void Rva0035A238::rva0035A14F(Rva0035A238Argument *argument)
{
	for (_STL::list<BfmePod12>::Node *item = records.begin(); item != records.end(); item = item->next)
	{
		if (item->data.key == argument->key)
		{
			rva00359E93(argument, item->data.value, false, true);
			item->data.zero = true;
		}
	}
}
