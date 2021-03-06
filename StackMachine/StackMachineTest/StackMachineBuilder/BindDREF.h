#pragma once
template<typename type>
struct BindDREF :boost::static_visitor<OrderBase*> {
	OrderBase* operator ()(...)const {
		throw std::string("errorArgs");
	}
	OrderBase* operator ()(Args<2> args)const {
		return MakeDREF(type(), args);
	}
	OrderBase* operator ()(Args<3> args)const {
		return MakeDREF(type(), args);
	}
	OrderBase* operator ()(Args<4> args)const {
		return MakeDREF(type(), args);
	}

	static OrderBase* _Make(VarArgs& va) {
		return boost::apply_visitor(BindDREF(), va);
	}
	static auto Make() {
		return phx::bind(&BindDREF::_Make, spt::_1);
	}
};