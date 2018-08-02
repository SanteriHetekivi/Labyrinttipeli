#include "Data.hpp"



Data::Data()
{
	this->ruudut = std::map<Julkinen::Koordinaatti, Pala>();
	this->irtopala = Pala();
	this->pelaajat = std::map<std::string, Pelaaja>();
	this->esineet = std::map<char, Esine>();
}


Data::~Data()
{
}

Pelaaja * Data::haePelaaja(std::string name)
{
	Pelaaja * tmp = NULL;
	if (this->pelaajat.find(name) != this->pelaajat.end()) {
		tmp = &this->pelaajat[name];
	}
	if(tmp != NULL) return tmp;
	else throw Julkinen::Alustusvirhe(Julkinen::Alustusvirhe::VIRHE_ANNETTUA_PELAAJAA_EI_LOYTYNYT);
}

/*Esine * Data::haeEsine(char merkki)
{
	Esine * tmp = NULL;
	if (this->esineet.find(merkki) != this->esineet.end()) {
		tmp = &this->esineet[merkki];
	}
	return tmp;
}*/

Julkinen::Koordinaatti Data::haeEsine(char merkki) const
{
	Julkinen::Koordinaatti kordinaatti = Julkinen::Koordinaatti();
	std::vector<Pala> palat = this->haeKaikkiPalat();
	Esine * tmp = NULL;
	for (Pala pala : palat)
	{
		if (pala.esine != NULL && pala.esine->merkki == merkki) return pala.sijainti;
	}
	
	return kordinaatti;
}

Esine * Data::haeEsine(Julkinen::Koordinaatti const& kordinaatit)
{
	Esine * tmp = NULL;
	if (this->ruudut.find(kordinaatit) != this->ruudut.end()) {
		tmp = this->ruudut[kordinaatit].esine;
	}
	
	return tmp;
}

Pala * Data::haePala(Julkinen::Koordinaatti const& kordinaatit)
{
	Pala * tmp = NULL;
	if (this->ruudut.find(kordinaatit) != this->ruudut.end()) {
		tmp = &this->ruudut[kordinaatit];
	}
	else if(kordinaatit.onkoIrtopala())
	{
		tmp = this->haeIrtopala();
	}
	return tmp;
}

Pelaaja * Data::haePelaaja(Julkinen::Koordinaatti const& kordinaatit)
{
	Pelaaja * data = NULL;
	if (this->ruudut.find(kordinaatit) != this->ruudut.end()) {
		data = this->ruudut[kordinaatit].pelaaja;
	}
	return data;
}

Pala * Data::haeIrtopala()
{
	return &this->irtopala;
}

Julkinen::Koordinaatti Data::haePelaajanSijainti(Pelaaja pelaaja) const
{
	Julkinen::Koordinaatti kordinaatti = Julkinen::Koordinaatti();
	Pelaaja * tmp = NULL;
	for (auto elem : this->ruudut)
	{
		tmp = elem.second.pelaaja;
		if (tmp != NULL && tmp->merkki == pelaaja.merkki)
		{
			kordinaatti = elem.first;
			break;
		}
	}
	return kordinaatti;
}

Julkinen::Koordinaatti Data::haeEsineenSijainti(Esine esine) const
{
	Julkinen::Koordinaatti kordinaatti = Julkinen::Koordinaatti();
	Esine * tmp = NULL;
	for (auto elem : this->ruudut)
	{
		tmp = elem.second.esine;
		if (tmp != NULL && tmp->merkki == esine.merkki)
		{
			kordinaatti = elem.first;
			break;
		}
	}
	return kordinaatti;
}



std::vector<Esine> Data::haeKaikkiEsineet() const
{
	std::vector<Esine> data;
	std::vector<Pala> palat = this->haeKaikkiPalat();
	for (Pala pala : palat)
	{
		if(pala.esine != NULL) data.push_back(*pala.esine);
	}
	return data;
}
std::vector<Pala> Data::haeKaikkiPalat() const
{
	std::vector<Pala> data;
	for (auto elem : this->ruudut)
	{
		data.push_back(elem.second);
	}
	data.push_back(this->irtopala);
	return data;
}
std::vector<Pelaaja> Data::haeKaikkiPelaajat() const
{
	std::vector<Pelaaja> data;
	for (auto elem : this->pelaajat)
	{
		data.push_back(elem.second);
	}
	return data;
}

