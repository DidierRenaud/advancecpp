#pragma once
#include <string>
#include <iostream>

enum class Famille : char { Vetement = 0, Fruit, ProduitMenager };
enum class TypeProduit : char { Pomme = 0, Choux, Jean, LiquideVaisselle, Javel };

class Produit {
public:
	Produit(Famille f, TypeProduit t, double p, const std::string& description) :
		m_f{ f },
		m_t{ t },
		m_p{ p },
		m_desc{ description }{

	}
	Produit(const Produit& p) :
		m_f{ p.m_f },
		m_t{ p.m_t },
		m_p{ p.m_p },
		m_desc{ p.m_desc }{
		//string(const string& s); 

		std::cout << "Produit Copy content " << std::endl;
	}
	Produit(Produit&& p) :
		m_f{ std::move(p.m_f) },
		//m_t{ std::move(p.m_t) },
		m_p{ std::move(p.m_p) },
		m_desc{ std::move(p.m_desc) }{
		//string(string && s);
		std::cout << "Produit swap content " << std::endl;
	}

	Famille getFamilleconst() const { return m_f; };
	TypeProduit getTypeProduit()  const { return m_t; };
	double getPrix()  const { return m_p; }
	const std::string& Description()  const { return m_desc; }
	virtual bool commestible()const { return false; }
private:
	Famille m_f;
	TypeProduit m_t;
	double m_p;
	std::string m_desc;
};

struct Commestible : public Produit {
	Commestible(Famille f, TypeProduit t, double p, const std::string& description) :
		Produit(f, t, p, description) {}
	void mangerMoi()const { std::cout << " Manger Moi !!! " << Description() << std::endl; }
	virtual bool commestible()const { return true; }
};

struct Pomme : public Commestible {
	Pomme() :Commestible(Famille::Fruit, TypeProduit::Pomme, 10, "pomme") {}
	void reduireEnCompote() {
		std::cout << " Je deviens de la compote !!!!!" << std::endl;
	};
};
struct Choux : public Commestible {
	Choux() :Commestible(Famille::Fruit, TypeProduit::Choux, 5, "choux") {}
};
struct Jean : public Produit {
	Jean() :Produit(Famille::Vetement, TypeProduit::Jean, 80, "jeans") {}
};
struct LiquideVaisselle : public Produit {
	LiquideVaisselle() :Produit(Famille::ProduitMenager, TypeProduit::LiquideVaisselle, 2.7, "liquide vaisselle") {}
	void laver() {}
};
struct Javel : public Produit {
	Javel() :Produit(Famille::ProduitMenager, TypeProduit::Javel, 1.2, "javel") {}
	void laver() {}
};

