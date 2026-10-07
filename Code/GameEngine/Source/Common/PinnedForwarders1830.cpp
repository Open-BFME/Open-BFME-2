// cl: /MD /DNDEBUG
//
// Four tiny members already pinned under placeholder names, each a guarded
// forward to one callee (pinned here under its address):
//   0x0030B719 19B Rva0030B719Shape::getRadius  - refresh via 0x0030B3D1
//                                                  while +0x24 is set, then
//                                                  return the float at +0x20
//   0x002B3740 19B Rva002BA8F1Logic::rva002B3740 - byte +0xA8 of what
//                                                  0x002B2B2D returns, or false
//   0x000A8AC0 12B MilesStreamRef::rva000A8AC0   - tail call 0x0010FB64 on the
//                                                  referenced stream if any
//   0x001ECEF6 13B Rva0023D607Holder::rva001ECEF6 - tail call 0x001ECE98 on
//                                                  the +0x10 member if any
// Plus twenty wave-3 family members of the same guarded-tailcall shape,
// each `if (member) member->callee(args...)` with the member at +0x0 (plain
// or global g_Va00A03314), disp8 (+0x4/+0x8/+0xC/+0x10/+0x20) or disp32
// (+0x2DC/+0x450/+0x7F4/+0x3850), cleaning 0, 4 or 8 stack bytes to match
// the forwarded arg count. Callees are pinned here under their addresses.
// Identities beyond these shapes are not recovered.

typedef bool Bool;
typedef float Real;

struct Region2D
{
	Region2D(const Region2D &that);
	float x_min;
	float y_min;
	float x_max;
	float y_max;
};

struct Rva0030B72CPoint
{
	Rva0030B72CPoint() {}
	__forceinline Rva0030B72CPoint(const Rva0030B72CPoint &that)
	{
		x = that.x;
		y = that.y;
	}
	float x, y;
};

class Rva0030B719Shape
{
public:
	Real getRadius() const;
	Region2D rva0030B6E3();
	Real rva0030B706() const;
	Rva0030B72CPoint rva0030B72C() const;
	void rva0030B3D1();
private:
	unsigned char m_pad00[0x0C];
	Region2D m_region; // +0x0C
	Real m_1C; // +0x1C
	Real m_radius; // +0x20
	Bool m_dirty; // +0x24
};

Real Rva0030B719Shape::getRadius() const
{
	if (m_dirty)
		const_cast<Rva0030B719Shape *>(this)->rva0030B3D1();
	return m_radius;
}

Real Rva0030B719Shape::rva0030B706() const
{
	if (m_dirty)
		const_cast<Rva0030B719Shape *>(this)->rva0030B3D1();
	return m_1C;
}

Region2D Rva0030B719Shape::rva0030B6E3()
{
	if (m_dirty)
		rva0030B3D1();
	return m_region;
}

// Native 30B72C..30B76F returns the midpoint of the measured bounds.
// ZH PolygonTrigger::getCenterPoint supports the role; BFME2's shape owner
// and original value-type identity remain unknown.
Rva0030B72CPoint Rva0030B719Shape::rva0030B72C() const
{
	if (m_dirty)
		const_cast<Rva0030B719Shape *>(this)->rva0030B3D1();
	Rva0030B72CPoint result;
	result.x = (m_region.x_max + m_region.x_min) * 0.5f;
	result.y = (m_region.y_max + m_region.y_min) * 0.5f;
	return result;
}

struct Rva002B3740Item
{
	unsigned char m_pad00[0xA8];
	Bool m_flag;
};

class Rva002BA8F1Logic
{
public:
	Bool rva002B3740();
	Rva002B3740Item *rva002B2B2D();
};

Bool Rva002BA8F1Logic::rva002B3740()
{
	Rva002B3740Item *item = rva002B2B2D();
	if (item)
		return item->m_flag;
	return false;
}

class MilesStream
{
public:
	void rva0010FB64();
};

class MilesStreamRef
{
public:
	void rva000A8AC0();
private:
	MilesStream *m_stream;
};

void MilesStreamRef::rva000A8AC0()
{
	if (m_stream)
		m_stream->rva0010FB64();
}

class Rva001ECE98
{
public:
	void rva001ECE98();
};

class Rva0023D607Holder
{
public:
	void rva001ECEF6();
private:
	unsigned char m_pad00[0x10];
	Rva001ECE98 *m_10;
};

