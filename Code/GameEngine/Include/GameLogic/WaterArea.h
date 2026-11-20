// The primary WaterArea view used by the chunk readers and writer.
// Retail table 0x00C691EC supplies slots 0 through 5. The setters and the
// base constructor at 0x005380A8 establish the fields through +0x2C.
// This declaration models the primary prefix used by these methods.
#ifndef CANONICAL_WATERAREA_H
#define CANONICAL_WATERAREA_H

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class DataChunkInput;

class WaterArea
{
public:
	virtual ~WaterArea();
	virtual bool v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();

	void parse(DataChunkInput &file, void *userData);
	void rva00537E7C(bool value);
	void rva00537E90(float value);
	void rva00537F74(const AsciiString &value);
	void rva00537FA0(const AsciiString &value);

private:
	friend class Rva00537EAD;

	unsigned char m_pad[0x1C];
	AsciiString m_s20;
	AsciiString m_s24;
	float m_f28;
	bool m_b2C;
};

#endif // CANONICAL_WATERAREA_H
