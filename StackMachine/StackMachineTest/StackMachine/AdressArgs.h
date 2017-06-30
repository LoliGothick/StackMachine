#pragma once
#include <array>
#include <tuple>
//���߂ɓn���A�h���X�\���̒�`<�����̐�>
template<int N>
struct  AdressArgs {
	std::array<void*, N> adrs;
public:
	AdressArgs(std::array<void*,N> _adrs):adrs(_adrs)
	{
	}
	AdressArgs() {}
	template<int M>
	char* GetAdr() {
		static_assert(M<= N&&M>0, "array range out");
		return (char*)adrs[M-1];
	}
};

/*template<>
struct  AdressArgs<1>
{
	char* adr1;
	AdressArgs(void* adr1) {
		this->adr1 = (char*)adr1;
	}
	AdressArgs() {}

};

template<>
struct  AdressArgs<2>
{
	char* adr1;
	char* adr2;
	AdressArgs(void* adr1, void* adr2) {
		this->adr1 = (char*)adr1;
		this->adr2 = (char*)adr2;
	}
	AdressArgs(){}
};

template<>
struct  AdressArgs<3>
{
	char* adr1;
	char* adr2;
	char* adr3;
	AdressArgs(void* adr1,void* adr2, void* adr3) {
		this->adr1 = (char*)adr1;
		this->adr2 = (char*)adr2;
		this->adr3 = (char*)adr3;
	}
	AdressArgs(){}
};

template<>
struct  AdressArgs<4>
{
	char* adr1;
	char* adr2;
	char* adr3;
	char* adr4;
	AdressArgs(void* adr1, void* adr2, void* adr3,void* adr4) {
		this->adr1 = (char*)adr1;
		this->adr2 = (char*)adr2;
		this->adr3 = (char*)adr3;
		this->adr4 = (char*)adr4;
	}
	AdressArgs() {}
};*/

//�G�C���A�X��`
template<int N>
using Args = AdressArgs<N>;

//AdressArgs�����֐�
template<class ..._Args>
auto Make_Arags(_Args... args) {
	return AdressArgs<sizeof...(_Args)>({ args... });
}
template<class ..._Args>
auto Make_Arags_for_tuple(std::tuple<_Args...> tuple) {
	return _Make_Arags_for_tuple (tuple, std::make_index_sequence<sizeof...(_Args)>());
}
template<size_t ...index,class ..._Args>
auto _Make_Arags_for_tuple(std::tuple<_Args...> tuple,std::index_sequence<index...>) {
	return AdressArgs<sizeof...(index)>({ (std::get<index>(tuple))... });
}