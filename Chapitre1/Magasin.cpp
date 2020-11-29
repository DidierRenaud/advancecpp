
#include "Magasin.h"
#include "Produit.h"
#include < utility >
#include < numeric >
Magasin::Magasin() {
	//fill(nullptr);
	/*for (auto& r : rayons) {
		r.fill(std::shared_ptr<Produit>());
	}*/
}

Magasin::~Magasin() {
}


double Magasin::totalAmmount()const {
	return std::accumulate(rayons.begin(), rayons.end(), 0.0, [](double d, auto& item) { return d+item->getPrix(); });
}

std::shared_ptr<Produit> Magasin::buyProduct(Famille f, TypeProduit t) {
	auto iterator = std::find_if(rayons.begin(), rayons.end(), [=](auto& i) { return i->getFamilleconst() == f && i->getTypeProduit() == t; });
	if (iterator != rayons.end()) {
		auto result= *iterator;
		rayons.erase(iterator);
		return result;
	}
	return std::shared_ptr<Produit>();
	//fill(nullptr);
	/*for (auto& r : rayons) {
		for (auto& p : r) {
			if (nullptr != p) {
				if ((p->getFamilleconst() == f) && (p->getTypeProduit() == t)) {
					return std::exchange(p, std::shared_ptr<Produit>());
				}
			}
		}
	}
	return nullptr;*/
}
std::vector< std::shared_ptr<Produit> >  Magasin::rayon(Famille f) const {
	auto itf = std::lower_bound(rayons.begin(), rayons.end(),
		f, [](auto& j, Famille f) {return  j->getFamilleconst() < f; });
	auto ite = std::upper_bound(rayons.begin(), rayons.end(),
		f, [](Famille f, auto& j) {return f < j->getFamilleconst(); }  );
	return std::vector< std::shared_ptr<Produit> >(itf, ite);
}

int  Magasin::nombreCommestible()const {
	return std::count_if(rayons.begin(), rayons.end(), [=](auto& i) { return dynamic_cast<Commestible*>(i.get()) != nullptr; });
	/*int ctr{ 0 };
	for (auto& r : rayons) {
		for (auto& p : r) {
			if (nullptr != p) 
			{
				try{
					dynamic_cast<Commestible&>(*p); 
					++ctr;
				}
				catch (...) {

				}
			}
		}
	}
	return ctr;*/
}
