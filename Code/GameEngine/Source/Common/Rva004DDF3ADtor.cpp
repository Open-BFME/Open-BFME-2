// cl: /O1 /EHsc /DNDEBUG /MD
// ??1Rva004DDF3A@@QAE@XZ @ 0x004DDF3A 23B: non-virtual dtor calling three
// Rva004DD843 cleanup methods with same this then tail-jumping to the third.
// Evidence: deleting-dtor caller 0x0028AB32; pins at 0x004DDD6E 0x004DDD80
// 0x004DDD92; prev/next TUs Rva004DD9E3.cpp and Rva001DB130Find.cpp.
class Rva004DD843
{
public:
	void rva004DDD6E();
	void rva004DDD80();
	void rva004DDD92();
};
class Rva004DDF3A : public Rva004DD843
{
public:
	~Rva004DDF3A();
};
Rva004DDF3A::~Rva004DDF3A()
{
	rva004DDD6E();
	rva004DDD80();
	rva004DDD92();
}
