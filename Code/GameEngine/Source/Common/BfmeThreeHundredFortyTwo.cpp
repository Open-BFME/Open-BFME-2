// cl: /O1 /G7 /MD
// Rva0052163E::Rva0052163E, retail 0x00521623 (27 bytes).
//
// Target evidence: the body runs the input-route base constructor
// 0x0031454D, stores its argument at +0xC and installs vftable 0x00C67840,
// whose slot 0 is the scalar deleting destructor 0x00444067 that calls this
// class's destructor 0x0052163E (both rowed under Rva0052163E). AptSkirmish's
// constructor 0x00522B0E builds one at +0x6C8 with the argument 10, so it is
// a constructor taking an int. Donor: BFME 1 0x00511190 is byte-identical
// (rowed there as the placeholder BfmeThingTC::bfmeInitTC).
class Rva0031455E {
public:
 Rva0031455E();
 virtual ~Rva0031455E();
 virtual void Rva0031455ELink(Rva0031455E *);
 virtual void Rva00314581Unlink();
private: void *next; void *window;
};

class Rva0052163E : public Rva0031455E
{
public:
	Rva0052163E(int count);
	virtual ~Rva0052163E();
	virtual int input(unsigned int msg, unsigned int data1, unsigned int data2);
private:
	int m_count;
};

Rva0052163E::Rva0052163E(int count) : m_count(count)
{
}
