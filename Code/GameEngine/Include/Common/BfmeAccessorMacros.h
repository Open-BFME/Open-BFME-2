// Accessor macros shared by the units that declare one-method views of a class at a fixed displacement.
#pragma once
#ifndef BFME_ACCESSOR_MACROS_H
#define BFME_ACCESSOR_MACROS_H

#define BFME_ARG_FIELD_SETTER(NAME, TYPE, DISP) \
	class NAME \
	{ \
	public: \
		void set(TYPE value); \
		char m_lead[DISP]; \
		TYPE m_value; \
	}; \
	void NAME::set(TYPE value) \
	{ \
		m_value = value; \
	}

#define BFME_ASCII_FIELD_CLEAR(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void clear(); \
	private: \
		char m_pad[DISP]; \
		AsciiString m_str; \
	}; \
	void NAME::clear() \
	{ \
		((StringBase<char> *)&m_str)->clear(); \
	}

#define BFME_ASCII_FIELD_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(const AsciiString &s); \
	private: \
		char m_pad[DISP]; \
		AsciiString m_str; \
	}; \
	void NAME::set(const AsciiString &s) \
	{ \
		return ((StringBase<char> &)m_str).set((const StringBase<char> &)s); \
	}

#define BFME_ASCII_FIELD_SET_CSTR(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(const char *s); \
	private: \
		char m_pad[DISP]; \
		AsciiString m_str; \
	}; \
	void NAME::set(const char *s) \
	{ \
		((StringBase<char> *)&m_str)->set(s); \
	}

#define BFME_BACK_POINTER_OFFSET( NAME, BACK, OFFSET )                        \
	class Sub##NAME                                                           \
	{                                                                         \
	public:                                                                   \
		char *m_base;                                                         \
	};                                                                        \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		char *get() const;                                                    \
	};                                                                        \
	char *NAME::get() const                                                   \
	{                                                                         \
		return ( (const Sub##NAME *)( (const char *)this - ( BACK ) ) )->m_base \
			+ ( OFFSET );                                                     \
	}

#define BFME_BLOCK_ASSIGN( NAME, LEAD, DWORDS )                               \
	struct Block##NAME                                                        \
	{                                                                         \
		unsigned int m_dword[ DWORDS ];                                       \
	};                                                                        \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		void set( const Block##NAME &value );                                 \
                                                                              \
		char         m_lead[ LEAD ];                                          \
		Block##NAME  m_block;                                                 \
	};                                                                        \
	void NAME::set( const Block##NAME &value ) { m_block = value; }

#define BFME_BLOCK_MEMCPY_ASSIGN( NAME, LEAD )                                 \
	struct Block##NAME                                                        \
	{                                                                         \
		unsigned int m_dword[ 3 ];                                            \
	};                                                                        \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		void set( const Block##NAME &value );                                 \
                                                                              \
		char        m_lead[ LEAD ];                                           \
		Block##NAME m_block;                                                  \
	};                                                                        \
	void NAME::set( const Block##NAME &value )                                \
	{                                                                         \
		m_block = value;                                                      \
	}

#define BFME_CHAIN_DTOR( NAME, SECOND )                                   \
	class NAME : public BigChainHold, public SECOND                       \
	{                                                                     \
	public:                                                               \
		__declspec(noinline) ~NAME();                                     \
	};

#define BFME_DISP0_DWORD_GETTER(NAME) \
	class NAME \
	{ \
	public: \
		int get() const; \
		int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return m_value; \
	}

#define BFME_DISP32_BACK_BYTECHASE_GETTER(NAME, BACK, DISP2) \
	class NAME \
	{ \
	public: \
		unsigned char get() const; \
	}; \
	unsigned char NAME::get() const \
	{ \
		return *(unsigned char *)((char *)*(void *const *)((char *)this - (BACK)) + (DISP2)); \
	}

#define BFME_DISP32_BACK_FLOATCHASE_GETTER(NAME, BACK, DISP2) \
	class NAME \
	{ \
	public: \
		float get() const; \
	}; \
	float NAME::get() const \
	{ \
		return *(float *)((char *)*(void *const *)((char *)this - (BACK)) + (DISP2)); \
	}

#define BFME_DISP32_BACK_PTRCHASE_GETTER(NAME, BACK, DISP2) \
	class NAME \
	{ \
	public: \
		int get() const; \
	}; \
	int NAME::get() const \
	{ \
		return *(int *)((char *)*(void *const *)((char *)this - (BACK)) + (DISP2)); \
	}

#define BFME_DISP32_BYTE_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		unsigned char get() const; \
		char m_lead[DISP]; \
		unsigned char m_value; \
	}; \
	unsigned char NAME::get() const \
	{ \
		return m_value; \
	}

#define BFME_DISP32_CVT_FLOAT_INT_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		float m_value; \
	}; \
	int NAME::get() const \
	{ \
		return (int)m_value; \
	}

#define BFME_DISP32_DWORD_CLEAR(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void clear(); \
		char m_lead[DISP]; \
		int m_counter; \
	}; \
	void NAME::clear() \
	{ \
		m_counter = 0; \
	}

#define BFME_DISP32_DWORD_DEC(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void dec(); \
		char m_lead[DISP]; \
		int m_counter; \
	}; \
	void NAME::dec() \
	{ \
		--m_counter; \
	}

#define BFME_DISP32_DWORD_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return m_value; \
	}

#define BFME_DISP32_DWORD_INC(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void inc(); \
		char m_lead[DISP]; \
		int m_counter; \
	}; \
	void NAME::inc() \
	{ \
		++m_counter; \
	}

#define BFME_DISP32_FIRST_PTRCHASE_GETTER(NAME, DISP1, DISP2) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP1]; \
		void *m_ptr; \
	}; \
	int NAME::get() const \
	{ \
		return *(int *)((char *)m_ptr + DISP2); \
	}

