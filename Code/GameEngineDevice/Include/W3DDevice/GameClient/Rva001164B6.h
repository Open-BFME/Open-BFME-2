#ifndef BFME2_RVA001164B6_H
#define BFME2_RVA001164B6_H

class AsciiString;

// The constructor at 0x0011646E installs the five-slot table at
// 0x007CFB24 and clears the byte at +4. Slot 1 is the deleting destructor.
class Rva001164B6
{
public:
	Rva001164B6();
	virtual AsciiString rva00111BE9() const = 0;
	virtual ~Rva001164B6();
	virtual void rva00111DB6() = 0;
	virtual void rva00111D65() = 0;
	virtual void doApply() = 0;

private:
	unsigned char m_04;
};

#endif