void Rva0023D607Holder::rva001ECEF6()
{
	if (m_10)
		m_10->rva001ECE98();
}

class Rva002D335B
{
public:
	void rva002D335B();
};

class Rva0004E4BD
{
public:
	void rva0004E4BD();
private:
	Rva002D335B *m_ptr;
};

void Rva0004E4BD::rva0004E4BD()
{
	if (m_ptr)
		m_ptr->rva002D335B();
}

class Rva0010FA6B
{
public:
	void rva0010FA6B(int a);
};

class Rva000A8AA6
{
public:
	void rva000A8AA6(int a);
private:
	Rva0010FA6B *m_ptr;
};

void Rva000A8AA6::rva000A8AA6(int a)
{
	if (m_ptr)
		m_ptr->rva0010FA6B(a);
}

class Rva003626AD
{
public:
	void rva003626AD(int a, int b);
};

class Rva00271BCC
{
public:
	void rva00271BCC(int a, int b);
private:
	unsigned char m_pad00[0x450];
	Rva003626AD *m_450;
};

void Rva00271BCC::rva00271BCC(int a, int b)
{
	if (m_450)
		m_450->rva003626AD(a, b);
}

class Rva000EDB47
{
public:
	void rva000EDB47();
};

class Rva00068D43
{
public:
	void rva00068D43();
private:
	unsigned char m_pad00[0x3850];
	Rva000EDB47 *m_3850;
};

void Rva00068D43::rva00068D43()
{
	if (m_3850)
		m_3850->rva000EDB47();
}

class Rva0010FAEA
{
public:
	void rva0010FAEA();
};

class Rva000A8AB4
{
public:
	void rva000A8AB4();
private:
	Rva0010FAEA *m_ptr;
};

void Rva000A8AB4::rva000A8AB4()
{
	if (m_ptr)
		m_ptr->rva0010FAEA();
}

class Rva0010FBDE
{
public:
	void rva0010FBDE();
};

class Rva000A8ACC
{
public:
	void rva000A8ACC();
private:
	Rva0010FBDE *m_ptr;
};

void Rva000A8ACC::rva000A8ACC()
{
	if (m_ptr)
		m_ptr->rva0010FBDE();
}

class Rva0010FDE9
{
public:
	void rva0010FDE9(int a);
};

class Rva000A8B23
{
public:
	void rva000A8B23(int a);
private:
	Rva0010FDE9 *m_ptr;
};

void Rva000A8B23::rva000A8B23(int a)
{
	if (m_ptr)
		m_ptr->rva0010FDE9(a);
}

class Rva0010FEF3
{
public:
	void rva0010FEF3(int a);
};

class Rva000A8B4B
{
public:
	void rva000A8B4B(int a);
private:
	Rva0010FEF3 *m_ptr;
};

void Rva000A8B4B::rva000A8B4B(int a)
{
	if (m_ptr)
		m_ptr->rva0010FEF3(a);
}

class Rva0010FFA2
{
public:
	void rva0010FFA2(int a);
};

class Rva000A8C6E
{
public:
	void rva000A8C6E(int a);
private:
	Rva0010FFA2 *m_ptr;
};

void Rva000A8C6E::rva000A8C6E(int a)
{
	if (m_ptr)
		m_ptr->rva0010FFA2(a);
}

class Rva001EB68A
{
public:
	void rva001EB68A();
};

class Rva001EB72F
{
public:
	void rva001EB72F();
private:
	unsigned char m_pad00[0x10];
	Rva001EB68A *m_10;
};

void Rva001EB72F::rva001EB72F()
{
	if (m_10)
		m_10->rva001EB68A();
}

class Rva001EB6FE
{
public:
	void rva001EB6FE();
};

class Rva001EB75C
{
public:
	void rva001EB75C();
private:
	unsigned char m_pad00[0x10];
	Rva001EB6FE *m_10;
};

void Rva001EB75C::rva001EB75C()
{
	if (m_10)
		m_10->rva001EB6FE();
}

class Rva0020E9A1
{
public:
	void rva0020E9A1();
};

class Rva0020EB41
{
public:
	void rva0020EB41();
private:
	unsigned char m_pad00[8];
	Rva0020E9A1 *m_8;
};

void Rva0020EB41::rva0020EB41()
{
	if (m_8)
		m_8->rva0020E9A1();
}

class Rva004E5EBE
{
public:
	void rva004E5EBE(int a, int b);
};