#define BFME_DISP32_FIRST_WORDCHASE_ZERO_GETTER(NAME, DISP1) \
	class Inner##NAME \
	{ \
	public: \
		short m_value; \
	}; \
	class Sub##NAME \
	{ \
	public: \
		Inner##NAME *m_holder; \
	}; \
	class NAME \
	{ \
	public: \
		int get() const; \
	}; \
	int NAME::get() const \
	{ \
		return ((const Sub##NAME *)((const char *)this + (DISP1)))->m_holder->m_value; \
	}

#define BFME_DISP32_FLOAT_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		float get() const; \
		char m_lead[DISP]; \
		float m_value; \
	}; \
	float NAME::get() const \
	{ \
		return m_value; \
	}

#define BFME_DISP32_FLOAT_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(float newValue); \
		char m_leadingPadding[DISP]; \
		float m_floatValue; \
	}; \
	void NAME::set(float newValue) \
	{ \
		m_floatValue = newValue; \
	}

#define BFME_DISP32_INT_PAIR_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void get(Disp32IntPair &result); \
		char m_leadingPadding[DISP]; \
		Disp32IntPair m_pairValue; \
	}; \
	void NAME::get(Disp32IntPair &result) \
	{ \
		result = m_pairValue; \
	}

#define BFME_DISP32_INT_TO_FLOAT_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(int newValue); \
		char m_leadingPadding[DISP]; \
		float m_floatValue; \
	}; \
	void NAME::set(int newValue) \
	{ \
		m_floatValue = (float)newValue; \
	}

#define BFME_DISP32_LEA_BEFORE_GETTER(NAME, BACK) \
	class NAME \
	{ \
	public: \
		void *get() const; \
	}; \
	void *NAME::get() const \
	{ \
		return (char *)this - (BACK); \
	}

#define BFME_DISP32_LEA_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void *get() const; \
	}; \
	void *NAME::get() const \
	{ \
		return (char *)this + DISP; \
	}

#define BFME_DISP32_MOVZX_BYTE_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		unsigned int get() const; \
		char m_lead[DISP]; \
		unsigned char m_value; \
	}; \
	unsigned int NAME::get() const \
	{ \
		return m_value; \
	}

#define BFME_DISP32_MOVZX_WORD_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		unsigned int get() const; \
		char m_lead[DISP]; \
		unsigned short m_value; \
	}; \
	unsigned int NAME::get() const \
	{ \
		return m_value; \
	}

#define BFME_DISP8_ADD_BEFORE_DWORD_GETTER(NAME, BACK, IMM) \
	class NAME \
	{ \
	public: \
		int get() const; \
	}; \
	int NAME::get() const \
	{ \
		return *(const int *)((const char *)this - (BACK)) + (IMM); \
	}

#define BFME_DISP8_ADD_DWORD_GETTER(NAME, DISP, IMM) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return m_value + IMM; \
	}

#define BFME_DISP8_ADD_IMM32_BEFORE_DWORD_GETTER(NAME, BACK, IMM) \
	class NAME \
	{ \
	public: \
		int get() const; \
	}; \
	int NAME::get() const \
	{ \
		return *(const int *)((const char *)this - (BACK)) + (IMM); \
	}

#define BFME_DISP8_ADD_IMM32_DWORD_GETTER(NAME, DISP, IMM) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return m_value + IMM; \
	}

#define BFME_DISP8_BACK_PTR_TERNARY_BOOL_GETTER(NAME, BACK, INNER_DISP) \
	struct NAME##Inner \
	{ \
		char m_pad[INNER_DISP]; \
		unsigned char m_b; \
	}; \
	struct NAME##Outer; \
	class NAME##Sub \
	{ \
	public: \
		bool get() const; \
	}; \
	struct NAME##Outer \
	{ \
		NAME##Inner *m_ptr; \
		char m_fill[BACK - 4]; \
		NAME##Sub m_sub; \
	}; \
	bool NAME##Sub::get() const \
	{ \
		return ((NAME##Outer *)((char *)this - BACK))->m_ptr->m_b ? true : false; \
	}

#define BFME_DISP8_BINARY_ADD_GETTER(NAME, DISP1, DISP2) \
	class NAME \
	{ \
	public: \
		int get() const; \
	}; \
	int NAME::get() const \
	{ \
		return *(const int *)((const char *)this + (DISP1)) + *(const int *)((const char *)this + (DISP2)); \
	}

#define BFME_DISP8_BINARY_SUB_GETTER(NAME, DISP1, DISP2) \
	class NAME \
	{ \
	public: \
		int get() const; \
	}; \
	int NAME::get() const \
	{ \
		return *(const int *)((const char *)this + (DISP1)) - *(const int *)((const char *)this + (DISP2)); \
	}

#define BFME_DISP8_BUMP_COUNTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		int bump(); \
		char m_lead[DISP]; \
		int m_counter; \
	}; \
	int NAME::bump() \
	{ \
		return ++m_counter; \
	}

#define BFME_DISP8_BYTECHASE_BEFORE_GETTER(NAME, BACK, INNER) \
	class Inner##NAME \
	{ \
	public: \
		char m_lead[INNER]; \
		unsigned char m_value; \
	}; \
	class Sub##NAME \
	{ \
	public: \
		Inner##NAME *m_holder; \
	}; \
	class NAME \
	{ \
	public: \
		unsigned char get() const; \
	}; \
	unsigned char NAME::get() const \
	{ \
		return ((const Sub##NAME *)((const char *)this - (BACK)))->m_holder->m_value; \
	}

#define BFME_DISP8_BYTECHASE_GETTER(NAME, DISP1, DISP2) \
	class NAME \
	{ \
	public: \
		unsigned char get() const; \
		char m_lead[DISP1]; \
		void *m_ptr; \
	}; \
	unsigned char NAME::get() const \
	{ \
		return *(unsigned char *)((char *)m_ptr + DISP2); \
	}

#define BFME_DISP8_BYTE_CMP_BOOL_GETTER(NAME, DISP, OP) \
	class NAME \
	{ \
	public: \
		bool get() const; \
		char m_lead[DISP]; \
		unsigned char m_byte; \
	}; \
	bool NAME::get() const \
	{ \
		return m_byte OP 0; \
	}

#define BFME_DISP8_BYTE_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		unsigned char get() const; \
		char m_lead[DISP]; \
		unsigned char m_value; \
	}; \
	unsigned char NAME::get() const \
	{ \
		return m_value; \
	}

#define BFME_DISP8_BYTE_ONE_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void enable(); \
		char m_lead[DISP]; \
		unsigned char m_enabled; \
	}; \
	void NAME::enable() \
	{ \
		m_enabled = 1; \
	}

#define BFME_DISP8_BYTE_SETTER(NAME, METHOD, DISP, IMM) \
	class NAME \
	{ \
	public: \
		void METHOD(); \
		char m_lead[DISP]; \
		unsigned char m_flag; \
	}; \
	void NAME::METHOD() \
	{ \
		m_flag = IMM; \
	}

#define BFME_DISP8_BYTE_TERNARY_BOOL_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		bool get() const; \
		char m_lead[DISP]; \
		unsigned char m_byte; \
	}; \
	bool NAME::get() const \
	{ \
		return m_byte ? true : false; \
	}

