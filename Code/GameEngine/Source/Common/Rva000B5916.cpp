// cl: /MD /Ireference/shims/bfme2_ascii
// ?rva000B5916@Rva000B5916@@QAEXM@Z 0x000B5916 73B evidence: chain via 0x000B2FBB rowed; edi from +0x44 slot0x50 then Rva at this-0xc float Matrix3D+0x18; +0x98 zero +0xa8 StringBase set EmptyString +0x94 1; neighbours 0x000B4E23/0x000B6253
#include "ascii_string.h"

class Matrix3D;
class Rva000B2FBB
{
public:
	void rva000B2FBB(float f, const Matrix3D *m);
};

class Obj000B5916
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20();
};

class Rva000B5916
{
	char _p0[0x44];
	Obj000B5916 *m_obj;
	char _p1[0x94 - 0x44 - 4];
	unsigned char m_94;
	char _p2[0x98 - 0x94 - 1];
	int m_98;
	char _p3[0xa8 - 0x98 - 4];
	StringBase<char> m_str;
public:
	void rva000B5916(float f);
};

void Rva000B5916::rva000B5916(float f)
{
	Obj000B5916 *obj = m_obj;
	if (obj)
	{
		obj->s20();
		Rva000B2FBB *r = (Rva000B2FBB *)((char *)this - 12);
		r->rva000B2FBB(f, (const Matrix3D *)((char *)obj + 24));
	}
	m_98 = 0;
	m_94 = 1;
	m_str.set("");
}