std::vector<Pala*> Data::haeKaikkiPalaOsoitteet()
{
	std::vector<Pala*> data;
	for (auto elem : this->ruudut)
	{
		Pala * tmp = this->haePala(elem.first);
		if(tmp != NULL) data.push_back(tmp);
	}
	if (&this->irtopala != NULL) data.push_back(&this->irtopala);
	return data;
}
std::vector<Pelaaja*> Data::haeKaikkiPelaajatOsoitteet()
{
	std::vector<Pelaaja*> data;
	for (auto elem : this->ruudut)
	{
		Pelaaja * tmp = this->haePelaaja(elem.first);
		if (tmp != NULL) data.push_back(tmp);
	}
	return data;
}

Pelaaja * Data::lisaaPelaaja(Pelaaja data, Julkinen::Koordinaatti const& kordinaatit)
{
	data.edellinentoiminto = "-";
	this->pelaajat[data.nimi] = data;
	if (!kordinaatit.onkoIrtopala())
	{
		if (this->ruudut.find(kordinaatit) != this->ruudut.end())
		{
			if (this->ruudut[kordinaatit].pelaaja == NULL)
			{
				this->ruudut[kordinaatit].pelaaja = &this->pelaajat[data.nimi];
				return &this->pelaajat[data.nimi];
			}
			else throw Julkinen::Alustusvirhe(Julkinen::Alustusvirhe::VIRHEELLINEN_SIJAINTI);
		}
		else throw Julkinen::Alustusvirhe(Julkinen::Alustusvirhe::VIRHEELLINEN_SIJAINTI);

	}
	else throw Julkinen::Alustusvirhe(Julkinen::Alustusvirhe::VIRHEELLINEN_SIJAINTI);

}

Esine * Data::lisaaEsine(Esine data, Julkinen::Koordinaatti const& kordinaatit)
{
	if (this->ruudut.find(kordinaatit) != this->ruudut.end())
	{
		if (this->ruudut[kordinaatit].esine == NULL)
		{
			this->esineet[data.merkki] = data;

			this->ruudut[kordinaatit].esine = &this->esineet[data.merkki];
			Pelaaja * pointer = NULL;
			try { pointer = this->haePelaaja(data.pelaaja); }
			catch (...) { throw; }
			if (pointer != NULL) pointer->kerättävätEsineet.push(&this->esineet[data.merkki]);
			else throw Julkinen::Alustusvirhe(Julkinen::Alustusvirhe::VIRHE_ANNETTUA_PELAAJAA_EI_LOYTYNYT);
			return &this->esineet[data.merkki];
		}
		else throw Julkinen::Alustusvirhe(Julkinen::Alustusvirhe::VIRHE_PALASSA_ON_JO_ESINE);
	}
	else throw Julkinen::Alustusvirhe(Julkinen::Alustusvirhe::VIRHEELLINEN_SIJAINTI);
}

Pala * Data::lisaaPala(Pala data, bool paivitaPala)
{
	Pala * osoite = NULL;
	if (data.rotaatio >= 1 && data.rotaatio <= 4)
	{
		if (data.sijainti.onkoIrtopala())
		{
			this->irtopala = data;
			osoite = this->haeIrtopala();
		}
		else
		{
			if (this->ruudut.find(data.sijainti) == this->ruudut.end() || paivitaPala)
			{
				this->ruudut[data.sijainti] = data;
				osoite = &this->ruudut[data.sijainti];
			}
			else throw Julkinen::Alustusvirhe(Julkinen::Alustusvirhe::VIRHEELLINEN_SIJAINTI);
		}
	}
	else throw Julkinen::Alustusvirhe(Julkinen::Alustusvirhe::VIRHEELLINEN_ROTAATIO);
	return osoite;
}

Pala * Data::lisaaIrtopala(Pala data)
{
	Pala * osoite = NULL;
	data.sijainti = Julkinen::Koordinaatti();
	this->irtopala = data;
	return this->haeIrtopala();
}

bool Data::liikutaPelaajaa(std::string nimi, Julkinen::Koordinaatti const& kordinaatit)
{
	bool result = false;
	Pelaaja * pelaaja = NULL;
	try { pelaaja = this->haePelaaja(nimi); }
	catch (...) { throw; }
	if (pelaaja != NULL)
	{
		Pala * vanhaPala = this->haePala(this->haePelaajanSijainti(*pelaaja));
		Pala * uusiPala = this->haePala(kordinaatit);
		if (vanhaPala != NULL && uusiPala != NULL)
		{
			vanhaPala->pelaaja = NULL;
			uusiPala->pelaaja = pelaaja;
			result = true;
		}
	} 
	return result;
}

Julkinen::Koordinaatti Data::pelaajanSeuraavanEsineenSijainti(const Pelaaja pelaaja) const
{
	Julkinen::Koordinaatti kordinaatti = Julkinen::Koordinaatti();
	if (!pelaaja.kerättävätEsineet.empty())
		kordinaatti = this->haeEsine(pelaaja.kerättävätEsineet.front()->merkki);
	return kordinaatti;
}