#define BFME_DISP8_BYTE_TWO_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(); \
		char m_lead[DISP]; \
		unsigned char m_value; \
	}; \
	void NAME::set() \
	{ \
		m_value = 2; \
	}

#define BFME_DISP8_BYTE_ZERO_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void disable(); \
		char m_lead[DISP]; \
		unsigned char m_enabled; \
	}; \
	void NAME::disable() \
	{ \
		m_enabled = 0; \
	}

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

#define BFME_DISP8_CMP_ZERO_BOOL_GETTER(NAME, DISP, OP) \
	class NAME \
	{ \
	public: \
		bool get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	bool NAME::get() const \
	{ \
		return m_value OP 0; \
	}

#define BFME_DISP8_DIV_AVG_DWORD_GETTER(NAME, DISP1, DISP2, DIVISOR) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP1]; \
		int m_first; \
	}; \
	int NAME::get() const \
	{ \
		return (m_first - *(int *)((char *)this + DISP2)) / DIVISOR; \
	}

#define BFME_DISP8_DIV_MOV_DWORD_GETTER(NAME, DISP1, DISP2, DIVISOR) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP1]; \
		int m_first; \
	}; \
	int NAME::get() const \
	{ \
		return (m_first - *(int *)((char *)this + DISP2)) / DIVISOR; \
	}

#define BFME_DISP8_DWORD_CLEAR(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void clear(); \
		char m_lead[DISP]; \
		int m_counter; \
	}; \
	void NAME::clear() \
	{ \
		m_counter = 0; \
	}

#define BFME_DISP8_DWORD_DEC(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void dec(); \
		char m_lead[DISP]; \
		int m_counter; \
	}; \
	void NAME::dec() \
	{ \
		--m_counter; \
	}

#define BFME_DISP8_DWORD_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return m_value; \
	}

#define BFME_DISP8_DWORD_INC(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void inc(); \
		char m_lead[DISP]; \
		int m_counter; \
	}; \
	void NAME::inc() \
	{ \
		++m_counter; \
	}

#define BFME_DISP8_DWORD_MASK(NAME, DISP, MASK) \
	class NAME \
	{ \
	public: \
		void clear(); \
		char m_lead[DISP]; \
		int m_counter; \
	}; \
	void NAME::clear() \
	{ \
		m_counter &= MASK; \
	}

#define BFME_DISP8_DWORD_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(int value); \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	void NAME::set(int value) \
	{ \
		m_value = value; \
	}

#define BFME_DISP8_FILD_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		double get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	double NAME::get() const \
	{ \
		return m_value; \
	}

#define BFME_DISP8_FLOATCHASE_BEFORE_GETTER(NAME, BACK, INNER) \
	class Inner##NAME \
	{ \
	public: \
		char m_lead[INNER]; \
		float m_value; \
	}; \
	class Sub##NAME \
	{ \
	public: \
		Inner##NAME *m_holder; \
	}; \
	class NAME \
	{ \
	public: \
		float get() const; \
	}; \
	float NAME::get() const \
	{ \
		return ((const Sub##NAME *)((const char *)this - (BACK)))->m_holder->m_value; \
	}

#define BFME_DISP8_FLOATCHASE_GETTER(NAME, DISP1, DISP2) \
	class NAME \
	{ \
	public: \
		float get() const; \
		char m_lead[DISP1]; \
		void *m_ptr; \
	}; \
	float NAME::get() const \
	{ \
		return *(float *)((char *)m_ptr + DISP2); \
	}

#define BFME_DISP8_FLOAT_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		float get() const; \
		char m_lead[DISP]; \
		float m_value; \
	}; \
	float NAME::get() const \
	{ \
		return m_value; \
	}

#define BFME_DISP8_FLOAT_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(float newValue); \
		char m_lead[DISP]; \
		float m_value; \
	}; \
	void NAME::set(float newValue) \
	{ \
		m_value = newValue; \
	}

#define BFME_DISP8_LEA_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void *get() const; \
	}; \
	void *NAME::get() const \
	{ \
		return (char *)this + DISP; \
	}

#define BFME_DISP8_LEA_NEG_SBB_GETTER(NAME, LEADISP, ADDIMM) \
	class NAME \
	{ \
	public: \
		int get() const; \
	}; \
	int NAME::get() const \
	{ \
		const char *field = (const char *)this; \
		const void *base = field - LEADISP; \
		field += ADDIMM; \
		return base ? (int)field : 0; \
	}

#define BFME_DISP8_MASKED_CHASE_DWORD_GETTER(NAME, DISP1, DISP2, MASK) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP1]; \
		void *m_ptr; \
	}; \
	int NAME::get() const \
	{ \
		return *(int *)((char *)m_ptr + DISP2) & MASK; \
	}

#define BFME_DISP8_MASKED_DWORD_GETTER(NAME, DISP, MASK) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return m_value & MASK; \
	}

#define BFME_DISP8_MOVZX_BYTE_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		unsigned int get() const; \
		char m_lead[DISP]; \
		unsigned char m_value; \
	}; \
	unsigned int NAME::get() const \
	{ \
		return m_value; \
	}

