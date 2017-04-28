#pragma once
#include "AdressArgs.h"
#include "Order.h"
#include <iostream>
#include "Print.h"
#include <map>
#include <string>
#include <vector>
#include "OrderVector.h"

//�X�^�b�N�}�V��
class StackMachine {
	//���x���L��
	std::map<std::string, void*> label;
	//�������̈�
	char* Memory = new char[65536];
	//Memory�̋󂫗̈�̐擪�A�h���X���w���C���f�b�N�X
	int usedIndex;
	//�Ō�̖��߂��i�[����Ă���A�h���X
	char* endOrderAdr;
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
	char** GetPR() {
		return (char**)&Memory[8];
	}
	//ax���W�X�^�̃A�h���X
	char* GetAX() {
		return &Memory[12];
	}
	//GR(i)���W�X�^�̃A�h���X
	char* GetGR(int i) {
		if (!(i >= 1 && i <= 8))throw "GetGR():�͈͊O�ł�";
		return &Memory[20 + (i - 1) * 8];
	};

	StackMachine()
	{
		usedIndex = 84;
	};
	//���ߊi�[
	void SetOrderVector(OrderVector orders) {
		//�͂��߂̖��߂̃|�C���^���i�[����Ă�|�C���^��ۑ�
		*GetPR() = &Memory[usedIndex];
		for (int i = 0; i < orders.size(); i++) {
			AddOrder(orders[i]);
		}
		endOrderAdr = &Memory[usedIndex - 4];
	}
	//���s
	void Run() {
		while (true)
		{
			(*(OrderBase**)(*GetPR()))->Do();
			*GetPR() += 4;
			if (*GetPR() == endOrderAdr + 4)return;
		}
	}
private:
	void AddOrder(Order& order) {
		*(void**)(&Memory[usedIndex]) = order.ob;
		if (order.label != "") {
			*(char**)label[order.label] = &Memory[usedIndex];
		}
		usedIndex += 4;
	};
public:
	//DC���߁B(���l,���x����)
	template<typename T>
	void DC(T t, std::string labelName) {
		if (label.count(labelName) == 1)throw "���x�����Ē�`����܂���";
		*(T*)(&Memory[usedIndex]) = t;
		label[labelName] = &Memory[usedIndex];
		usedIndex += sizeof(T);
	};
	//DS���߁B(���l,���x����)
	void DS(int size, std::string labelName) {
		if (label.count(labelName) == 1)throw "���x�����Ē�`����܂���";
		label[labelName] = &Memory[usedIndex];
		usedIndex += size;
	};

	void* GetLabel(std::string labelName) {
		if (label.count(labelName) == 0)throw "����`�̃��x���ɃA�N�Z�X���悤�Ƃ��܂���";
		return label[labelName];
	};

	void* operator[](std::string labelName) {
		if (label.count(labelName) == 0)throw "����`�̃��x���ɃA�N�Z�X���悤�Ƃ��܂���";
		return label[labelName];
	}

};

#include "LD.h"
#include "JMP.h"
#include "ADD.h"