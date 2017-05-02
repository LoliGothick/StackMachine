#include "StackMachine.h"
void main() {
	///�X�^�b�N�}�V���p��
	StackMachine sm;
	///�萔�m��///
	sm.DC(3.998, "A");
	sm.DS(sizeof(double), "B");
	///���ߍ쐬///
	OrderVector orderv;
	orderv
		<< MakeCAST<int, double>()(Args<1>(sm["B"], sm["A"]))
		<< MakePRINT<int>()(Args<5>(sm["B"]));
	///���ߊi�[///
	sm.SetOrderVector(orderv);
	///���s///
	sm.Run();
}