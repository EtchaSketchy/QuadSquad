#ifndef PS4_h
#define PS4_H

enum {
	BUTTON_X = 0,
	BUTTON_CIRCLE,
	BUTTON_SQUARE,
	BUTTON_TRIANGE,
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_LBUMPER,
	BUTTON_RBUMPER,
	BUTTON_LSTICK,
	BUTTON_RSTICK,
	BUTTON_OPTIONS,
	BUTTON_SHARE
};


#include <Windows.h>
#include <Xinput.h>
#include <iostream>

//Button Mappings
static const WORD XINPUT_Buttons[] = {
	XINPUT_GAMEPAD_A,
	XINPUT_GAMEPAD_B,
	XINPUT_GAMEPAD_X,
	XINPUT_GAMEPAD_Y,
	XINPUT_GAMEPAD_DPAD_UP,
	XINPUT_GAMEPAD_DPAD_DOWN,
	XINPUT_GAMEPAD_DPAD_LEFT,
	XINPUT_GAMEPAD_DPAD_RIGHT,
	XINPUT_GAMEPAD_LEFT_SHOULDER,
	XINPUT_GAMEPAD_RIGHT_SHOULDER,
	XINPUT_GAMEPAD_LEFT_THUMB,
	XINPUT_GAMEPAD_RIGHT_THUMB,
	XINPUT_GAMEPAD_START,
	XINPUT_GAMEPAD_BACK
};

struct XButtonIDs
{
	// Function prototypes
	//---------------------//
	XButtonIDs(); // Default constructor

	// Member variables
	//---------------------//

	int A, B, X, Y; // 'Action' buttons

	// Directional Pad (D-Pad)
	int DPad_Up, DPad_Down, DPad_Left, DPad_Right;

	// Shoulder ('Bumper') buttons
	int L_Shoulder, R_Shoulder;

	// Thumbstick buttons
	int L_Thumbstick, R_Thumbstick;

	int Start; // 'START' button
	int Back;  // 'BACK' button
};

class CGamepad
{
public:
	CGamepad();
	CGamepad(int _Index);
	~CGamepad();

	//update stuff
	void update();

	//Thumbsticks
	bool LStick_Dead();
	bool Rstick_Dead();

	float LeftStick_x();
	float LeftStick_y();
	float RightStick_x();
	float RightStick_y();

	//Triggers
	float LeftTrigger();
	float RightTrigger();

	//Vibration
	void Vibrate(float _leftMotor, float _rightMotor);

	//Button presses
	bool isButtonPressed(int _button);

	//Fetch data
	XINPUT_STATE getState();
	int getIndex();
	bool isConnected();

private:
	XINPUT_STATE m_State;
	int m_Index;
};



#endif

// Externally define the 'XButtonIDs' struct as 'XButtons'
extern XButtonIDs XButtons;