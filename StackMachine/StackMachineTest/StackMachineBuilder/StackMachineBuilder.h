#pragma once


//�O���}�[�̒�`
/////////////////////////////////////////

class RunMachine;
struct Script
{
	Script();
	RunMachine CreateRunMachine();
	bool Parse(std::string::iterator& first, std::string::iterator& last);
private:
	struct ImplScript;
	ImplScript* implScript;

};

