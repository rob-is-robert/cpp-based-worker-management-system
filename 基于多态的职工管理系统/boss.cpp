#include "boss.h"

//���캯��
Boss::Boss(int id, string name, int dId)
{
	this->m_id = id;
	this->m_name = name;
	this->m_deptId = dId;
}

//��ʾ������Ϣ
void Boss::showInfo()
{
	cout << "ְ����ţ�" << this->m_id;
	cout << "\tְ��������" << this->m_name;
	cout << "\t��λ��" << this->getDeptName();
	cout << "\tְ���ϰ��ְ��" << endl;

}

//��ȡ��λ����
string Boss::getDeptName()
{
	return string("�ϰ�");
}
