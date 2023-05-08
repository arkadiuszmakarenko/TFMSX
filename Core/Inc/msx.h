#ifndef __MSX_H
#define __MSX_H


#include "usbh_hid_keybd.h"
#include "usb_host.h"

extern USBH_HandleTypeDef hUsbHostFS;
extern USBH_HandleTypeDef hUsbHostHS;

extern HID_KEYBD_Info_TypeDef *USBH_HID_GetKeybdInfo(USBH_HandleTypeDef *phost);
extern ApplicationTypeDef Appli_state;





void ProcessMSXKeyboard();
void InitMSXKeyboard();
void ProcessIRQ();

#define READ_MSX_ROW_VALUE(val) (val&0xF) //


//MSX International Matrix
/*
			bit 7	bit 6	bit 5	bit 4	bit 3	bit 2	bit 1	bit 0
row 0		7 &		6 ^		5 %		4 $		3 #		2 @		1 !		0 )
row 1		; :		] }		[ {		\ ¦		= +		- _		9 (		8 *
row 2		B		A		DEAD	/ ?		. >		, <		` ~		' "
row 3		J		I		H		G		F		E		D		C
row 4		R		Q		P		O		N		M		L		K
row 5		Z		Y		X		W		V		U		T		S
row 6		F3		F2		F1		CODE	CAPS	GRAPH	CTRL	SHIFT
row 7		RET		SELECT	BS		STOP	TAB		ESC		F5		F4
row 8		→		↓		↑		←		DEL		INS		HOME	SPACE
row 9		NUM4	NUM3	NUM2	NUM1	NUM0	NUM/	NUM+	NUM*
row 10		NUM.	NUM,	NUM-	NUM9	NUM8	NUM7	NUM6	NUM5


U.K. matrix (QWERTY with a "£" key)
	bit 7	bit 6	bit 5	bit 4	bit 3	bit 2	bit 1	bit 0
00	7 &		6 ^		5 %		4 $		3 #		2 @		1 !		0 )
01	; :		] }		[ {		\ ¦		= +		- _		9 (		8 *
02	b B		a A		`´		/ ?		. >		, <		£ ~		' "
03	j J		i I		h H		g G		f F		e E		d D		c C
04	r R		q Q		p P		o O		n N		m M		l L		k K
05	z Z		y Y		x X		w W		v V		u U		t T		s S
06	F3F8	F2F7	F1F6	CODE	CAPS	GRAPH	CTRL	SHIFT
07	RET		SELECT	BS		STOP	TAB		ESC		F5F10	F4F9
08	→		↓		↑		←		DEL		INS		HomeCLS	SPACE
09	4		3		2		1		0		/		+		*
10	.		,		-		9		8		7		6		5
 */

#define KB_ROW_0 0
#define KB_ROW_1 1
#define KB_ROW_2 2
#define KB_ROW_3 3
#define KB_ROW_4 4
#define KB_ROW_5 5
#define KB_ROW_6 6
#define KB_ROW_7 7
#define KB_ROW_8 8
#define KB_ROW_9 9
#define KB_ROW_10 10

#define KB_BIT_0 0b00000001
#define KB_BIT_1 0b00000010
#define KB_BIT_2 0b00000100
#define KB_BIT_3 0b00001000
#define KB_BIT_4 0b00010000
#define KB_BIT_5 0b00100000
#define KB_BIT_6 0b01000000
#define KB_BIT_7 0b10000000




#define MSX_KEYS_SIZE 90

