#include "Pelaaja.hpp"



Pelaaja::Pelaaja(Julkinen::PelaajaTyyppi _tyyppi,
	std::string _nimi, char _merkki,
	std::queue<Esine*> _kerättävätEsineet,
	std::vector<Esine*> _keratytEsineet,
	std::string _edellinentoiminto, bool _extraVuoro,
	bool _menetaVuoro, bool _onTyontanyt,
	bool _onLiikkunut)
{
	this->tyyppi = _tyyppi;
	this->nimi = _nimi;
	this->merkki = _merkki;
	this->kerättävätEsineet = _kerättävätEsineet;
	this->keratytEsineet = _keratytEsineet;
	this->edellinentoiminto = _edellinentoiminto;
	this->extraVuoro = _extraVuoro;
	this->menetaVuoro = _menetaVuoro;
	this->onTyontanyt = _onTyontanyt;
	this->onLiikkunut = _onLiikkunut;
}


Pelaaja::~Pelaaja()
{
}

std::string Pelaaja::kerattavatesineet()
{
	std::string str = "";
	if (!this->kerättävätEsineet.empty())
	{
		str += this->kerättävätEsineet.front()->merkki;
		for (unsigned int i = 0; i < this->kerättävätEsineet.size() - 1; i++)
		{
			str += "*";
		}
	}
	return str;
}

std::string Pelaaja::keratytesineet()
{
	std::string str = "";
	for each (Esine * esine in keratytEsineet)
	{
		str += esine->merkki;
	}
	return str;
}