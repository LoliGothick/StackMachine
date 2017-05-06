#include "StackMachineBuilder.h"
void main() {
	Compile(
		"A idc -4;"
		"V idc 1,1,4,5,1,4,8,1,0,19;"
		"ENDSTR cdc 'E','N','D';"
		"START iadd A 4;"
		"iprint V A;"
		"icpa A 36;"
		"jmpb END ax;"
		"jmp START;"
		"END cprint '\n';"
		"cprint ENDSTR;"
		"cprint ENDSTR 1;"
		"cprint ENDSTR 2;"
		"cprint '\n';"
	);
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