#include "StackMachineCompiler.h"
#include <fstream>
void main() {
	std::string path;
	std::string buf;
	path = "test.txt";
	std::ifstream ifs(path);
	StackMachineCompiler smc;
	int lineCount=0;
	while (ifs&&std::getline(ifs, buf)) {
		lineCount++;
		 try {
			 smc.Compile(
				 buf
			 );
		 }
		 catch (std::string str) {
			 std::cout << str<<"Line:"<<lineCount<<std::endl<<std::endl;
			 std::cout<<"   " <<'"'<< buf <<'"'<< std::endl<<std::endl;
			 return;
		 }
	}

	smc.Run();
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