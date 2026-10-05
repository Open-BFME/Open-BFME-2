// cl: /O1 /DNDEBUG /MD /EHsc /Oy- /G7
//
// Twenty-three keyed Drawable lookups, each 25 bytes: forward the hidden
// return pointer and a constant key (0x21..0x37) to the Drawable member at
// 0x0027675F (DrawableKeyedLookup.cpp) and return the Rva002390CB it
// builds. The wrappers pass `this` through untouched, so they are
// members of the same class; the pushed-ecx slot zeroed first is MSVC's
// return-object flag for a class with a destructor. Retail scatters them
// over several units (inline members emitted where first used); the keys
// identify them, the names stay address-derived. Flags follow the Drawable
// units; the wrappers compile identically without /EHsc.

class Rva002390CB
{
public:
	Rva002390CB(const Rva002390CB &other);
	~Rva002390CB();

private:
	char m_pad[8];
};

class Drawable
{
public:
	Rva002390CB rva0027675F(int key);

	Rva002390CB rva00346C79(); // key 0x21
	Rva002390CB rva00346C92(); // key 0x22
	Rva002390CB rva00346CAB(); // key 0x23
	Rva002390CB rva00346CC4(); // key 0x24
	Rva002390CB rva0027682F(); // key 0x25
	Rva002390CB rva00276848(); // key 0x26
	Rva002390CB rva00276861(); // key 0x27
	Rva002390CB rva0027687A(); // key 0x28
	Rva002390CB rva00276893(); // key 0x29
	Rva002390CB rva00374389(); // key 0x2A
	Rva002390CB rva003743A2(); // key 0x2B
	Rva002390CB rva0049D114(); // key 0x2C
	Rva002390CB rva004BE120(); // key 0x2D
	Rva002390CB rva004BE139(); // key 0x2E
	Rva002390CB rva00462D95(); // key 0x2F
	Rva002390CB rva00462DAE(); // key 0x30
	Rva002390CB rva004BE152(); // key 0x31
	Rva002390CB rva004BE16B(); // key 0x32
	Rva002390CB rva004BE184(); // key 0x33
	Rva002390CB rva00462DC7(); // key 0x34
	Rva002390CB rva0028F8E0(); // key 0x35
	Rva002390CB rva0028F8F9(); // key 0x36
	Rva002390CB rva0028F912(); // key 0x37
};

Rva002390CB Drawable::rva00346C79()
{
	return rva0027675F(0x21);
}

Rva002390CB Drawable::rva00346C92()
{
	return rva0027675F(0x22);
}

Rva002390CB Drawable::rva00346CAB()
{
	return rva0027675F(0x23);
}

Rva002390CB Drawable::rva00346CC4()
{
	return rva0027675F(0x24);
}

Rva002390CB Drawable::rva0027682F()
{
	return rva0027675F(0x25);
}

Rva002390CB Drawable::rva00276848()
{
	return rva0027675F(0x26);
}

Rva002390CB Drawable::rva00276861()
{
	return rva0027675F(0x27);
}

Rva002390CB Drawable::rva0027687A()
{
	return rva0027675F(0x28);
}

Rva002390CB Drawable::rva00276893()
{
	return rva0027675F(0x29);
}

Rva002390CB Drawable::rva00374389()
{
	return rva0027675F(0x2A);
}

Rva002390CB Drawable::rva003743A2()
{
	return rva0027675F(0x2B);
}

Rva002390CB Drawable::rva0049D114()
{
	return rva0027675F(0x2C);
}

Rva002390CB Drawable::rva004BE120()
{
	return rva0027675F(0x2D);
}

Rva002390CB Drawable::rva004BE139()
{
	return rva0027675F(0x2E);
}

Rva002390CB Drawable::rva00462D95()
{
	return rva0027675F(0x2F);
}

Rva002390CB Drawable::rva00462DAE()
{
	return rva0027675F(0x30);
}

Rva002390CB Drawable::rva004BE152()
{
	return rva0027675F(0x31);
}

Rva002390CB Drawable::rva004BE16B()
{
	return rva0027675F(0x32);
}

Rva002390CB Drawable::rva004BE184()
{
	return rva0027675F(0x33);
}

Rva002390CB Drawable::rva00462DC7()
{
	return rva0027675F(0x34);
}

Rva002390CB Drawable::rva0028F8E0()
{
	return rva0027675F(0x35);
}

Rva002390CB Drawable::rva0028F8F9()
{
	return rva0027675F(0x36);
}

Rva002390CB Drawable::rva0028F912()
{
	return rva0027675F(0x37);
}
