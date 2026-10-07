// Target evidence: the 69-byte body at RVA 0x00105CF6 reads the first pointer
// from its first argument, advances non-null data by 8 bytes, and calls the
// routine at 0x00158BA0 on the subobject at this+4 with a two-float output.
// It conditionally converts those floats to the two output integers. The null
// fallback is the wide null character at 0x007BB5C4. Identity and class names
// remain address-derived; the callee body is not recovered here.
extern unsigned short g_Va007BB5C4;

class Rva00158BA0
{
public:
	void rva00158BA0(float *extent, const unsigned short *text);
};

class Rva00105CF6
{
private:
	char m_prefix[4];
	Rva00158BA0 m_text_measure;

public:
	void rva00105CF6(const unsigned short **text_data, int *width, int *height);
};

// ?rva00105CF6@Rva00105CF6@@QAEXPAPBGPAH1@Z
void Rva00105CF6::rva00105CF6(const unsigned short **text_data, int *width, int *height)
{
	float extent[2];
	const unsigned short *data = *text_data;
	const unsigned short *text = data != 0
		? (const unsigned short *)((const char *)data + 8)
		: &g_Va007BB5C4;

	m_text_measure.rva00158BA0(extent, text);
	if (width != 0) {
		*width = (int)extent[0];
	}
	if (height != 0) {
		*height = (int)extent[1];
	}
}
