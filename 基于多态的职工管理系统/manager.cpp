#include "manager.h"


//���캯��
Manager::Manager(int id, string name, int dId)
{
	this->m_id = id;
	this->m_name = name;
	this->m_deptId = dId;
}

//��ʾ������Ϣ
void Manager::showInfo()
{
	cout << "ְ����ţ�" << this->m_id;
	cout << "\tְ��������" << this->m_name;
	cout << "\t��λ��" << this->getDeptName();
	cout << "\tְ�𣺾����ְ��" << endl;
}

//��ȡ��λ����
string Manager::getDeptName()
{
	return string("����");
}