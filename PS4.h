#ifndef PS4_h
#define PS4_H

#include <Windows.h>
#include <Xinput.h>
#include <iostream>

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

	//Fetch data
	XINPUT_STATE getState();
	int getIndex();
	bool isConnected();

private:
	XINPUT_STATE m_State;
	int m_Index;
};



#endif