#define BFME_DISP8_MOVZX_WORD_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		unsigned int get() const; \
		char m_lead[DISP]; \
		unsigned short m_value; \
	}; \
	unsigned int NAME::get() const \
	{ \
		return m_value; \
	}

#define BFME_DISP8_MOV_LEA_NEG_SBB_GETTER(NAME, ADDIMM) \
	class NAME \
	{ \
	public: \
		int get() const; \
	}; \
	int NAME::get() const \
	{ \
		const void *base = this; \
		const char *field = (const char *)base + ADDIMM; \
		return base ? (int)field : 0; \
	}

#define BFME_DISP8_NEG_DWORD_GETTER(NAME, INDEX) \
	class NAME \
	{ \
	public: \
		int get() const; \
	}; \
	int NAME::get() const \
	{ \
		return ((const int *)this)[INDEX]; \
	}

#define BFME_DISP8_NEG_FLOAT_GETTER(NAME, INDEX) \
	class NAME \
	{ \
	public: \
		float get() const; \
	}; \
	float NAME::get() const \
	{ \
		return ((const float *)this)[INDEX]; \
	}

#define BFME_DISP8_NEG_LEA_GETTER(NAME, BACK) \
	class NAME \
	{ \
	public: \
		void *get() const; \
	}; \
	void *NAME::get() const \
	{ \
		return (char *)this - BACK; \
	}

#define BFME_DISP8_NULL_ADJUST_GETTER(NAME, DISP, ADJ) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		int m_ptr; \
	}; \
	int NAME::get() const \
	{ \
		return m_ptr ? m_ptr + ADJ : 0; \
	}

#define BFME_DISP8_NULL_ADJUST_GLOBAL_GETTER(NAME, DISP, ADJ, GLOBAL) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		int m_ptr; \
	}; \
	int NAME::get() const \
	{ \
		return m_ptr ? m_ptr + ADJ : (int)&GLOBAL; \
	}

#define BFME_DISP8_PTRCHASE_BEFORE_DWORD_GETTER(NAME, BACK, INNER) \
	class Inner##NAME \
	{ \
	public: \
		char m_lead[INNER]; \
		int m_value; \
	}; \
	class Sub##NAME \
	{ \
	public: \
		Inner##NAME *m_holder; \
	}; \
	class NAME \
	{ \
	public: \
		int get() const; \
	}; \
	int NAME::get() const \
	{ \
		return ((const Sub##NAME *)((const char *)this - (BACK)))->m_holder->m_value; \
	}

#define BFME_DISP8_PTRCHASE_DWORD_GETTER(NAME, DISP1, DISP2) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP1]; \
		void *m_ptr; \
	}; \
	int NAME::get() const \
	{ \
		return *(int *)((char *)m_ptr + DISP2); \
	}

#define BFME_DISP8_PTR_TERNARY_BOOL_GETTER(NAME, DISP, INNER_DISP) \
	struct NAME##Inner \
	{ \
		char m_pad[INNER_DISP]; \
		int m_inner; \
	}; \
	class NAME \
	{ \
	public: \
		bool get() const; \
		char m_lead[DISP]; \
		NAME##Inner *m_ptr; \
	}; \
	bool NAME::get() const \
	{ \
		return m_ptr->m_inner ? true : false; \
	}

#define BFME_DISP8_PTR_TERNARY_CMP_BOOL_GETTER(NAME, DISP, INNER_DISP, IMM, OP) \
	struct NAME##Inner \
	{ \
		char m_pad[INNER_DISP]; \
		int m_inner; \
	}; \
	class NAME \
	{ \
	public: \
		bool get() const; \
		char m_lead[DISP]; \
		NAME##Inner *m_ptr; \
	}; \
	bool NAME::get() const \
	{ \
		return m_ptr->m_inner OP IMM ? true : false; \
	}

#define BFME_DISP8_SAR_AVG_DWORD_GETTER(NAME, DISP1, DISP2, IMM) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP1]; \
		int m_first; \
	}; \
	int NAME::get() const \
	{ \
		return (m_first - *(int *)((char *)this + DISP2)) >> IMM; \
	}

#define BFME_DISP8_SAR_DWORD_GETTER(NAME, DISP, IMM) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return m_value >> IMM; \
	}

#define BFME_DISP8_SCALED_BITS(NAME, SHIFT) \
    class NAME { \
    public: \
        unsigned scaled() const; \
        char m_lead[0x10]; \
        unsigned m_value; \
    }; \
    unsigned NAME::scaled() const { return m_value << SHIFT; }

#define BFME_DISP8_SHL_DWORD_GETTER(NAME, DISP, IMM) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return m_value << IMM; \
	}

#define BFME_DISP8_SHR3_AND_DWORD_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		unsigned int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return (m_value >> 3) & 1; \
	}

#define BFME_DISP8_SHRN_AND_DWORD_GETTER(NAME, DISP, COUNT) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		unsigned int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return (m_value >> COUNT) & 1; \
	}

#define BFME_DISP8_SHRN_AND_MASK_DWORD_GETTER(NAME, DISP, COUNT, MASK) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		unsigned int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return (m_value >> COUNT) & MASK; \
	}

#define BFME_DISP8_SHR_AND_DWORD_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		unsigned int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return (m_value >> 1) & 1; \
	}

#define BFME_DISP8_SUB_DWORD_GETTER(NAME, DISP, IMM) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return m_value - IMM; \
	}

#define BFME_DISP8_SUB_IMM32_DWORD_GETTER(NAME, DISP, IMM) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return m_value - IMM; \
	}

#define BFME_DISP8_TERNARY_BOOL_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		bool get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	bool NAME::get() const \
	{ \
		return m_value ? true : false; \
	}

