// Target facts (retail 1.06, addresses are RVAs): 0x0040475C clears twenty floats at +0 and +0x50 and dword masks at +0xA0/+0xA4; 0x00404781 updates those arrays and masks. Field names are neutral placeholders.
// CellGrid constructor 0x0056C266 allocates count*0xA8+4 at 0x0056C2A9 and passes stride 0xA8, initializer 0x00404AA5 and empty destructor 0x000B3FD0 at 0x0056C2C3..0x0056C2DC; deleting destructor 0x0056C01E repeats that stride and callback. sizeof is 0xA8, with no bases or virtual functions; initialization and destruction store no vptr.
// Initializer 0x00404AA5 calls reset 0x0040475C and returns this. The ledger names AddDeath (0x00404781), rva0040475C, rva00404AA5 and rva00404CF5 (0x00404CF5); calls at 0x0056C505 and 0x00404B5B retain the out-of-line AddDeath/reset bodies. No original class name is established.

#pragma once

#ifndef BFME2_RVA00404781_H
#define BFME2_RVA00404781_H

class Rva00404781
{
public:
	Rva00404781();
	~Rva00404781();

	void AddDeath(float value, int first, int second);
	void rva0040475C();
	Rva00404781 *rva00404AA5();
	int rva00404CF5(bool useCellRatio);

	float m_a[20];
	float m_b[20];
	unsigned int m_flags0;
	unsigned int m_flags1;
};

typedef char Rva00404781Size[(sizeof(Rva00404781) == 0xA8) ? 1 : -1];

#endif
