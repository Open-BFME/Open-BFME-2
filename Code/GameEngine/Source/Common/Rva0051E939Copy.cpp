// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0051E939Copy@@YAPAVRva0051E437@@PAV1@00@Z @0x0051E939 50B: counted copy of Rva0051E437 array via rowed rva0051E437; n=(last-first); callers 0x0051EC31
class Rva0051E437
{
public:
	Rva0051E437 &rva0051E437(const Rva0051E437 &src);
private:
	int m00;
	unsigned short m04;
	unsigned short m06;
	unsigned short m08;
};
Rva0051E437 *Rva0051E939Copy(Rva0051E437 *first, Rva0051E437 *last, Rva0051E437 *result)
{
	int n = last - first;
	if (n <= 0)
		return result;
	int count = n;
	do
	{
		result->rva0051E437(*first);
		++first;
		++result;
		--count;
	} while (count != 0);
	return result;
}