#define BFME_DISP8_TERNARY_CMP_BOOL_GETTER(NAME, DISP, IMM, OP) \
	class NAME \
	{ \
	public: \
		bool get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	bool NAME::get() const \
	{ \
		return m_value OP IMM ? true : false; \
	}

#define BFME_DISP8_WORDCHASE_ZERO_GETTER(NAME, DISP1) \
	class Inner##NAME \
	{ \
	public: \
		short m_value; \
	}; \
	class Sub##NAME \
	{ \
	public: \
		Inner##NAME *m_holder; \
	}; \
	class NAME \
	{ \
	public: \
		int get() const; \
	}; \
	int NAME::get() const \
	{ \
		return ((const Sub##NAME *)((const char *)this + (DISP1)))->m_holder->m_value; \
	}

#define BFME_DISP8_WORD_FIELD_GETTER(NAME, OFFSET) \
	class NAME \
	{ \
	public: \
		unsigned short get() const; \
		char m_lead[OFFSET]; \
		unsigned short m_value; \
	}; \
	unsigned short NAME::get() const \
	{ \
		return m_value; \
	}

#define BFME_DISP8_WORD_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(unsigned short value); \
		char m_lead[DISP]; \
		unsigned short m_value; \
	}; \
	void NAME::set(unsigned short value) \
	{ \
		m_value = value; \
	}

#define BFME_DISP_BLOB_SETTER(NAME, DISP) \
	struct NAME##Blob \
	{ \
		int m_words[32]; \
	}; \
	class NAME \
	{ \
	public: \
		void set(const NAME##Blob *value); \
		char m_lead[DISP]; \
		NAME##Blob m_value; \
	}; \
	void NAME::set(const NAME##Blob *value) \
	{ \
		m_value = *value; \
	}

#define BFME_DISP_BYTE_FLOAT_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		float get() const; \
		char m_lead[DISP]; \
		unsigned char m_value; \
	}; \
	float NAME::get() const \
	{ \
		return m_value; \
	}

#define BFME_DISP_BYTE_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		unsigned char get() const; \
		char m_lead[DISP]; \
		unsigned char m_value; \
	}; \
	unsigned char NAME::get() const \
	{ \
		return m_value; \
	}

#define BFME_DISP_BYTE_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(unsigned char value); \
		char m_lead[DISP]; \
		unsigned char m_value; \
	}; \
	void NAME::set(unsigned char value) \
	{ \
		m_value = value; \
	}

#define BFME_DISP_DWORD_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return m_value; \
	}

#define BFME_DISP_DWORD_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(int value); \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	void NAME::set(int value) \
	{ \
		m_value = value; \
	}

#define BFME_DISP_FLOAT_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		float get() const; \
		char m_lead[DISP]; \
		float m_value; \
	}; \
	float NAME::get() const \
	{ \
		return m_value; \
	}

#define BFME_FIELD_COPIER(NAME, SRC, DST) \
	class NAME \
	{ \
	public: \
		void copy(); \
		char m_lead[SRC]; \
		int m_src; \
		char m_mid[(DST) - (SRC) - 4]; \
		int m_dst; \
	}; \
	void NAME::copy() \
	{ \
		m_dst = m_src; \
	}

#define BFME_FLAG_BIT_SETTER( NAME, LEAD, MASK )                              \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		void setFlag( unsigned char on );                                     \
                                                                              \
		char         m_lead[ LEAD ];                                          \
		unsigned int m_flags;                                                 \
	};                                                                        \
	void NAME::setFlag( unsigned char on )                                    \
	{                                                                         \
		if ( on )                                                             \
			m_flags |= ( MASK );                                              \
		else                                                                  \
			m_flags &= ~( MASK );                                             \
	}

#define BFME_IMUL_ADD_DWORD_GETTER(NAME, IMM) \
	class NAME \
	{ \
	public: \
		int get(int scale) const; \
		int m_value; \
	}; \
	int NAME::get(int scale) const \
	{ \
		return scale * IMM + m_value; \
	}

#define BFME_INT_ZERO_GETTER(NAME) \
	class NAME \
	{ \
	public: \
		int get() const; \
	}; \
	int NAME::get() const \
	{ \
		return 0; \
	}

#define BFME_KEYED_RECORD_FIND( NAME, RECORD, SIZE )                         \
	struct RECORD                                                            \
	{                                                                        \
		int  m_lead[ 2 ];                                                    \
		int  m_key;                                                          \
		char m_rest[ SIZE - 12 ];                                            \
	};                                                                       \
	class NAME                                                               \
	{                                                                        \
	public:                                                                  \
		RECORD *find( int key ) const;                                       \
                                                                             \
		RECORD *m_records;                                                   \
		int     m_count;                                                     \
	};                                                                       \
	RECORD *NAME::find( int key ) const                                      \
	{                                                                        \
		RECORD *end = m_records + m_count;                                   \
		for ( RECORD *record = m_records; record < end; ++record )           \
		{                                                                    \
			if ( record->m_key == key )                                      \
				return record;                                               \
		}                                                                    \
		return 0;                                                            \
	}

#define BFME_LAZY_CACHED_ACCESSOR( NAME, HELPER, OFFSET )                     \
	struct NAME##Cached { int m_opaque; };                                    \
	struct NAME##Owner                                                        \
	{                                                                         \
		char m_lead[ OFFSET ];                                                \
		NAME##Cached *m_slot;                                                 \
	};                                                                        \
	NAME##Cached *HELPER( NAME##Owner *owner );                               \
	struct NAME                                                               \
	{                                                                         \
		void *m_head;                                                         \
		NAME##Owner *m_owner;                                                 \
		NAME##Cached *get();                                                  \
	};                                                                        \
	NAME##Cached *NAME::get()                                                 \
	{                                                                         \
		if ( m_owner->m_slot == 0 )                                           \
			m_owner->m_slot = HELPER( m_owner );                              \
		return m_owner->m_slot;                                               \
	}

