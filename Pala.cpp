#include "Pala.hpp"

Pala::Pala()
{
	this->pala = Julkinen::PalaTyyppi();
	this->rotaatio = 0;
	this->sijainti = Julkinen::Koordinaatti();
	this->tyyppi = Julkinen::NORMAALI;
	this->kohde = Julkinen::Koordinaatti();;
	this->esine = NULL;
	this->pelaaja = NULL;
}

Pala::Pala(Julkinen::PalaTyyppi pala,
	unsigned int rotaatio,
	Julkinen::Koordinaatti sijainti,
	Julkinen::ErikoispalaTyyppi tyyppi,
	Julkinen::Koordinaatti kohde,
	Esine * esine,
	Pelaaja * pelaaja)
{
	this->pala = pala;
	this->rotaatio = rotaatio;
	this->sijainti = sijainti;
	this->tyyppi = tyyppi;
	this->kohde = kohde;
	this->esine = esine;
	this->pelaaja = pelaaja;
}


Pala::~Pala()
{
}


bool Pala::keraaEsine()
{
	bool kerasiko = false;
	if (this->pelaaja != NULL && !this->pelaaja->kerättävätEsineet.empty())
	{
		Esine * tmp = this->pelaaja->kerättävätEsineet.front();
		if (tmp == this->esine)
		{
			this->pelaaja->keratytEsineet.push_back(tmp);
			this->pelaaja->kerättävätEsineet.pop();
			this->esine = NULL;
			kerasiko = true;
		}
	}

	return kerasiko;
}