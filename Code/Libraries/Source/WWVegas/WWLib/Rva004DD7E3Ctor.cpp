// cl: /DNDEBUG /MD /EHsc
//
// ??0Rva004DD7E3@@QAE@H@Z @ 0x004DD7E3 39B
// Ctor stores int arg at +0 then constructs three 0x18 members at +4 +0x1C +0x34
// via rowed ??0Rva004DD7C4@@QAE@XZ. Evidence: three calls to 0x004DD7C4;
// returns this; callers at 0x00298308 0x002993BB.
class Rva004DD7C4
{
public:
	Rva004DD7C4();
private:
	int m00;
	int m04;
	int m08;
	int m0C;
	int m10;
	int m14;
};
class Rva004DD7E3
{
public:
	Rva004DD7E3(int x);
private:
	int m00;
	Rva004DD7C4 m04;
	Rva004DD7C4 m1C;
	Rva004DD7C4 m34;
};
Rva004DD7E3::Rva004DD7E3(int x)
	: m00(x)
	, m04()
	, m1C()
	, m34()
{
}
