// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x0035A238, 90 bytes, RET 16. The owner is unresolved.
// Native fields: list at +14, argument key at +74, a 12-byte record with
// key/value/flag/zero at +0/+4/+8/+9. Existing footprint list callees supply
// the container ABI; BfmePod12 describes storage rather than target identity.

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
		void push_front(const T &);
		void push_back(const T &);
	private:
		void *head;
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
