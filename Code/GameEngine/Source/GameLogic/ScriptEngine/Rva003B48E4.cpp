// cl: /DNDEBUG /MD /EHsc
// ?rva003B48E4@Rva003B48E4@@QAEXPAX@Z @0x003B48E4 (158B): recursive script check/clear over two head lists via captureGroup plus self plus leaf checks with clear and delete. Evidence: callers 0x003B490D self plus 0x003B694C; rowed captureGroup 0x003B40A1 check 0x003B483D check 0x003B489C clears 0x003B31DF 0x003B3204 delete 0x0002FD60; ret 4 single void-star arg from retail bytes.
class Rva003B40A1Holder
{
public:
	void *captureGroup(void *p);
};

class Rva003B483DHolder
{
public:
	bool check(const void *p) const;
};

class Rva003B489CHolder
{
public:
	bool check(const void *p) const;
};

class Rva003B31DF
{
public:
	void clear();
};

class Rva003B3204
{
public:
	void clear();
};

struct Node
{
	Node *next;
	int unk4;
	int flag;
};

struct Arg
{
	Node *head0;
	Node *head1;
};

class Rva003B48E4
{
public:
	void rva003B48E4(void *arg);
};

void Rva003B48E4::rva003B48E4(void *arg)
{
	Arg *a = (Arg *)arg;
	Node **pp = (Node **)a;
	while (*pp != 0) {
		Node *cur = *pp;
		void *cap = ((Rva003B40A1Holder *)this)->captureGroup(cur);
		void *q = cap != 0 ? (char *)cap + 4 : 0;
		rva003B48E4(q);
		if (!((Rva003B483DHolder *)this)->check(cur)) {
			Node *nxt = cur->next;
			*pp = nxt;
			cur->next = 0;
			((Rva003B31DF *)cur)->clear();
			::operator delete(cur);
		} else {
			cur->flag = 1;
			pp = (Node **)cur;
		}
	}
	Node **qq = &a->head1;
	while (*qq != 0) {
		Node *cur = *qq;
		if (!((Rva003B489CHolder *)this)->check(cur)) {
			Node *nxt = cur->next;
			*qq = nxt;
			cur->next = 0;
			((Rva003B3204 *)cur)->clear();
			::operator delete(cur);
		} else {
			cur->flag = 1;
			qq = (Node **)cur;
		}
	}
}
