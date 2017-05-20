#pragma once
template<typename type>
struct BindPOP :boost::static_visitor<OrderBase*> {
	StackMachine* sm;
public: BindPOP(StackMachine* sm) :sm(sm) {}
		template<class Args>
		OrderBase* operator ()(Args)const {
			return nullptr;
		}
		template<>
		OrderBase* operator ()(Args<1> args)const {
			return MakePOP(type(), args, *sm);
		}
		template<>
		OrderBase* operator ()(Args<5> args)const {
			return MakePOP(type(), args, *sm);
		}

		static OrderBase* _Make(StackMachine* sm, VarArgs& va) {
			return boost::apply_visitor(BindPOP<type>(sm), va);
		}
		static auto Make(StackMachine& sm) {
			return phx::bind(&BindPOP::_Make, &sm, spt::_1);
		}
};