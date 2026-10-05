// cl: /Od /Ob1

inline bool bfmeEqVMQ(char a, char b)
{
	return a == b;
}

class BfmeStrVMQ
{
public:
	bool bfmeNeVMQ(const char *o) const;
};

bool BfmeStrVMQ::bfmeNeVMQ(const char *o) const
{
	return !bfmeEqVMQ(*o, *(const char *)this);
}

class Rva00249B0
{
public:
	bool f(const char *o) const;
};

bool Rva00249B0::f(const char *o) const
{
	return bfmeEqVMQ(*o, *(const char *)this);
}
