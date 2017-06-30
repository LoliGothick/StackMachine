#pragma once
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