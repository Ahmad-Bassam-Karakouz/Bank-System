#include<iostream>
#include"cls_login_screen.h"

using namespace std;

int main()
{
	while (true)
	{

		if (!cls_login_screen::show_login_screen())
		{
			break;
		}		

	}

	return 0;

}