#pragma once
#include "AddressType.h"
#include "AdressArgs.h"
#include "Order.h"
#include "LD.h"
#include <map>
#include <string>

//�X�^�b�N�}�V��
class StackMachine {
	//���x���L��
	std::map<std::string, void*> label;
	//�������̈�
	char* Memory = new char[65536];
	//�Ō���̖��߂̃|�C���^���i�[����Ă���C���f�b�N�X
	int endOrder;
public:
	//sp���W�X�^�̃A�h���X
	char* GetSP() {
		return &Memory[0];
	};
	//bp���W�X�^�̃A�h���X
	char* GetBP() {
		return &Memory[4];
	};
	//pr���W�X�^�̃A�h���X
	char* GetPR() {
		return &Memory[8];
	}
	//ax���W�X�^�̃A�h���X
	char* GetAX() {
		return &Memory[12];
	}
	//GR(i)���W�X�^�̃A�h���X
	char* const GetGR(int i) {
		if (!(i >= 1 && i <= 8))throw "GetGR():�͈͊O�ł�";
		return &Memory[20+(i-1)*8];
	};

StackMachine()
{
	//�͂��߂̖��߂̃|�C���^���i�[����Ă�|�C���^��ۑ�
	*(void**)GetPR() =&Memory[84] ;
	endOrder = 80;
}
void AddOrder(OrderBase* order) {
	endOrder += 4;
	*(void**)(&Memory[endOrder]) = order;
}
};