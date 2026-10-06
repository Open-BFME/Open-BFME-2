// cl: /MD
// ?Rva00406F51Find@@YG_NPBVRva002B224BDwordField@@PAX1@Z @0x00406F51 75B: array search.
// If a3 null return false; else get array via rowed get 0x002B224B, walk null-
// terminated 4B array, via virtual +0xA8 get obj, via virtual +0x38 test (a2,a3)
// return true on first true else false. Caller 0x0040877C. Ret 0xC is stdcall.
class Rva002B224BDwordField
{
public:
	int get() const;
};

class Node
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual bool v14(void *a, void *b);
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual Node *v42();
};

bool __stdcall Rva00406F51Find(const Rva002B224BDwordField *f, void *a2, void *a3)
{
	if (a3 == 0)
		return false;
	Node **arr = (Node **)f->get();
	for (; *arr; ++arr) {
		Node *e = *arr;
		Node *o = e->v42();
		if (!o)
			continue;
		if (o->v14(a2, a3))
			return true;
	}
	return false;
}
