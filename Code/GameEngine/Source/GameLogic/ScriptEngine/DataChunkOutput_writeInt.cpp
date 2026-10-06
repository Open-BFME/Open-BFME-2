// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// DataChunkOutput::writeInt, retail 0x00306CFF (24 bytes).
// DataChunkOutput::writeReal, retail 0x00306CFF (24 bytes, ICF-folded).
// DataChunkOutput::writeByte, retail 0x00306D17 (24 bytes).
// Binary chunk writers; the file handle lives at +0x04. Int and float are
// both four bytes on the stack, so those two bodies fold to identical code;
// byte writes a single byte with the same shape and a smaller size immediate.

extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(
	const void *ptr, unsigned int size, unsigned int count, void *file);

typedef unsigned char WriteByteValue;

class DataChunkOutput
{
public:
	void writeInt(int intValue);
	void writeReal(float realValue);
	void writeByte(WriteByteValue byteValue);

private:
	char pad_0000[4];
	void *file;
};

void DataChunkOutput::writeInt(int intValue)
{
	fwrite(&intValue, 4, 1, file);
}

void DataChunkOutput::writeReal(float realValue)
{
	fwrite(&realValue, 4, 1, file);
}

void DataChunkOutput::writeByte(WriteByteValue byteValue)
{
	fwrite(&byteValue, 1, 1, file);
}
