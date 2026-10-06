// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?get@Rva002722AA@@QBEPAXXZ, retail 0x002722AA, 19 bytes.
// ?get@Rva002722BD@@QBEPAXXZ, retail 0x002722BD, 19 bytes.
// Branched LEA getters selecting interpolated versus logic blocks via
// adjacent flag bytes. Evidence: callers 0x0028E8D4 and 0x002747F9 read the
// same +0x1A4/+0x1A5/+0x38/+0x158 family; first returns matrix-like block
// (+0x158 versus +0x8) whose +0xC/+0x1C/+0x2C floats the caller copies.

class Rva002722AA
{
public:
	void *get() const;
};

class Rva002722BD
{
public:
	void *get() const;
};

void *Rva002722AA::get() const
{
	if (*(char *)((char *)this + 0x1A4) != 0)
		return (char *)this + 0x158;
	return (char *)this + 8;
}

void *Rva002722BD::get() const
{
	if (*(char *)((char *)this + 0x1A5) != 0)
		return (char *)this + 0x18C;
	return (char *)this + 0x38;
}
