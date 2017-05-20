#pragma once
#include "AdressArgs.h"
#include "type.h"
#include "Order.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "OrderVector.h"
#include <type_traits>

//�X�^�b�N�}�V��
class StackMachine {
	//���x���L��
	std::map<std::string, void*> label;
	//���l���x���L��
	std::map<int, void*> ilabel;
	std::map<double, void*> dlabel;
	std::map<bool, void*> blabel;
	std::map<char, void*> clabel;
	std::map<std::string, void*> slabel;
	//�������̈�
	char* Memory = new char[65536];
	//Memory�̋󂫗̈�̐擪�A�h���X���w���C���f�b�N�X
	int usedIndex;
	//�Ō�̖��߂��i�[����Ă���A�h���X
	char* endOrderAdr;
public:
	//sp���W�X�^�̃A�h���X
	char** GetSP() {
		return (char**)&Memory[0];
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
	void* GetAX() {
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
		*GetSP() = &Memory[usedIndex];
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
	//���l����
	void* ValueLabel(int t) {
		if (ilabel.count(t) == 1)return ilabel[t];
		int* tp = new (&Memory[usedIndex]) int;
		*tp = t;
		ilabel[t] = &Memory[usedIndex];
		usedIndex += sizeof(int);
		return ilabel[t];
	};
	void* ValueLabel(double t) {
		if (dlabel.count(t) == 1)return dlabel[t];
		double* tp = new (&Memory[usedIndex]) double;
		*tp = t;
		dlabel[t] = &Memory[usedIndex];
		usedIndex += sizeof(double);
		return dlabel[t];
	};
	void* ValueLabel(bool t) {
		if (blabel.count(t) == 1)return blabel[t];
		bool* tp = new (&Memory[usedIndex]) bool;
		*tp = t;
		blabel[t] = &Memory[usedIndex];
		usedIndex += sizeof(double);
		return blabel[t];
	};
	void* ValueLabel(char t) {
		if (clabel.count(t) == 1)return clabel[t];
		char* tp = new (&Memory[usedIndex]) char;
		*tp = t;
		clabel[t] = &Memory[usedIndex];
		usedIndex += sizeof(char);
		return clabel[t];
	};
	void* ValueLabel(std::vector<char> v) {
		std::string str;
		for each (auto c in v)
		{
			str.push_back(c);
		}
		if (slabel.count(str) == 1)return slabel[str];
		slabel[str] = &Memory[usedIndex];
		for each (auto c in v)
		{
			char* tp = new (&Memory[usedIndex]) char;
			*tp = c;
			usedIndex += sizeof(char);
		}
		return slabel[str];
	};

	//DC���߁B(���l,���x����)
	template<typename T>
	void DC(T t, std::string labelName) {
		if (label.count(labelName) == 1)throw "���x�����Ē�`����܂���";
		T* tp=new (&Memory[usedIndex]) T;
		*tp= t;
		label[labelName] = &Memory[usedIndex];
		usedIndex += sizeof(T);
	};


	//�z��DCV���߁B(vector{���l,���l,���l,���l....},���x����)
	template<typename T>
	void DCV(std::vector<T> t, std::string labelName) {
		if (label.count(labelName) == 1)throw "���x�����Ē�`����܂���";
		label[labelName] = &Memory[usedIndex];
		for (auto it = t.begin(); it != t.end(); it++) {
			T* tp = new (&Memory[usedIndex]) T;
			*tp = *it;
			usedIndex += sizeof(T);
		}
	};
	//DS���߁B(���l,���x����)
	void DS(int size, std::string labelName) {
		if (label.count(labelName) == 1)throw "���x�����Ē�`����܂���";
		label[labelName] = &Memory[usedIndex];
		usedIndex += size;
	};
	void* operator[](std::string labelName) {
		if (label.count(labelName) == 0) {
			DS(4, labelName);
		}
		return label[labelName];
	}

};

#include "PUSH.h"
#include "POP.h"
#include "LD.h"
#include "JMP.h"
#include "ADD.h"
#include "CPAEQ.h"
#include "CPANEQ.h"
#include "JMPB.h"
#include "INC.h"
#include "REF.h"
#include "DREF.h"
#include "LDR.h"
#include "CAST.h"
#include "Print.h"
#include "SPRINT.h"