#pragma once
#include "stdafx.h"
namespace phx = boost::phoenix;
namespace spt = boost::spirit;
#include "StackMachine.h"
#include "CustomVariant.h"
#include "BindOrder.h"


//�O���}�[�̒�`
/////////////////////////////////////////

template<typename Iterator>
struct Script :spt::qi::grammar<Iterator>{
private:
	StackMachine sm;
	OrderVector ov;
	auto AddOrder() {
		return phx::bind([this](OrderBase* ob) {ov << ob; }, spt::_1);
	}
	auto AddOrderLabel() {
		return phx::bind([this](std::string str) { ov << str; }, spt::_1);
	}
public:
	void Run() { sm.SetOrderVector(ov); sm.Run(); }
	Script() :Script::base_type(Code) {
		std::vector<int> v = {1,2,3};
		using spt::qi::eps;
		using spt::qi::lit;
		using spt::qi::_val;
		using spt::qi::double_;
		using spt::qi::bool_;
		using spt::qi::int_;
		using spt::qi::alpha;
		using spt::qi::as_string;
		using spt::ascii::char_;
		using spt::qi::real_parser;
		using spt::qi::strict_real_policies;
		real_parser<double, strict_real_policies<double>> strict_double;
		Code = 
			*(
				(DC >> lit(';')) 
				| 
				(-(Label[AddOrderLabel()]>>lit(' '))>>Order[AddOrder()] >> lit(';'))
			);
		Char = lit('\'') >>char_>> lit('\'');
		Value = strict_double | int_|  Char|bool_;
		ValueAdr = Value[_val = BindValueAdr::Make(sm)];
		DC =
			(Label >> lit(' ') >> lit("idc") >> lit(' ') >> int_%',')[BindDCV::Make<int>(sm)] |
			(Label >> lit(' ') >> lit("ddc") >> lit(' ') >> double_%',')[BindDCV::Make<double>(sm)] |
			(Label >> lit(' ') >> lit("bdc") >> lit(' ') >> bool_%',')[BindDCV::Make<bool>(sm)] |
			(Label >> lit(' ') >> lit("cdc") >> lit(' ') >> Char%',')[BindDCV::Make<char>(sm)];
		Label =as_string[(+(char_('A', 'Z')))];
		LabelAdr = Label[_val = BindLabelAdr::Make(sm)];
		Register =
			lit("ax")[_val = sm.GetAX()] |
			lit("gr1")[_val = sm.GetGR(1)] |
			lit("gr2")[_val = sm.GetGR(2)] |
			lit("gr3")[_val = sm.GetGR(3)] |
			lit("gr4")[_val = sm.GetGR(4)] |
			lit("gr5")[_val = sm.GetGR(5)] |
			lit("gr6")[_val = sm.GetGR(6)] |
			lit("gr7")[_val = sm.GetGR(7)] |
			lit("gr8")[_val = sm.GetGR(8)];
		Adr = LabelAdr | Register|ValueAdr;
		Args1 = (Adr >> lit(' ') >> Adr)[_val = BindArgs1::Make()];
		Args3 = (Adr >> lit(' ') >> Adr >> lit(' ') >> Adr)[_val = BindArgs3::Make()];
		Args4 = (Adr >> lit(' ') >> Adr >> lit(' ') >> Adr >> lit(' ') >> Adr)[_val = BindArgs4::Make()];
		Args5 = (Adr)[_val=BindArgs5::Make()];
		Args = (Args1 | Args3 | Args4 | Args5);
		Order = (PRINT|ADD|LD|JMP|JMPB|CPA);
		JMP = lit("jmp") >> lit(' ') >> Args[_val = BindJMP::Make(sm)];
		JMPB = lit("jmpb") >> lit(' ') >> Args[_val = BindJMPB::Make(sm)];
		PRINT = 
			(lit("iprint") >> lit(' ') >> Args[_val = BindPRINT<int>::Make()])|
			(lit("dprint") >> lit(' ') >> Args[_val = BindPRINT<double>::Make()])|
			(lit("bprint") >> lit(' ') >> Args[_val = BindPRINT<bool>::Make()])|
			(lit("cprint") >> lit(' ') >> Args[_val = BindPRINT<char>::Make()]);
		LD=
			(lit("ild") >> lit(' ') >> Args[_val = BindLD<int>::Make()]) |
			(lit("dld") >> lit(' ') >> Args[_val = BindLD<double>::Make()]) |
			(lit("bld") >> lit(' ') >> Args[_val = BindLD<bool>::Make()]) |
			(lit("cld") >> lit(' ') >> Args[_val = BindLD<char>::Make()]);
		ADD =
			(lit("iadd") >> lit(' ') >> Args[_val = BindADD<int>::Make()]) |
			(lit("dadd") >> lit(' ') >> Args[_val = BindADD<double>::Make()]) |
			(lit("badd") >> lit(' ') >> Args[_val = BindADD<bool>::Make()]) |
			(lit("cadd") >> lit(' ') >> Args[_val = BindADD<char>::Make()]);
		CPA =
			(lit("icpa") >> lit(' ') >> Args[_val = BindCPA<int>::Make(sm)]) |
			(lit("dcpa") >> lit(' ') >> Args[_val = BindCPA<double>::Make(sm)]) |
			(lit("bcpa") >> lit(' ') >> Args[_val = BindCPA<bool>::Make(sm)]) |
			(lit("ccpa") >> lit(' ') >> Args[_val = BindCPA<char>::Make(sm)]);
	}
	//script�R�[�h�S�̂��܂Ƃ߂镶�@
	spt::qi::rule<Iterator>Code;
	//DC ����
	spt::qi::rule<Iterator>DC;
	//PRINT����
	spt::qi::rule<Iterator,OrderBase*>PRINT;
	//LD����
	spt::qi::rule<Iterator, OrderBase*>LD;
	//ADD����
	spt::qi::rule<Iterator, OrderBase*>ADD;
	//CPA����
	spt::qi::rule<Iterator, OrderBase*>CPA;
	//JMP����
	spt::qi::rule<Iterator, OrderBase*>JMP;
	//JMPB����
	spt::qi::rule<Iterator, OrderBase*>JMPB;
	//���s����
	spt::qi::rule<Iterator, OrderBase*>Order;
	//���x��
	spt::qi::rule<Iterator,std::string()>Label;
	//���x�����w���A�h���X
	spt::qi::rule<Iterator, void*>LabelAdr;
	//���W�X�^�̃A�h���X
	spt::qi::rule<Iterator, void*>Register;
	//�A�h���X
	spt::qi::rule<Iterator, void*>Adr;
	//Arg<1>
	spt::qi::rule<Iterator, Args<1>()>Args1;
	//Arg<3>
	spt::qi::rule<Iterator, Args<3>()>Args3;
	//Arg<4>
	spt::qi::rule<Iterator, Args<4>()>Args4;
	//Arg<5>
	spt::qi::rule<Iterator, Args<5>()>Args5;
	//Args<...>
	spt::qi::rule<Iterator, VarArgs()>Args;
	//char�`��
	spt::qi::rule<Iterator,char()>Char;
	//���l
	spt::qi::rule<Iterator, VarValue>Value;
	//���l�A�h���X
	spt::qi::rule<Iterator, void*>ValueAdr;

};


//�\����͎��s
void Compile(std::string str) {
	Script<std::_String_iterator<std::_String_val<std::_Simple_types<char>>> > script_parser;
	auto first = str.begin();
	auto last = str.end();
	bool r = spt::qi::parse(first, last, script_parser);
	if (first != last) // �ǂݍ��݂�����ĂȂ��Ƃ�
		throw "���@�G���[";
	if (r == false)throw "���@�G���[";
	script_parser.Run();
}

