// ??0Rva005CCC69@@QAE@PAVRva005CCDDD@@@Z
// partial score=0.5 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Native5CCC50..5CCC69: base ctor5CCBD0; parent stored at24; C74F24.
class Rva005CCDDD;
class Rva005CCC07
{
public:
	Rva005CCC07() throw();
	virtual ~Rva005CCC07();
private:
	char unknown04[0x20];
};
class Rva005CCC69 : public Rva005CCC07
{
public:
	Rva005CCC69(Rva005CCDDD *) throw();
	virtual ~Rva005CCC69();
private:
	Rva005CCDDD *owner;
};
Rva005CCC69::Rva005CCC69(Rva005CCDDD *p) throw() : owner(p)
{
}
