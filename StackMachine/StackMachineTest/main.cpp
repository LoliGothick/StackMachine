#include "StackMachineBuilder.h"
#include <fstream>
void main() {
	std::string path;
	std::string codeStr;
	std::string buf;
	path = "test.txt";
	//std::cin >> path;
	std::ifstream ifs(path);
	while (ifs&&std::getline(ifs, buf)) {
		codeStr += buf;
	}
	Compile(
		codeStr
	);
	std::cin >> path;
	/*///�X�^�b�N�}�V���p��
	StackMachine sm;
	///�萔�m��///
	sm.DC(3.998, "A");
	sm.DS(sizeof(int), "B");
	///���ߍ쐬///
	OrderVector orderv;
	orderv
		<< MakeCAST(_i,_d,Args<1>(sm["B"], sm["A"]))
		<< MakePRINT(_i,Args<5>(sm["B"]));
	///���ߊi�[///
	sm.SetOrderVector(orderv);
	///���s///
	sm.Run();*/
	/*
	double A=3.998;
	int B;
	B=(int)A;
	std::cout<<B<<std::endl;
	*/
}