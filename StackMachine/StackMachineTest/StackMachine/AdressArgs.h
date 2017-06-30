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
template<class ...Args_>
auto Make_Arags(Args_&&... args) {
	return AdressArgs<sizeof...(Args_)>({ std::forward<Args_>(args)... });
}
template<class ...Args_>
auto Make_Arags_for_tuple(const std::tuple<Args_...>& tuple) {
	return Make_Arags_for_tuple_impl (tuple, std::make_index_sequence<sizeof...(Args_)>());
}
template<size_t ...index,class ...Args_>
auto Make_Arags_for_tuple_impl(const std::tuple<Args_...>& tuple,std::index_sequence<index...>) {
	return AdressArgs<sizeof...(index)>({ (std::get<index>(tuple))... });
}