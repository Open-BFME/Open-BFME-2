#ifndef BFME2_NETWORK_TRANSPORT_H
#define BFME2_NETWORK_TRANSPORT_H

// BFME 2 Transport layout retained from the byte-verified home unit.
// Target evidence: 0x004D53B5 clears two 128-entry rings at stride 0x40E,
// eight 12-byte slots at +0x40E0C, and six 30-word statistics arrays.
// 0x004D51A7 and 0x004D51ED independently witness both address words.
// WorldBuilder Transport.cpp supplies the class/setter identity; private
// field labels below describe offsets, without asserting original names.
// Header adoption is gated per unit; incompatible views remain queued.

class Rva00594DC0;

struct Rva004D4A80Slot
{
	void *m_object;
	int m_x;
	short m_y;
	char m_pad[2];
	Rva004D4A80Slot(void);
	~Rva004D4A80Slot(void) {}
};

class Transport
{
public:
	Transport(void);
	bool allowBroadcasts(bool allowBroadcasts);
	~Transport(void);
	void RemoveSocketForSlot(unsigned short index);
	void Rva004D5496(void);
	void clearBuffer_Rva004D4A59(void);
	bool rva004D53B5(void *addr);
	void setSlotSocket(void *obj, unsigned short index, int *vals);
	void setDestAddrToSocket(int index, void *address);
	bool doRecv(Rva00594DC0 *receiver);
	bool update(Rva00594DC0 *receiver);
	bool doSend();

private:
#pragma pack(push, 1)
	struct Message
	{
		unsigned int m_crc;
		unsigned char m_data[0x400];
		int m_length; // +0x404
		unsigned long m_addr;
		unsigned short m_port;
	};
#pragma pack(pop)
	Message m_outBuffer[128];
	Message m_inBuffer[128];
	bool m_flag40E00;
	void *m_ptr40E04;
	bool m_winsockActive;
	// Eight 12-byte slots at +0x40E0C. The first word holds the slot's
	// object pointer (the clearer compares and zeroes it); the element
	// constructor zeroes the first ten bytes and the destructor is an
	// empty inline, folded with the other empty dtors.
	Rva004D4A80Slot m_slots[8];
	int m_int40E6C;
	int m_int40E70;
	int m_stats0[30];
	int m_stats1[30];
	int m_stats2[30];
	int m_stats3[30];
	int m_stats4[30];
	int m_stats5[30];
	int m_badPackets;
};

typedef char TransportSizeWitness[(sizeof(Transport) == 0x41148) ? 1 : -1];

#endif
