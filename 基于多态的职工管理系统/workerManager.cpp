#include "workerManager.h"

WorkerManager::WorkerManager()
{
	
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读文件

	//文件不存在
	if (!ifs.is_open()) 
	{
		cout << "文件不存在" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件存在 数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof()) 
	{
		cout << "文件为空" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件存在且记录数据
	int num = this->get_EmpNum();
	cout << "职工人数为：" << num << endl;
	this->m_EmpNum = num;
	this->m_FileIsEmpty = false;
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->init_Emp();
	
}

void WorkerManager::Show_menu()
{
	cout << "********************" << endl;
	cout << "欢迎使用职工管理系统" << endl;
	cout << "0 退出程序" << endl;
	cout << "1 添加职工" << endl;
	cout << "2 显示职工" << endl;
	cout << "3 删除职工" << endl;
	cout << "4 修改职工" << endl;
	cout << "5 查询职工" << endl;
	cout << "6 排序" << endl;
	cout << "7 清空所有" << endl;
}

void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);//退出程序
}

void WorkerManager::Add_Emp()
{
	cout << "请输入添加人数：" << endl;
	int addNum = 0;
	cin >> addNum;

	if (addNum > 0) 
	{
		int newSize = this->m_EmpNum + addNum; //新空间的大小

		//开辟新空间
		Worker** newSpace = new Worker * [newSize];

		//将原来的数据拷贝到新空间

		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//添加新数据
		for (int i = 0; i < addNum;i++)
		{
			int id;
			string name;
			int dSelect;
			cout << "请输入第" << i + 1 << "个新职工的编号：" << endl;
			cin >> id;

			cout << "请输入第" << i + 1 << "个新职工的名字：" << endl;
			cin >> name;

			cout << "请输入第" << i + 1 << "个新职工的岗位：" << endl;
			cout << "1 职工" << endl;
			cout << "2 经理" << endl;
			cout << "3 老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
			default:
				break;
			}

			newSpace[this->m_EmpNum + i] = worker;
		}

		//释放原有的空间
		delete[] this->m_EmpArray;
		//更改新空间的指向
		this->m_EmpArray = newSpace;

		this->m_EmpNum = newSize;

		this->m_FileIsEmpty = false;

		cout << "成功添加了" << addNum << "名新职工" << endl;

		//保存到文件中
		this->save();
		
		//按任意键后清屏回到上级目录
		system("pause");
		system("cls");
	}
	else {
		cout << "Error" << endl;
	}

}

void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_id << " "
			<< this->m_EmpArray[i]->m_name << " "
			<< this->m_EmpArray[i]->m_deptId << endl;
	}

}

int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int num = 0;

	int id;
	string name;
	int dId;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		num++;
	}

	return num;
}

void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int index = 0;

	int id;
	string name;
	int dId;

	while (ifs >> id && ifs >> name && ifs >> dId) 
	{
		Worker* worker = NULL;

		if (dId == 1) 
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)
		{
			worker = new Manager(id, name, dId);
		}
		else 
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}

void WorkerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在" << endl;
	}
	else { 
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}

	system("pause");
	system("cls");
}

void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或为空！" << endl;
	}
	else 
	{
		cout << "请输入删除职工编号：" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);

		if (index != -1)
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;

			//数据同步到文件中
			this->save();
			cout << "删除成功" << endl;

		}
		else
		{
			cout << "Error! 未找到此人" << endl;
		}

		system("pause");
		system("cls");
	}
}

int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty) 
	{
		cout << "文件不存在或为空！" << endl;

	}
	else
	{
		cout << "请输入修改职工编号：" << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1) 
		{
			delete this->m_EmpArray[ret];
			int newId = 0;
			string newName = "";
			int dselect = 0;
			cout << "查到：" << id << "职工，请输入新的职工号：" << endl;
			cin >> newId;
			cout << "请输入新的姓名" << endl;
			cin >> newName;
			cout << "请输入新的岗位" << endl;
			cout << "1 职工" << endl;
			cout << "2 经理" << endl;
			cout << "3 老板" << endl;
			cin >> dselect;
			Worker* worker = NULL;

			switch (dselect)
			{
			case 1:
				worker = new Employee(newId, newName, dselect);
				break;
			case 2:
				worker = new Manager(newId, newName, dselect);
				break;
			case 3:
				worker = new Boss(newId, newName, dselect);
				break;
			default:
				break;
			}

			this->m_EmpArray[ret] = worker;

			cout << "修改成功！" << endl;

			this->save();

		}
		else {
			cout << "Error! 查无此人。" << endl;

		}

	}
}

void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或为空！" << endl;

	}
	else
	{
		cout << "请输入查找方法：" << endl;
		cout << "1 按编号" << endl << "2 按姓名" << endl;
		int select = 0;
		cin >> select;
		if (select == 1) 
		{
			cout << "请输入职工编号：" << endl;
			int id;
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1) 
			{
				cout << "查找成功" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else 
			{
				cout << "查无此人！" << endl;
			}
		}
		else if (select == 2)
		{
			bool flag = false;

			cout << "请输入职工姓名：" << endl;
			string name;
			cin >> name;
			for (int i = 0; i < this->m_EmpNum ; i++)
			{
				if (this->m_EmpArray[i]->m_name == name) {
					cout << "查找成功" << endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}

			if (!flag) {
				cout << "查无此人" << endl;

			}
		}
		else 
		{
			cout << "Error!" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
		system("pause");
		system("cls");

	}
	else
	{
		cout << "选择排序方式：" << endl << "1 按编号升序" << endl << "2 按编号降序" << endl;
		int select;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum;i++) 
		{
			int minOrmax = i;
			
			for (int j = i + 1; j < this->m_EmpNum; j++) 
			{
				if (select == 1)//升序
				{
					if (this->m_EmpArray[minOrmax]->m_id > this->m_EmpArray[j]->m_id)
					{
						minOrmax = j;
					}
				}
				else //降序
				{
					if (this->m_EmpArray[minOrmax]->m_id < this->m_EmpArray[j]->m_id)
					{
						minOrmax = j;
					}
				}
			}
			if (i != minOrmax) 
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrmax];
				this->m_EmpArray[minOrmax] = temp;
				
			}

		}
		cout << "排序成功" << endl;
		this->save();
		this->Show_Emp();
	}
}

void WorkerManager::Clean_File()
{
	cout << "确认清空？" << endl;
	cout << "1 确定" << endl << "2 返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) 
	{
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
				
			}
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功" << endl;
	}
	system("pause");
	system("csl");
}

WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}
