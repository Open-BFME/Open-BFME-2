// flags: region default (reverse/retail_inventory/flag_regions.csv)

class Rva000A9DF8ObjA
{
public:
	void Set(int value);
};

class Rva000A9DF8ObjB
{
public:
	void Set(int value);
};

class Rva000A9DF8ObjC
{
public:
	void Set(int value);
};

void Rva000A9DF8FireA(Rva000A9DF8ObjA *obj, int value)
{
	if (obj)
		obj->Set(value);
}

void Rva000A9DF8FireB(Rva000A9DF8ObjB *obj, int value)
{
	if (obj)
		obj->Set(value);
}

void Rva000A9DF8FireC(Rva000A9DF8ObjC *obj, int value)
{
	if (obj)
		obj->Set(value);
}
