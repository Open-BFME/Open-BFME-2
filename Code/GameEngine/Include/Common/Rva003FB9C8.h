// Both setters write five integer fields, then dispatch through vtable offset 0x0C.
#ifndef CANONICAL_RVA003FB9C8_H
#define CANONICAL_RVA003FB9C8_H

class Rva003FB9C8
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	void rva003FB9C8(int a, int b);
	void rva003FB9EB(int a, int b);
private:
	char m_pad04[0x28];
	int m_2c;
	char m_pad30[4];
	int m_34;
	int m_38;
	char m_pad3C[0x10];
	int m_4c;
	int m_50;
};

#endif // CANONICAL_RVA003FB9C8_H
