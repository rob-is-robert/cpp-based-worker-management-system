#include "employee.h"

//���캯��
Employee::Employee(int id, string name, int dId)
{

	this->m_id = id;
	this->m_name = name;
	this->m_deptId = dId;
}

//��ʾ������Ϣ
void Employee::showInfo()
{
	cout << "ְ����ţ�" << this->m_id;
	cout << "\tְ��������" << this->m_name;
	cout << "\t��λ��" << this->getDeptName();
	cout << "\tְ��Ա����ְ��" << endl;

}

//��ȡ��λ����
string Employee::getDeptName()
{
	return string("Ա��");
}
