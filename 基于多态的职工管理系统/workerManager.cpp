#include "workerManager.h"

WorkerManager::WorkerManager()
{
	
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�

	//�ļ�������
	if (!ifs.is_open()) 
	{
		cout << "�ļ�������" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ����� ����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof()) 
	{
		cout << "�ļ�Ϊ��" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ������Ҽ�¼����
	int num = this->get_EmpNum();
	cout << "ְ������Ϊ��" << num << endl;
	this->m_EmpNum = num;
	this->m_FileIsEmpty = false;
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->init_Emp();
	
}

void WorkerManager::Show_menu()
{
	cout << "********************" << endl;
	cout << "��ӭʹ��ְ������ϵͳ" << endl;
	cout << "0 �˳�����" << endl;
	cout << "1 ���ְ��" << endl;
	cout << "2 ��ʾְ��" << endl;
	cout << "3 ɾ��ְ��" << endl;
	cout << "4 �޸�ְ��" << endl;
	cout << "5 ��ѯְ��" << endl;
	cout << "6 ����" << endl;
	cout << "7 �������" << endl;
}

void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);//�˳�����
}

void WorkerManager::Add_Emp()
{
	cout << "���������������" << endl;
	int addNum = 0;
	cin >> addNum;

	if (addNum > 0) 
	{
		int newSize = this->m_EmpNum + addNum; //�¿ռ�Ĵ�С

		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];

		//��ԭ�������ݿ������¿ռ�

		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//���������
		for (int i = 0; i < addNum;i++)
		{
			int id;
			string name;
			int dSelect;
			cout << "�������" << i + 1 << "����ְ���ı�ţ�" << endl;
			cin >> id;

			cout << "�������" << i + 1 << "����ְ�������֣�" << endl;
			cin >> name;

			cout << "�������" << i + 1 << "����ְ���ĸ�λ��" << endl;
			cout << "1 ְ��" << endl;
			cout << "2 ����" << endl;
			cout << "3 �ϰ�" << endl;
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

		//�ͷ�ԭ�еĿռ�
		delete[] this->m_EmpArray;
		//�����¿ռ��ָ��
		this->m_EmpArray = newSpace;

		this->m_EmpNum = newSize;

		this->m_FileIsEmpty = false;

		cout << "�ɹ������" << addNum << "����ְ��" << endl;

		//���浽�ļ���
		this->save();
		
		//��������������ص��ϼ�Ŀ¼
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
		cout << "�ļ�������" << endl;
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
		cout << "�ļ������ڻ�Ϊ�գ�" << endl;
	}
	else 
	{
		cout << "������ɾ��ְ����ţ�" << endl;
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

			//����ͬ�����ļ���
			this->save();
			cout << "ɾ���ɹ�" << endl;

		}
		else
		{
			cout << "Error! δ�ҵ�����" << endl;
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
		cout << "�ļ������ڻ�Ϊ�գ�" << endl;

	}
	else
	{
		cout << "�������޸�ְ����ţ�" << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1) 
		{
			delete this->m_EmpArray[ret];
			int newId = 0;
			string newName = "";
			int dselect = 0;
			cout << "�鵽��" << id << "ְ�����������µ�ְ���ţ�" << endl;
			cin >> newId;
			cout << "�������µ�����" << endl;
			cin >> newName;
			cout << "�������µĸ�λ" << endl;
			cout << "1 ְ��" << endl;
			cout << "2 ����" << endl;
			cout << "3 �ϰ�" << endl;
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

			cout << "�޸ĳɹ���" << endl;

			this->save();

		}
		else {
			cout << "Error! ���޴��ˡ�" << endl;

		}

	}
}

void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ�Ϊ�գ�" << endl;

	}
	else
	{
		cout << "��������ҷ�����" << endl;
		cout << "1 �����" << endl << "2 ������" << endl;
		int select = 0;
		cin >> select;
		if (select == 1) 
		{
			cout << "������ְ����ţ�" << endl;
			int id;
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1) 
			{
				cout << "���ҳɹ�" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else 
			{
				cout << "���޴��ˣ�" << endl;
			}
		}
		else if (select == 2)
		{
			bool flag = false;

			cout << "������ְ��������" << endl;
			string name;
			cin >> name;
			for (int i = 0; i < this->m_EmpNum ; i++)
			{
				if (this->m_EmpArray[i]->m_name == name) {
					cout << "���ҳɹ�" << endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}

			if (!flag) {
				cout << "���޴���" << endl;

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
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
		system("pause");
		system("cls");

	}
	else
	{
		cout << "ѡ������ʽ��" << endl << "1 ���������" << endl << "2 ����Ž���" << endl;
		int select;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum;i++) 
		{
			int minOrmax = i;
			
			for (int j = i + 1; j < this->m_EmpNum; j++) 
			{
				if (select == 1)//����
				{
					if (this->m_EmpArray[minOrmax]->m_id > this->m_EmpArray[j]->m_id)
					{
						minOrmax = j;
					}
				}
				else //����
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
		cout << "����ɹ�" << endl;
		this->save();
		this->Show_Emp();
	}
}

void WorkerManager::Clean_File()
{
	cout << "ȷ����գ�" << endl;
	cout << "1 ȷ��" << endl << "2 ����" << endl;
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
		cout << "��ճɹ�" << endl;
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
