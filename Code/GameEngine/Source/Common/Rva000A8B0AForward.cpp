// flags: region default (reverse/retail_inventory/flag_regions.csv)
// NativeA8B0A..A8B23 forwards two floats to the event factory10FD5E.
// The callee's rowed ctor10EF14 stores both floats in a20-byte event.
// BFME1 donor BfmeConv2133Forward.cpp at revision6d9434269164392c5ba62aaa7c15a86b5b020d76
// supplied only the instruction shape. Its Shadow::setSize inference is
// refuted by the native factory and is not a target identity.
class Rva0010FD5E
{
public:
	void rva0010FD5E(float first, float second);
};

class Rva000A8B0A
{
public:
	void rva000A8B0A(float first, float second);
};

void Rva000A8B0A::rva000A8B0A(float first, float second)
{
	reinterpret_cast<Rva0010FD5E *>(this)->rva0010FD5E(first, second);
}
