#pragma once
#include "StackMachineBuilder.h"
#include "StackMachine.h"

class StackMachineCompiler {
	StackMachineBuilder::Script script_parser;
public:
	void Run() {
		script_parser.CreateRunMachine().Run();
	}
	//�\����͎��s
	void Compile(std::string str) {
		auto first = str.begin();
		auto last = str.end();
		bool r = script_parser.Parse(first, last);
		if (first != last) // �ǂݍ��݂�����ĂȂ��Ƃ�
			throw std::string("Syntax Error  ");
		if (r == false)throw std::string("Syntax Error  ");
	}
};