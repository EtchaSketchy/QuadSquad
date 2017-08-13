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