#define BFME_LAZY_CACHED_ACCESSOR_REAL( NAME, HELPER, OFFSET )                     \
	struct NAME##Cached { int m_opaque; };                                    \
	struct NAME##Owner                                                        \
	{                                                                         \
		char m_lead[ OFFSET ];                                                \
		NAME##Cached *m_slot;                                                 \
	};                                                                        \
	class HELPER##Object; HELPER##Object *HELPER( void *owner );                               \
	struct NAME                                                               \
	{                                                                         \
		void *m_head;                                                         \
		NAME##Owner *m_owner;                                                 \
		NAME##Cached *get();                                                  \
	};                                                                        \
	NAME##Cached *NAME::get()                                                 \
	{                                                                         \
		if ( m_owner->m_slot == 0 )                                           \
			m_owner->m_slot = (NAME##Cached *)HELPER( m_owner );                              \
		return m_owner->m_slot;                                               \
	}

#define BFME_LITERAL_NAME_GETTER(NAME, TEXT) \
	class NAME \
	{ \
	public: \
		const char *name() const; \
	}; \
	const char *NAME::name() const \
	{ \
		return TEXT; \
	}

#define BFME_MOVSX_BYTE_FIELD_GETTER(NAME, OFFSET) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[OFFSET]; \
		signed char m_value; \
	}; \
	int NAME::get() const \
	{ \
		return m_value; \
	}

#define BFME_PAIR_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(Int a, Int b); \
		char m_lead[DISP]; \
		Int m_a; \
		Int m_b; \
	}; \
	void NAME::set(Int a, Int b) \
	{ \
		m_a = a; \
		m_b = b; \
	}

#define BFME_PA_ERASE_ELEM( NAME, SIZE ) \
	struct NAME                          \
	{                                    \
		virtual ~NAME();                 \
		char m_body[ (SIZE) - 4 ];       \
		NAME();                          \
		NAME( const NAME & );            \
		NAME &operator=( const NAME & ); \
	}

#define BFME_R2_NULL_HEAD_BITS(NAME, FIELD) \
    class NAME \
    { \
    public: \
        unsigned getBits() const; \
        const void *m_pointee; \
    }; \
    unsigned NAME::getBits() const \
    { \
        if (m_pointee) \
            return *(const unsigned *)((const char *)m_pointee + FIELD); \
        return 0; \
    }

#define BFME_RVA001F43BD_SLOT_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(void *p); \
	}; \
	void NAME::set(void *p) \
	{ \
		((Rva001F43BD *)((char *)this + DISP))->rva001F43BD(p); \
	}

#define BFME_SCALED_INT_FLOAT_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		float get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	float NAME::get() const \
	{ \
		return m_value * 0.01f; \
	}

#define BFME_SNAPSHOT_NAME_GETTER(NAME, TEXT) \
	class NAME \
	{ \
	protected: \
		virtual const char *GetSnapshotName() const; \
	}; \
	const char *NAME::GetSnapshotName() const \
	{ \
		return TEXT; \
	}

#define BFME_SUBOBJECT_ARG_FORWARDER( NAME, OFFSET )                      \
	class NAME##Owner                                                     \
	{                                                                     \
	public:                                                               \
		char m_lead[ OFFSET ];                                            \
		Rva005045C6 m_sub;                                                \
	};                                                                    \
	void NAME( NAME##Owner *owner, GenForwardedArg *a )                   \
	{                                                                     \
		owner->m_sub.addControlPoint( *(const Rva00064640Record *)a );       \
	}

#define BFME_TWO_DWORD_ASSIGN( NAME, LEAD )                                   \
	struct Pair##NAME                                                         \
	{                                                                         \
		unsigned int m_first;                                                 \
		unsigned int m_second;                                                \
	};                                                                        \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		void set( const Pair##NAME &value );                                  \
                                                                              \
		char         m_lead[ LEAD ];                                          \
		unsigned int m_first;                                                 \
		unsigned int m_second;                                                \
	};                                                                        \
	void NAME::set( const Pair##NAME &value )                                 \
	{                                                                         \
		m_first = value.m_first;                                              \
		m_second = value.m_second;                                            \
	}

#define BFME_TWO_DWORD_SETTER( NAME, LEAD )                                   \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		void set( int first, int second );                                    \
                                                                              \
		char m_lead[ LEAD ];                                                  \
		int  m_first;                                                         \
		int  m_second;                                                        \
	};                                                                        \
	void NAME::set( int first, int second )                                   \
	{                                                                         \
		m_first = first;                                                      \
		m_second = second;                                                    \
	}

#define BFME_VPTR_CLEANUP_DELETING_DTOR( NAME, CLEANUP )                      \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		virtual ~NAME();                                                      \
	};                                                                        \
	NAME::~NAME()                                                             \
	{                                                                         \
		( (CLEANUP *)this )->run();                                           \
	}

#define BFME_VPTR_ZERO_BYTE_BYTE_CTOR( NAME )                                 \
	class NAME : public VptrZeroHead                                          \
	{                                                                         \
	public:                                                                   \
		NAME( unsigned char first, unsigned char second );                    \
                                                                              \
		unsigned char m_first;                                                \
		unsigned char m_second;                                                \
	};                                                                        \
	NAME::NAME( unsigned char first, unsigned char second )                   \
		: m_first( first ), m_second( second ) {}

#define BFME_VPTR_ZERO_PTR_BYTE_PTR_CTOR( NAME )                              \
	class NAME : public VptrZeroHead                                          \
	{                                                                         \
	public:                                                                   \
		NAME( void *first, unsigned char second, void *third );               \
                                                                              \
		void          *m_first;                                               \
		unsigned char  m_second;                                              \
		void          *m_third;                                               \
	};                                                                        \
	NAME::NAME( void *first, unsigned char second, void *third )              \
		: m_first( first ), m_second( second ), m_third( third ) {}

#define BFME_VTABLE_INSTALL(NAME, VTABLE) \
	class NAME \
	{ \
	public: \
		NAME *init(); \
		void *m_vtable; \
	}; \
	NAME *NAME::init() \
	{ \
		m_vtable = VTABLE; \
		return this; \
	}

#define BFME_WORD_FIELD_GETTER(NAME, OFFSET) \
	class NAME \
	{ \
	public: \
		unsigned short get() const; \
		char m_lead[OFFSET]; \
		unsigned short m_value; \
	}; \
	unsigned short NAME::get() const \
	{ \
		return m_value; \
	}

