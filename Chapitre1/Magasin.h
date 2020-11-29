#pragma once
#include "Produit.h"
//#include <array>
#include <vector>
#include <memory>
#include < algorithm >
class Magasin {
private:
//	std::array<std::array< std::shared_ptr<Produit>, 200 >, 3 > rayons;
	std::vector<  std::shared_ptr<Produit> > rayons; 
public:
	Magasin();
	~Magasin();
	template <class T>
	void addProduct(const T& prod) {
		rayons.push_back(std::make_shared<T>(prod));
		//std::sort(rayons.begin(), rayons.end(), [](auto& i, auto& j) {return i->getFamilleconst() < j->getFamilleconst(); });
	/*	auto& p = rayons.at(static_cast<int>(prod.getFamilleconst()));
		for (auto& i : p) {
			if (!i) {
				i = 
				return;
			}
		}*/
	}
	template <class T>
	void addProduct(T&& prod) {
		rayons.push_back(std::make_shared<T>(prod));
		/*auto& p = rayons.at(static_cast<int>(prod.getFamilleconst()));
		for (auto& i : p) {
			if (!i) {
				i = std::make_shared<T>(std::move(prod));
				return;
			}
		}*/
	}
	double totalAmmount()const;
	int nombreCommestible()const;
	std::vector< std::shared_ptr<Produit> > rayon(Famille f)const;
	std::shared_ptr<Produit> buyProduct(Famille f, TypeProduit t);
};