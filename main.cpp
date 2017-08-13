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
			cout << mypad1->LeftStick_x() << endl;
		}
	}
	system("pause");
}