#define FX_DRAW_MODULE_TEMPLATE(NAME, INFO)                                                        \
    /* Retail derives draw templates through CategoryModuleTemplate<6>; keeping \
       that intermediate base is required for its destructor EH-state shape. */ \
    class NAME : public CategoryModuleTemplate<6>, public INFO                                     \
    {                                                                                              \
    public:                                                                                        \
        NAME();                                                                                    \
        NAME(const NAME &that);                                                                    \
                                                                                                   \
        NAME &operator=(const NAME &that);                                                         \
                                                                                                   \
        void parse(INI *ini);                                                                      \
    };

#define FX_EVENT_MODULE_TEMPLATE(NAME, INFO)                                                       \
    class NAME : public CategoryModuleTemplate<8>, public INFO                                     \
    {                                                                                              \
    public:                                                                                        \
        NAME();                                                                                    \
        NAME(const NAME &that);                                                                    \
        virtual ~NAME();                                                                           \
                                                                                                   \
        NAME &operator=(const NAME &that);                                                         \
    };

#define FX_MODULE_TEMPLATE(NAME, INFO)                                                             \
    class NAME : public ModuleTemplate, public SecondaryModuleBase, public INFO                    \
    {                                                                                              \
    public:                                                                                        \
        NAME();                                                                                    \
        virtual ~NAME();                                                                           \
        NAME(const NAME &that);                                                                    \
                                                                                                   \
        NAME &operator=(const NAME &that);                                                         \
                                                                                                   \
        void parse(INI *ini);                                      \
    };

#define GAP_INT_FORWARD_CTOR(NAME, BASE) \
	class BASE \
	{ \
	public: \
		BASE(const int *value); \
	}; \
	class NAME : public BASE \
	{ \
	public: \
		NAME(int value); \
	}; \
	NAME::NAME(int value) : BASE(&value) \
	{ \
	}

#define GAP_VTABLE_ARG_CTOR(NAME) \
	class NAME \
	{ \
	public: \
		NAME(int value); \
		virtual ~NAME() {} \
	private: \
		int m_04; \
		int m_08; \
	}; \
	NAME::NAME(int value) : m_04(0), m_08(value) \
	{ \
	}

#define GAP_VTABLE_PAIR_CTOR(NAME) \
	class NAME \
	{ \
	public: \
		NAME(const GapPair &pair); \
		virtual ~NAME() {} \
	private: \
		int m_04; \
		int m_08; \
		int m_0C; \
	}; \
	NAME::NAME(const GapPair &pair) : m_04(0), m_08(pair.a), m_0C(pair.b) \
	{ \
	}

#define GAP_VTABLE_WORD_CTOR(NAME) \
	class NAME : public GapWordBase04 \
	{ \
	public: \
		NAME(int a); \
		virtual ~NAME() {} \
	}; \
	NAME::NAME(int a) : GapWordBase04(a) \
	{ \
	}

#define MODULE_INFO_THIRD_BASE(NAME) \
	class NAME \
	{ \
	public: \
		virtual ~NAME() {} \
	};

#define MODULE_TEMPLATE_CLONE_SLOT( NAME, METHOD, BASE, SRC, SLOT1, SIZE )    \
	class BASE : public Rva003AC8D7Slot0, public SLOT1, public Rva003AC8D7Slot2 \
	{                                                                        \
	public:                                                                  \
		BASE( unsigned int arg, SRC src );                                    \
	};                                                                       \
	class NAME##Object : public BASE                                         \
	{                                                                        \
	public:                                                                  \
		__forceinline NAME##Object( unsigned int arg, SRC src )              \
			: BASE( arg, src ) {}                                             \
		char m_storage[ SIZE - sizeof( BASE ) ];                              \
	};                                                                       \
	class NAME##Clone                                                        \
	{                                                                        \
	public:                                                                  \
		virtual NAME##Object *METHOD( unsigned int arg ) = 0;                 \
	};                                                                       \
	class NAME##Host : public Rva003AC8D7Primary, public NAME##Clone          \
	{                                                                        \
	public:                                                                  \
		virtual NAME##Object *METHOD( unsigned int arg );                      \
	};

#define PARTICLE_MODULE_FINAL( NAME, TEMPLATE, BASE )                           \
	class TEMPLATE;                                                           \
	class NAME : public BASE                                                  \
	{                                                                         \
	public:                                                                   \
		NAME( void *owner, TEMPLATE *module_template );                         \
	};                                                                        \
	NAME::NAME( void *owner, TEMPLATE *module_template )                        \
		: BASE( owner, module_template )                                       \
	{                                                                         \
	}

#define PARTICLE_MODULE_INTERMEDIATE( NAME, MODULE )                            \
	class NAME : public FXParticleSystem::MODULE                                \
	{                                                                         \
	public:                                                                   \
		NAME( void *system, void *module_template );                            \
	};                                                                        \
	NAME::NAME( void *system, void *module_template )                           \
		: FXParticleSystem::MODULE( *static_cast<RvaParticleSystemPtr *>( system ), \
			static_cast<const FXParticleSystem::MODULE##Template *>( module_template ) ) \
	{                                                                         \
	}

#define Q1_PLAIN_ZERO_CTOR( NAME, HEAD )                                  \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		unsigned int m_head;                                              \
		int m_a;                                                          \
		int m_b;                                                          \
		NAME();                                                           \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
		m_head = HEAD;                                                    \
		m_a = 0;                                                          \
		m_b = 0;                                                          \
	}

#define Q1_VFTABLE_ZERO_CTOR( NAME )                                      \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		virtual void v();                                                 \
		int m_a;                                                          \
		int m_b;                                                          \
		NAME();                                                           \
	};                                                                    \
	void NAME::v()                                                        \
	{                                                                     \
	}                                                                     \
	NAME::NAME()                                                          \
	{                                                                     \
		m_a = 0;                                                          \
		m_b = 0;                                                          \
	}

#define Q1_VFTABLE_ZERO_CTOR_PAD( NAME, PAD )                             \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		virtual void v();                                                 \
		char m_lead[ PAD ];                                               \
		int m_a;                                                          \
		int m_b;                                                          \
		NAME();                                                           \
	};                                                                    \
	void NAME::v()                                                        \
	{                                                                     \
	}                                                                     \
	NAME::NAME()                                                          \
	{                                                                     \
		m_a = 0;                                                          \
		m_b = 0;                                                          \
	}

