// cl: /DNDEBUG /MD /EHsc
// ?rva003B4982@Rva003B4982@@QAEXPAX@Z @0x003B4982 (158B): recursive script skip/clear over two head lists via captureGroup plus self plus skipGroup/skipScript with clear and delete. Evidence: callers 0x003B49AB self plus 0x003B7373; rowed captureGroup 0x003B40A1 skipGroup 0x003B485A skipScript 0x003B48B9 clears 0x003B31DF 0x003B3204 delete 0x0002FD60; ret 4 single void-star arg from retail bytes. Rows say skipGroup/skipScript return int but retail tests al so truncate via unsigned char to get test al al while keeping row mangling.
class Rva003B40A1Holder
{
public:
	void *captureGroup(void *p);
};

class Rva003B485AHolder
{
public:
	int skipGroup(void *p);
};

class Rva003B48B9Holder
{
public:
	int skipScript(void *p);
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

class Rva003B4982
{
public:
	void rva003B4982(void *arg);
};

void Rva003B4982::rva003B4982(void *arg)
{
	Arg *a = (Arg *)arg;
	Node **pp = (Node **)a;
	while (*pp != 0) {
		Node *cur = *pp;
		void *cap = ((Rva003B40A1Holder *)this)->captureGroup(cur);
		void *q = cap != 0 ? (char *)cap + 4 : 0;
		rva003B4982(q);
		int s = ((Rva003B485AHolder *)this)->skipGroup(cur);
		if ((unsigned char)s != 0) {
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
		int s = ((Rva003B48B9Holder *)this)->skipScript(cur);
		if ((unsigned char)s != 0) {
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
