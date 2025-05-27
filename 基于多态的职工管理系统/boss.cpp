#include "boss.h"

//构造函数
Boss::Boss(int id, string name, int dId)
{
	this->m_id = id;
	this->m_name = name;
	this->m_deptId = dId;
}

//显示个人信息
void Boss::showInfo()
{
	cout << "职工编号：" << this->m_id;
	cout << "\t职工姓名：" << this->m_name;
	cout << "\t岗位：" << this->getDeptName();
	cout << "\t职责：老板的职责" << endl;

}

//获取岗位名称
string Boss::getDeptName()
{
	return string("老板");
}
