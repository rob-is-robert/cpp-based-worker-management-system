#include <iostream>
using namespace std;
#include "workerManager.h"

#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

int main()
{
	////测试代码
	//Worker* worker = NULL;
	//worker = new Manager(2, "Robert", 2);
	//worker->showInfo();
	//delete worker;

	//worker = new Boss(3, "Albert", 2);
	//worker->showInfo();
	//delete worker;



	//实例化一个职工管理系统对象
	WorkerManager wm;

	int choice = 0; //用户的选项

	while (true)
	{
		//显示菜单
		wm.Show_menu();

		cout << "请输入您的选择" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:
			wm.ExitSystem();
			break;
		case 1:
			wm.Add_Emp();
			break;
		case 2:
			wm.Show_Emp();
			break;
		case 3:
			wm.Del_Emp();
			break;
		case 4:
			wm.Mod_Emp();
			break;
		case 5:
			wm.Find_Emp();
			break;
		case 6:
			wm.Sort_Emp();
			break;
		case 7:
			wm.Clean_File();
			break;

		default:
			system("cls");//清屏
			break;

		}
	}

	system("pause");

	




	return 0;

}