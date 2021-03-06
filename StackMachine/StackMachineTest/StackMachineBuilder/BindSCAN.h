#pragma once
template<typename type>
struct BindSCAN :boost::static_visitor<OrderBase*> {
	OrderBase* operator ()(...)const {
		throw std::string("errorArgs");
	}
	OrderBase* operator ()(Args<1> args)const {
		return MakeSCAN(type(), args);
	}
	OrderBase* operator ()(Args<2> args)const {
		return MakeSCAN(type(), args);
	}

	static OrderBase* _Make(VarArgs& va) {
		return boost::apply_visitor(BindSCAN(), va);
	}
	static auto Make() {
		return phx::bind(&BindSCAN::_Make, spt::_1);
	}
};