#define Q2_HEAP_COPY_CLONE( NAME, SIZE )                                  \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME( const NAME &other );                                        \
		NAME *clone() const;                                              \
	private:                                                              \
		char m_unreconstructed_00[ SIZE ];                                \
	};                                                                    \
	NAME *NAME::clone() const                                             \
	{                                                                     \
		return new NAME( *this );                                         \
	}

#define R2_RELEASE( NAME, OFF )                                           \
	class NAME##Owned                                                     \
	{                                                                     \
	public:                                                               \
		virtual ~NAME##Owned();                                             \
	};                                                                    \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		char m_leading[ OFF ];                                              \
		NAME##Owned *m_owned;                                               \
		void release();                                                     \
	};                                                                    \
	void NAME::release()                                                  \
	{                                                                     \
		delete m_owned;                                                     \
		m_owned = 0;                                                        \
	}

#define R4_TWO_MEMBER_DTOR( NAME, LEAD, M1, M2 )                              \
	struct NAME                                                               \
	{                                                                         \
		char m_lead[ LEAD ];                                                  \
		M1 m_first;                                                           \
		M2 m_second;                                                          \
		~NAME();                                                              \
	};                                                                        \
	NAME::~NAME() {}

#define RVA_APT_CTOR(NAME, TYPE, SIZE) \
	class NAME : public Rva006D6360Base, public Rva006DBits \
	{ \
	public: \
		NAME(); \
		virtual ~NAME() {} \
	}; \
	NAME::NAME() : Rva006D6360Base(TYPE, SIZE), Rva006DBits() \
	{ \
		m_flags = (m_flags & 0xFE07FFFFu) | 0x40000u; \
	}

#define RVA_APT_FLAG_CTOR(NAME, TYPE, KEEP, SET) \
	class NAME : public BfmeAptValue006DCD20 \
	{ \
	public: \
		NAME(); \
		virtual ~NAME() {} \
	}; \
	NAME::NAME() : BfmeAptValue006DCD20(TYPE) \
	{ \
		if(0){throw 0;} \
		m_flags = (m_flags & (KEEP)) | (SET); \
	}

#define S3_ARRAY_CLEAR( NAME, SIZE )                                      \
	class NAME##Elem                                                      \
	{                                                                     \
	public:                                                               \
		virtual void step( int flags );                                   \
		char m_pad[ SIZE - 4 ];                                           \
	};                                                                    \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void clear();                                                     \
		NAME##Elem *m_array;                                              \
		int m_count;                                                      \
	};                                                                    \
	void NAME::clear()                                                    \
	{                                                                     \
		if( m_array )                                                     \
		{                                                                 \
			for( int i = 0; i < m_count; ++i )                            \
				m_array[ i ].step( 0 );                                   \
			Gen007EFFC0()->release( m_array, 0 );                         \
			m_array = 0;                                                  \
		}                                                                 \
		m_count = 0;                                                      \
	}

#define S3_ARRAY_LOOKUP( NAME, SIZE )                                     \
	class NAME##Elem                                                      \
	{                                                                     \
	public:                                                               \
		virtual void step( int flags );                                   \
		char m_pad[ SIZE - 4 ];                                           \
	};                                                                    \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME##Elem *at( int index );                                      \
		NAME##Elem *m_array;                                              \
		int m_count;                                                      \
	};                                                                    \
	NAME##Elem *NAME::at( int index )                                     \
	{                                                                     \
		if ( index >= m_count )                                           \
			return 0;                                                     \
		return m_array + index;                                           \
	}

#define S3_DELETE_AND_CLEAR( NAME, CALLEE, OFFSET )                       \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void release();                                                   \
		char m_lead[ OFFSET ];                                            \
		CALLEE *m_owned;                                                  \
	};                                                                    \
	void NAME::release()                                                  \
	{                                                                     \
		delete m_owned;                                                   \
		m_owned = 0;                                                      \
	}

#define S3_OWNED_CALLEE_NAMED( NAME )                                     \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		~NAME();                                                          \
	};

#define V3_CLONE_FACTORY( NAME, SIZE )                                     \
	class NAME                                                             \
	{                                                                      \
	public:                                                                \
		NAME *clone() const;                                               \
		char m_storage[ SIZE ];                                            \
	};                                                                     \
	NAME *NAME::clone() const                                              \
	{                                                                      \
		return reinterpret_cast<NAME *>( new Rva003AF89A( *reinterpret_cast<const Rva003AF89A *>( this ) ) ); \
	}

#define V3_INLINE_COPY_CTOR( NAME, SECOND )                               \
	class NAME : public V3Vt01111D90, public SECOND                       \
	{                                                                     \
	public:                                                               \
		NAME( const NAME & );                                             \
	};                                                                    \
	NAME::NAME( const NAME &nAME ) : V3Vt01111D90( nAME ) {}

#define V3_NEW_TWO_ARG_FACTORY( NAME, BASE, SIZE, LEAF, ARGS )                         \
	class V3Host##NAME;                                                    \
	class BASE : public LEAF \
	{                                                                      \
	public:                                                                \
		__declspec(noinline) BASE( void *arg, V3Host##NAME *owner ); \
	};                                                                     \
	class NAME##Object : public BASE                                       \
	{                                                                      \
	public:                                                                \
		NAME##Object( void *arg, V3Host##NAME *owner );                                        \
	};                                                                     \
	typedef char NAME##Size[(sizeof(NAME##Object) == SIZE) ? 1 : -1]; \
	class V3Host##NAME                                                     \
	{                                                                      \
	public:                                                                \
		NAME##Object *create( void *arg );                                 \
	};                                                                     \
	NAME##Object *V3Host##NAME::create( void *arg )                        \
	{                                                                      \
		return new NAME##Object( arg, this );                              \
	}

#define V3_POLY_COPY_1( NAME )                                            \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME( const NAME &other );                                        \
		virtual ~NAME();                                                  \
		Int m_field04;                                                    \
	};                                                                    \
	NAME::NAME( const NAME &other )                                       \
	{                                                                     \
		m_field04 = other.m_field04;                                      \
	}

#endif
