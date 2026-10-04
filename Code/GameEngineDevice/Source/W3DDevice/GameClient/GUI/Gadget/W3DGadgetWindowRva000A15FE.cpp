// cl: /O1 /DNDEBUG /MD
// ??0Rva000A15FE@@QAE@PAX@Z @0x000A15FE 24B. Ctor forwards void* to base
// Rva0078D310Host 0x00104F8F then stores vtable 0x007C8DB4 (same as
// Rva000A1616Window input/system vtable in W3DGadgetWindowDrawSlots).
// Evidence: gap between 0x000A15EC/0x000A1616 rows sharing these flags;
// callees rowed base ctor and vtable extern g_00BC8DB4; callers 0x0008FC04
// 0x000A164D.
class Rva0078D310Host
{
public:
	Rva0078D310Host(void *context);
};

extern const void *const g_00BC8DB4[];

class Rva000A15FE : public Rva0078D310Host
{
public:
	Rva000A15FE(void *context);
};

Rva000A15FE::Rva000A15FE(void *context)
	: Rva0078D310Host(context)
{
	*(const void **)this = g_00BC8DB4;
}

extern const void *const g_00BC8DE0[];

class Rva000A1646 : public Rva000A15FE
{
public:
	Rva000A1646(void *context);
};

Rva000A1646::Rva000A1646(void *context)
	: Rva000A15FE(context)
{
	*(const void **)this = g_00BC8DE0;
}

extern const void *const g_00BC8D5C[];

class Rva000A12FE : public Rva0078D310Host
{
public:
	Rva000A12FE(void *context);
};

Rva000A12FE::Rva000A12FE(void *context)
	: Rva0078D310Host(context)
{
	*(const void **)this = g_00BC8D5C;
}

extern const void *const g_00BC8D88[];

class Rva000A1346 : public Rva000A12FE
{
public:
	Rva000A1346(void *context);
};

Rva000A1346::Rva000A1346(void *context)
	: Rva000A12FE(context)
{
	*(const void **)this = g_00BC8D88;
}

extern const void *const g_00BC91AC[];

class Rva000A435C : public Rva0078D310Host
{
public:
	Rva000A435C(void *context);
};

Rva000A435C::Rva000A435C(void *context)
	: Rva0078D310Host(context)
{
	*(const void **)this = g_00BC91AC;
}

extern const void *const g_00BC91D8[];

class Rva000A43A4 : public Rva000A435C
{
public:
	Rva000A43A4(void *context);
};

Rva000A43A4::Rva000A43A4(void *context)
	: Rva000A435C(context)
{
	*(const void **)this = g_00BC91D8;
}

extern const void *const g_00BC8CAC[];

class Rva000A0891 : public Rva0078D310Host
{
public:
	Rva000A0891(void *context);
};

Rva000A0891::Rva000A0891(void *context)
	: Rva0078D310Host(context)
{
	*(const void **)this = g_00BC8CAC;
}

extern const void *const g_00BC8CD8[];

class Rva000A08D9 : public Rva000A0891
{
public:
	Rva000A08D9(void *context);
};

Rva000A08D9::Rva000A08D9(void *context)
	: Rva000A0891(context)
{
	*(const void **)this = g_00BC8CD8;
}
