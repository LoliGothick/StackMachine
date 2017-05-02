#include "StackMachine.h"
void main() {
	///�X�^�b�N�}�V���p��
	StackMachine sm;
	///�萔�m��///
	sm.DC(0, "A");
	sm.DC(10, "MAX");
	sm.DC<std::string>("end", "ENDSTR");
	sm.DS(4, "TEST");
	sm.DS(4, "END");
	///���ߍ쐬///
	OrderVector orderv;
	orderv
		<<"TEST"<< MakeINC<int>()(Args<5>(sm["A"]))
		<<MakeCPA<int>()(Args<1>(sm["A"], sm["MAX"]), sm)
		<<MakePRINT<int>()(Args<5>(sm["A"]))
		<<MakeJMPB()(Args<1>(sm["END"],sm.GetAX()),sm)
		<<MakeJMP()(Args<5>(sm["TEST"]), sm)
		<<"END"<< MakePRINT<std::string>()(Args<5>(sm["ENDSTR"]));
	///���ߊi�[///
	sm.SetOrderVector(orderv);
	///���s///
	sm.Run();
}