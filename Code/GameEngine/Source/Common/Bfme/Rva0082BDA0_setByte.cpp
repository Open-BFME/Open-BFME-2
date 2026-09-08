// cl: /DNDEBUG /MD /EHsc

class Rva0082BDA0
{
public:
	void *setByte(unsigned char value);
};

#pragma optimize("y", off)
void *Rva0082BDA0::setByte(unsigned char value)
{
	Rva0082BDA0 * volatile self = this;
	*reinterpret_cast<unsigned char *>(self) = value;
	return const_cast<Rva0082BDA0 *>(self);
}
#pragma optimize("y", on)
