#include <iostream>
#include "PS4.h"
using namespace std;

CGamepad* mypad1;


int main()
{
	mypad1 = new CGamepad(1);
	if (mypad1->isConnected())
	{
		while (1)
		{
			mypad1->update();
			if (!mypad1->LStick_Dead())
			{
				cout << "Left Joystick =" << mypad1->LeftStick_x() << " : " << mypad1->LeftStick_y() << endl;

			}
			else
			{
				cout << "Left Joystick = DEAD ZONE"<< endl;
			}

			if (!mypad1->Rstick_Dead())
			{
				cout << "Right Joystick =" << mypad1->RightStick_x() << " : " << mypad1->RightStick_y() << endl;
			}
			else
			{
				cout << "Right Joystick = DEAD ZONE" << endl;
			}
			cout << endl;

			cout << "Left Trigger =" << mypad1->LeftTrigger() << endl;
			cout << "Right Trigger =" << mypad1->RightTrigger() << endl;

			if (mypad1->LeftTrigger() > 0.0f || mypad1->RightTrigger() > 0.0f)
			{
				mypad1->Vibrate(1.0f, 1.0f);
			}
			else
			{
				mypad1->Vibrate(0.0f, 0.0f);
			}
			

			Sleep(100);
			system("cls");
		}
	}
	system("pause");
}