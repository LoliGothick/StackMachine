#include "StackMachine.h"
void main() {
	///���z�}�V���p��
	StackMachine sm;
	///�萔�m��///
	//A DC 0
	sm.DC(0, "A");
	sm.DC(1, "B");
	sm.DS(4, "TEST");
	///���ߍ쐬///
	OrderVector orderv;
	orderv

		//TEST ADD A,B
		<< "TEST"<< MakeADD<int>()(Args<1>(sm["A"],sm["B"]))

		//PRINT A
		<< MakePRINT<int>()(Args<5>(sm["A"]))

		//JMP TEST
		<< MakeJMP()(Args<5>(sm["TEST"]),sm);

	///���ߊi�[///
	sm.SetOrderVector(orderv);
	///���s///
	sm.Run();
}