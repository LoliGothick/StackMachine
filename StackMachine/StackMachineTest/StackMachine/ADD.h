#pragma once
template<typename type, typename AD>
struct ADD :OrderBase
{
private:
	AD ad;
	template<typename AD2>
	void Do2();
	template<>
	void Do2<Args<1>>()
	{
		(*(type*)ad.adr1) += (*(type*)ad.adr2);
	};
	template<>
	void Do2<Args<2>>()
	{
		*(type*)(ad.adr1 + *ad.x1) += *(type*)ad.adr2;
	};
	template<>
	void Do2<Args<3>>()
	{
		*(type*)ad.adr1 += *(type*)(ad.adr2 + *ad.x2);
	};
	template<>
	void Do2<Args<4>>()
	{
		*(type*)(ad.adr1 + *ad.x1)+= *(type*)(ad.adr2 + *ad.x2);
	};
public:
	virtual void Do() {
		Do2<AD>();
	};
	ADD(AD ad) :ad(ad) {}
};

template<typename AD>
struct ADD<char*,AD> :OrderBase
{
private:
	AD ad;
	template<typename AD2>
	void Do2();
	template<>
	void Do2<Args<1>>()
	{
		(*(char**)ad.adr1) += (*(int*)ad.adr2);
	};
	template<>
	void Do2<Args<2>>()
	{
		*(char**)(ad.adr1 + *ad.x1) += *(int*)ad.adr2;
	};
	template<>
	void Do2<Args<3>>()
	{
		*(char**)ad.adr1 += *(int*)(ad.adr2 + *ad.x2);
	};
	template<>
	void Do2<Args<4>>()
	{
		*(char**)(ad.adr1 + *ad.x1) += *(int*)(ad.adr2 + *ad.x2);
	};
public:
	virtual void Do() {
		Do2<AD>();
	};
	ADD(AD ad) :ad(ad) {}
};

template<typename Type,typename AD>
auto MakeADD(Type, AD ad)
{
	return new ADD<Type, AD>(ad);
}