#pragma once

struct Order {
	OrderBase* ob;
	std::string label;
	Order(OrderBase* ob, std::string label) {
		this->ob = ob;
		this->label = label;
	}
};

//�ʖ���`
using OrderVector = std::vector<Order>;
static std::string __label="";
//�O���[�o�����Z�q�I�[�o�[���[�h
inline OrderVector& operator<<(OrderVector& ov, OrderBase* ob) {
	
	ov.push_back(Order(ob,__label));
	__label = "";
	return ov;
}
inline OrderVector& operator<<(OrderVector& ov, std::string _label) {
	if (__label != "")throw std::string("label����ꂽ���Ƃ�OrderBase*�����ĉ�����");
	__label = _label;
	return ov;
}