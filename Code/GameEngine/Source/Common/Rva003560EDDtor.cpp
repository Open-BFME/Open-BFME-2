// cl: /MD /EHsc
// ??1Rva003560ED@@UAE@XZ @0x003560ED (112B)
// Derived dtor of Rva00355D66 clearing TheGameLogic +0x78 then calling
// TheDisplay slot 0x110 plus rowed W3DDisplay::rva0025D2F6 0x0025D2F6 then
// destroying StringBase narrow at +0x14/+0x10 via rowed releaseBuffer
// 0x00036410 then base 0x00355D66. Same recipe as Rva003563A7Dtor.
// Evidence: vtable 0x00814EA4 plus deleting caller 0x0035670B.
template <typename T> class StringBase {
public: ~StringBase() { releaseBuffer(); }
private: void releaseBuffer();
	T *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


class Display {
public:
	virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03(); virtual void d04();
	virtual void d05(); virtual void d06(); virtual void d07(); virtual void d08(); virtual void d09();
	virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
	virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
	virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
	virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
	virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34();
	virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
	virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44();
	virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49();
	virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54();
	virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59();
	virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64();
	virtual void d65(); virtual void d66(); virtual void d67(); virtual void slot68();
};

extern Display *TheDisplay;

class GameLogic {
public:
	char m_pad[0x78];
	bool m_flag78;
};

extern GameLogic *TheGameLogic;

class W3DDisplay {
public:
	void rva0025D2F6();
};

class Rva00355D66 {
public:
	virtual ~Rva00355D66();
private:
	char m_pad[0x0c];
};

class Rva003560ED : public Rva00355D66 {
public:
	virtual ~Rva003560ED();
private:
	StringBase<char> m_s10;
	StringBase<char> m_s14;
};

Rva003560ED::~Rva003560ED()
{
	TheGameLogic->m_flag78 = false;
	TheDisplay->slot68();
	((W3DDisplay *)TheDisplay)->rva0025D2F6();
}
