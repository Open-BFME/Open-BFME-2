// Two disp32 compare bool getters split out of Disp8CmpBoolGetters.cpp: each
// tests the dword at this+0x1E0 against a code address (retail compares it
// with the VAs 0x008020CE and 0x00727E5D, the rowed window input callbacks
// LeftHUDInput 0x004020CE and GadgetPushButtonInput 0x00327E5D, so +0x1E0 is
// a GameWindow input callback). Identity is not recovered: names derive from
// the addresses.
// flags: region default (reverse/retail_inventory/flag_regions.csv)

enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };
class GameWindow;
WindowMsgHandledType LeftHUDInput(GameWindow *window, unsigned int msg, unsigned int mData1, unsigned int mData2);
WindowMsgHandledType GadgetPushButtonInput(GameWindow *window, unsigned int msg, unsigned int mData1, unsigned int mData2);

#define BFME_DISP8_CMP_IMM_BOOL_GETTER(NAME, DISP, IMM, OP) \
	class NAME \
	{ \
	public: \
		bool get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	bool NAME::get() const \
	{ \
		return m_value OP IMM; \
	}

BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva00313913CmpBoolField, 0x1E0, (int)&LeftHUDInput, ==)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva0031393ACmpBoolField, 0x1E0, (int)&GadgetPushButtonInput, ==)