class Rva0029B16A
{
public:
	void rva0029B16A(int a, int b);
private:
	unsigned char m_pad00[0x7F4];
	Rva004E5EBE *m_7F4;
};

void Rva0029B16A::rva0029B16A(int a, int b)
{
	if (m_7F4)
		m_7F4->rva004E5EBE(a, b);
}

class Rva004F2ABC
{
public:
	void rva004F2ABC(int a, int b);
};

class Rva002A9CDE
{
public:
	void rva002A9CDE(int a, int b);
private:
	unsigned char m_pad00[0x2DC];
	Rva004F2ABC *m_2DC;
};

void Rva002A9CDE::rva002A9CDE(int a, int b)
{
	if (m_2DC)
		m_2DC->rva004F2ABC(a, b);
}

class Rva004F0819
{
public:
	void rva004F0819(int a);
};

class Rva002A9CF0
{
public:
	void rva002A9CF0(int a);
private:
	unsigned char m_pad00[0x2DC];
	Rva004F0819 *m_2DC;
};

void Rva002A9CF0::rva002A9CF0(int a)
{
	if (m_2DC)
		m_2DC->rva004F0819(a);
}

class Rva004F2C14
{
public:
	void rva004F2C14(int a);
};

class Rva002A9DEC
{
public:
	void rva002A9DEC(int a);
private:
	unsigned char m_pad00[0x2DC];
	Rva004F2C14 *m_2DC;
};

void Rva002A9DEC::rva002A9DEC(int a)
{
	if (m_2DC)
		m_2DC->rva004F2C14(a);
}

struct GlobalA03314;
extern GlobalA03314 *g_Va00A03314;

class Rva0043CD3C
{
public:
	void rva0043CD3C();
};

class Rva0043D15F
{
public:
	void rva0043D15F();
};

void Rva0043D15F::rva0043D15F()
{
	Rva0043CD3C *p = (Rva0043CD3C *)g_Va00A03314;
	if (p)
		p->rva0043CD3C();
}

class Rva004E0D19
{
public:
	void rva004E0D19(int a);
};

class Rva004FC176
{
public:
	void rva004FC176(int a);
private:
	unsigned char m_pad00[0x20];
	Rva004E0D19 *m_20;
};

void Rva004FC176::rva004FC176(int a)
{
	if (m_20)
		m_20->rva004E0D19(a);
}

class Rva005CB283
{
public:
	void rva005CB283();
};

class Rva005CCB16
{
public:
	void rva005CCB16();
private:
	unsigned char m_pad00[4];
	Rva005CB283 *m_4;
};

void Rva005CCB16::rva005CCB16()
{
	if (m_4)
		m_4->rva005CB283();
}

class Rva000B3FD0
{
public:
	void rva000B3FD0();
};

class Rva005D13D5
{
public:
	void rva005D13D5();
private:
	unsigned char m_pad00[0xC];
	Rva000B3FD0 *m_C;
};

void Rva005D13D5::rva005D13D5()
{
	if (m_C)
		m_C->rva000B3FD0();
}

// Native 2B3B66..2B3BCF: no stack arguments; walks an array of
// groups at +8C/+90 and each group's array at +1B8/+1BC, invoking
// the verified dirty-coordinate method 319E7C on every element.
// The original receiver and group names remain unknown.
class Rva003195C9Owner
{
public:
    void rva00319E7C();
};
struct Rva002B3B66Range
{
    Rva003195C9Owner **begin, **end;
    unsigned size() const { return static_cast<unsigned>(end - begin); }
};
struct Rva002B3B66Group
{
    unsigned char pad[0x1B8];
    Rva002B3B66Range items;
};
struct Rva002B3B66Groups
{
    Rva002B3B66Group **begin, **end;
    unsigned size() const { return static_cast<unsigned>(end - begin); }
    Rva002B3B66Group *operator[](unsigned i) const { return begin[i]; }
};
class Rva002B3B66
{
public:
    void rva002B3B66();
private:
    unsigned char pad[0x8C];
    Rva002B3B66Groups groups;
};
void Rva002B3B66::rva002B3B66()
{
    for (unsigned i = 0; i < groups.size(); ++i)
    {
        Rva002B3B66Range &range = groups[i]->items;
        for (unsigned j = 0; j < range.size(); ++j)
            range.begin[j]->rva00319E7C();
    }
}