// Array of 3 elements USB_KEYCODE, MSX_ROW, MSX_BIT
static const uint8_t msxkeymap[MSX_KEYS_SIZE][3] =
{
		//7 &		6 ^		5 %		4 $		3 #		2 @		1 !		0 )
		{KEY_7_AMPERSAND,						KB_ROW_0,		KB_BIT_7},
		{KEY_6_CARET,							KB_ROW_0,		KB_BIT_6},
		{KEY_5_PERCENT,							KB_ROW_0,		KB_BIT_5},
		{KEY_4_DOLLAR,							KB_ROW_0,		KB_BIT_4},
		{KEY_3_NUMBER_SIGN,						KB_ROW_0,		KB_BIT_3},
		{KEY_2_AT,								KB_ROW_0,		KB_BIT_2},
		{KEY_1_EXCLAMATION_MARK,				KB_ROW_0,		KB_BIT_1},
		{KEY_0_CPARENTHESIS,					KB_ROW_0,		KB_BIT_0},
		//; :		] }		[ {		\ ¦		= +		- _		9 (		8 *
		{KEY_SEMICOLON_COLON,					KB_ROW_1,		KB_BIT_7},
		{KEY_CBRACKET_AND_CBRACE,				KB_ROW_1,		KB_BIT_6},
		{KEY_OBRACKET_AND_OBRACE ,				KB_ROW_1,		KB_BIT_5},
		{KEY_BACKSLASH_VERTICAL_BAR,			KB_ROW_1,		KB_BIT_4},
		{KEY_EQUAL_PLUS,						KB_ROW_1,		KB_BIT_3},
		{KEY_MINUS_UNDERSCORE,					KB_ROW_1,		KB_BIT_2},
		{KEY_9_OPARENTHESIS,					KB_ROW_1,		KB_BIT_1},
		{KEY_8_ASTERISK,						KB_ROW_1,		KB_BIT_0},
		//B		A		DEAD	/ ?		. >		, <		` ~		' "
		{KEY_B,									KB_ROW_2,		KB_BIT_7},
		{KEY_A,									KB_ROW_2,		KB_BIT_6},
		{0x35,									KB_ROW_2,		KB_BIT_5}, //KEY_GRAVE_ACCENT_AND_TILDE
		{KEY_BACKSLASH_VERTICAL_BAR,			KB_ROW_2,		KB_BIT_4},
		{KEY_SLASH_QUESTION,					KB_ROW_2,		KB_BIT_3},
		{KEY_DOT_GREATER,						KB_ROW_2,		KB_BIT_2},
		{KEY_COMMA_AND_LESS,					KB_ROW_2,		KB_BIT_1},
		{KEY_SINGLE_AND_DOUBLE_QUOTE,			KB_ROW_2,		KB_BIT_0},
		//J		I		H		G		F		E		D		C
		{KEY_J,									KB_ROW_3,		KB_BIT_7},
		{KEY_I,									KB_ROW_3,		KB_BIT_6},
		{KEY_H,									KB_ROW_3,		KB_BIT_5},
		{KEY_G,									KB_ROW_3,		KB_BIT_4},
		{KEY_F,									KB_ROW_3,		KB_BIT_3},
		{KEY_E,									KB_ROW_3,		KB_BIT_2},
		{KEY_D,									KB_ROW_3,		KB_BIT_1},
		{KEY_C,									KB_ROW_3,		KB_BIT_0},
		//R		Q		P		O		N		M		L		K
		{KEY_R,									KB_ROW_4,		KB_BIT_7},
		{KEY_Q,									KB_ROW_4,		KB_BIT_6},
		{KEY_P,									KB_ROW_4,		KB_BIT_5},
		{KEY_O,									KB_ROW_4,		KB_BIT_4},
		{KEY_N,									KB_ROW_4,		KB_BIT_3},
		{KEY_M,									KB_ROW_4,		KB_BIT_2},
		{KEY_L,									KB_ROW_4,		KB_BIT_1},
		{KEY_K,									KB_ROW_4,		KB_BIT_0},
		//Z		Y		X		W		V		U		T		S
		{KEY_Z,									KB_ROW_5,		KB_BIT_7},
		{KEY_Y,									KB_ROW_5,		KB_BIT_6},
		{KEY_X,									KB_ROW_5,		KB_BIT_5},
		{KEY_W,									KB_ROW_5,		KB_BIT_4},
		{KEY_V,									KB_ROW_5,		KB_BIT_3},
		{KEY_U,									KB_ROW_5,		KB_BIT_2},
		{KEY_T,									KB_ROW_5,		KB_BIT_1},
		{KEY_S,									KB_ROW_5,		KB_BIT_0},
		//F3		F2		F1		CODE	CAPS	GRAPH	CTRL	SHIFT
		{KEY_F3,								KB_ROW_6,		KB_BIT_7},
		{KEY_F2,								KB_ROW_6,		KB_BIT_6},
		{KEY_F1,								KB_ROW_6,		KB_BIT_5},
		{KEY_LEFT_GUI,							KB_ROW_6,		KB_BIT_4},
		{0x39, 									KB_ROW_6,		KB_BIT_3},//KEY_CAPS LOCK,
		{KEY_RIGHT_GUI,							KB_ROW_6,		KB_BIT_2},
		{KEY_LEFTCONTROL,						KB_ROW_6,		KB_BIT_1},
		{KEY_RIGHTCONTROL,						KB_ROW_6,		KB_BIT_1},
		{KEY_LEFTSHIFT,							KB_ROW_6,		KB_BIT_0},
		{KEY_RIGHTSHIFT,						KB_ROW_6,		KB_BIT_0},
		//RET		SELECT	BS		STOP	TAB		ESC		F5		F4
		{KEY_ENTER,								KB_ROW_7,		KB_BIT_7},
		{KEY_SELECT,							KB_ROW_7,		KB_BIT_6},
		{KEY_BACKSPACE,							KB_ROW_7,		KB_BIT_5},
		{KEY_PAUSE,								KB_ROW_7,		KB_BIT_4},
		{KEY_TAB,								KB_ROW_7,		KB_BIT_3},
		{KEY_ESCAPE,							KB_ROW_7,		KB_BIT_2},
		{KEY_F5,								KB_ROW_7,		KB_BIT_1},
		{KEY_F4,								KB_ROW_7,		KB_BIT_0},
		//→		↓		↑		←		DEL		INS		HOME	SPACE
		{KEY_RIGHTARROW,						KB_ROW_8,		KB_BIT_7},
		{KEY_DOWNARROW,							KB_ROW_8,		KB_BIT_6},
		{KEY_UPARROW,							KB_ROW_8,		KB_BIT_5},
		{KEY_LEFTARROW,							KB_ROW_8,		KB_BIT_4},
		{KEY_DELETE,							KB_ROW_8,		KB_BIT_3},
		{KEY_INSERT,							KB_ROW_8,		KB_BIT_2},
		{KEY_HOME,								KB_ROW_8,		KB_BIT_1},
		{KEY_SPACEBAR,							KB_ROW_8,		KB_BIT_0},
		//NUM4	NUM3	NUM2	NUM1	NUM0	NUM/	NUM+	NUM*
		{KEY_KEYPAD_4_LEFT_ARROW,				KB_ROW_9,		KB_BIT_7},
		{KEY_KEYPAD_3_PAGEDN,					KB_ROW_9,		KB_BIT_6},
		{KEY_KEYPAD_2_DOWN_ARROW,				KB_ROW_9,		KB_BIT_5},
		{KEY_KEYPAD_1_END,						KB_ROW_9,		KB_BIT_4},
		{KEY_KEYPAD_0_INSERT,					KB_ROW_9,		KB_BIT_3},
		{KEY_KEYPAD_SLASH,						KB_ROW_9,		KB_BIT_2},
		{KEY_KEYPAD_PLUS,						KB_ROW_9,		KB_BIT_1},
		{KEY_KEYPAD_ASTERIKS,					KB_ROW_9,		KB_BIT_0},
		//NUM.	NUM,	NUM-	NUM9	NUM8	NUM7	NUM6	NUM5
		{KEY_KEYPAD_DECIMAL_SEPARATOR_DELETE,	KB_ROW_10,		KB_BIT_7},
		{KEY_NONUS_BACK_SLASH_VERTICAL_BAR,		KB_ROW_10,		KB_BIT_6},
		{KEY_KEYPAD_MINUS,						KB_ROW_10,		KB_BIT_5},
		{KEY_KEYPAD_9_PAGEUP,					KB_ROW_10,		KB_BIT_4},
		{KEY_KEYPAD_8_UP_ARROW,					KB_ROW_10,		KB_BIT_3},
		{KEY_KEYPAD_7_HOME,						KB_ROW_10,		KB_BIT_2},
		{KEY_KEYPAD_6_RIGHT_ARROW,				KB_ROW_10,		KB_BIT_1},
		{KEY_KEYPAD_5,							KB_ROW_10,		KB_BIT_0},

};

#endif
