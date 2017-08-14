#include "PS4.h"
#pragma comment(lib,"Xinput.lib");

CGamepad::CGamepad()
{
}

CGamepad::CGamepad(int _Index)
{
	//Keeps as player 1 or player 2
	m_Index = m_Index - 1;
}

CGamepad::~CGamepad()
{
}

void CGamepad::update()
{
    m_State = getState();
}

bool CGamepad::LStick_Dead()
{
	short x = m_State.Gamepad.sThumbLX;
	short y = m_State.Gamepad.sThumbLY;

	//Check left X
	if (x > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || x < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		return false;
	}
	
	//Check left Y
	if (y > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || y < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		return false;
	}

	//Return true if both are doing kinda nothing;
	return true;
}

bool CGamepad::Rstick_Dead()
{
	short x = m_State.Gamepad.sThumbRX;
	short y = m_State.Gamepad.sThumbRY;

	//Check left X
	if (x > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || x < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		return false;
	}

	//Check left Y
	if (y > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || y < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		return false;
	}

	//Return true if both are doing kinda nothing;
	return true;
}

float CGamepad::LeftStick_x()
{
	//store value
	short value = m_State.Gamepad.sThumbLX;

	//Cast and return
	return(static_cast<float>(value) / 32768.0f);
}

float CGamepad::LeftStick_y()
{
	//store value
	short value = m_State.Gamepad.sThumbLY;

	//Cast and return
	return(static_cast<float>(value) / 32768.0f);
}

float CGamepad::RightStick_x()
{
	//store value
	short value = m_State.Gamepad.sThumbRX;

	//Cast and return
	return(static_cast<float>(value) / 32768.0f);
}

float CGamepad::RightStick_y()
{
	//store value
	short value = m_State.Gamepad.sThumbRY;

	//Cast and return
	return(static_cast<float>(value) / 32768.0f);
}

float CGamepad::LeftTrigger()
{
	//Fetch value
	BYTE Trigger = m_State.Gamepad.bLeftTrigger;

	//If the trigger is not dead zoned
	if (Trigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		//dividing will give value from 0.0f - 1.0f
		return Trigger / 255.0f;
	}

	//If it is dead zoned
	return 0.0f;
}

float CGamepad::RightTrigger()
{
	//Fetch value
	BYTE Trigger = m_State.Gamepad.bRightTrigger;

	//If the trigger is not dead zoned
	if (Trigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		//dividing will give value from 0.0f - 1.0f
		return Trigger / 255.0f;
	}

	//If it is dead zoned
	return 0.0f;
}

void CGamepad::Vibrate(float _leftMotor, float _rightMotor)
{
	//Vibration 
	XINPUT_VIBRATION vibration;

	//zero out the memory
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

	//Calculate vibration values
	int iLeftMotor = int(_leftMotor * 65535.0f);
	int iRightMotor = int(_rightMotor * 65535.0f);

	//Set vibration values
	vibration.wLeftMotorSpeed = iLeftMotor;
	vibration.wRightMotorSpeed = iRightMotor;

	//Finally, set the vibration
	XInputSetState(m_Index, &vibration);
}

XINPUT_STATE CGamepad::getState()
{
	XINPUT_STATE GamepadState;
	ZeroMemory(&GamepadState, sizeof(XINPUT_STATE));
	XInputGetState(m_Index, &GamepadState);
	return GamepadState;
}

int CGamepad::getIndex()
{
	return m_Index;
}

bool CGamepad::isConnected()
{
	for (unsigned int i = 0; i < 50; i++)
	{
		// Zero memory
		ZeroMemory(&m_State, sizeof(XINPUT_STATE));

		// Get the state of the gamepad
		DWORD Result = XInputGetState(i, &m_State);

		if (Result == ERROR_SUCCESS)
		{
			std::cout << "Connected on port: " << i << std::endl;
			m_Index = i;
			return true;  // The gamepad is connected
		}
	}

	return false;
}
