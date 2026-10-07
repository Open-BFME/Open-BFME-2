// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Native 5EBC8E..5EBCC9: one owning-pointer word, allocation size 50.
// Its rowed destructor 5EBCC9 calls clear5EBC74, which destroys the
// existing Rva005EB8D6 pointee. The constructor 5EB9F2 takes this owner,
// saves it at +0, returns the allocated instance, and consumes RET4.
class Rva005EBC74;
class Rva005EB8D6
{
public:
	Rva005EB8D6(Rva005EBC74 *);
	~Rva005EB8D6();
private:
	char unknown00[0x50];
};

class Rva005EBC74
{
public:
	Rva005EBC74();
	~Rva005EBC74();
	void clear();
private:
	Rva005EB8D6 *m_ptr;
};

Rva005EBC74::Rva005EBC74() : m_ptr(new Rva005EB8D6(this))
{
}
