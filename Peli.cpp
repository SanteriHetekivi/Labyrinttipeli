#include "Peli.hpp"



Peli::Peli()
{
	this->_tila = ALUSTUS;
}


Peli::~Peli()
{
}

bool Peli::onkoAlustustilassa() const
{
	return (this->_tila == ALUSTUS);
}


void Peli::lisaaNaytto(Julkinen::Nayttorajapinta* naytto)
{
	ESIEHTO(this->onkoAlustustilassa());
	ESIEHTO(naytto != NULL);
	ESIEHTO(this->_naytto == NULL);
	//Peli on alustustilassa. Annettu parametri ei ole tyhjä. Näyttöä ei ole lisätty.
	if (this->onkoAlustustilassa() && naytto != NULL && this->_naytto == NULL)
	{
		this->_naytto = new PelinNaytto(naytto);

		this->_toiminto = new PelaajaToiminto(naytto, this->_koko, this->_data);
		_naytto->aloitaRakennus();
	}
}

void Peli::maaritaPelialueenKoko(Julkinen::Koordinaatti const& koko)
{
	ESIEHTO(this->onkoAlustustilassa());
	ESIEHTO(this->_naytto != NULL);
	this->_koko = koko;
	this->_toiminto->asetaKoko(koko);
}

void Peli::lisaaPelaaja(Julkinen::PelaajaTyyppi tyyppi, std::string const& nimi, char lyhenne, Julkinen::Koordinaatti const& sijainti)
{
	ESIEHTO(this->onkoAlustustilassa());
	ESIEHTO(!this->_koko.onkoIrtopala());
	Pelaaja tmp = Pelaaja(tyyppi, nimi, lyhenne);
	Pelaaja * pointer = NULL;
	try{ pointer = this->_data->lisaaPelaaja(tmp, sijainti); }
	catch (...) { throw; }
	if(pointer != NULL ) this->_pelaajat.push_back(pointer);
}

void Peli::lisaaPala(Julkinen::PalaTyyppi pala, unsigned int rotaatio, Julkinen::Koordinaatti const& sijainti)
{
	ESIEHTO(this->onkoAlustustilassa());
	ESIEHTO(this->_naytto != NULL);
	Pala tmp = Pala(pala, rotaatio, sijainti);
	try { this->_data->lisaaPala(tmp); }
	catch (...) { throw; }
}

void Peli::lisaaEsine(char merkki, Julkinen::Koordinaatti const& sijainti, std::string const& pelaaja)
{
	ESIEHTO(this->onkoAlustustilassa());
	Esine tmp = { merkki, pelaaja };
	try { this->_data->lisaaEsine(tmp, sijainti); }
	catch (...) { throw; }
}

void Peli::asetaPalanTyyppi(Julkinen::ErikoispalaTyyppi tyyppi, Julkinen::Koordinaatti const& sijainti, Julkinen::Koordinaatti const& kohde)
{
	ESIEHTO(this->onkoAlustustilassa());
	Pala * pala = this->_data->haePala(sijainti);
	ESIEHTO(pala != NULL);

	if (pala != NULL) {
		pala->tyyppi = tyyppi;
		pala->kohde = kohde;
	}

	JALKIEHTO(pala->tyyppi == tyyppi);
	JALKIEHTO(pala->kohde == kohde);
}

void Peli::alustusLopeta()
{
	if (this->_pelaajat.begin() != this->_pelaajat.end()) {
		this->vuorossa = this->_pelaajat.begin();
	}
	
	this->paivitaNaytto();
	this->_tila = PELI;
}

bool Peli::onkoPelitilassa() const
{
	return (this->_tila == PELI);
}

void Peli::komentoTyonna(Julkinen::Reuna reuna, unsigned int paikka, unsigned int rotaatio)
{
	ESIEHTO(this->onkoPelitilassa());
	try
	{
		this->_toiminto->Tyonna(reuna, paikka, rotaatio, *vuorossa);
	}
	catch (...)
	{
		throw;
	}
	this->paivitaNaytto();
	return;
}

void Peli::komentoLiiku(Julkinen::Suunta suunta, unsigned int maara)
{
	ESIEHTO(this->onkoPelitilassa());
	try
	{
		this->_toiminto->Liiku(suunta, maara, *vuorossa);
	}
	catch (Julkinen::Toimintovirhe virhe)
	{
		throw Julkinen::Toimintovirhe(virhe);
	}
	return;
}

bool Peli::vaihdaVuoro()
{
	ESIEHTO(this->onkoPelitilassa());
	Pelaaja * pelaaja = *vuorossa;
	if (!pelaaja->onTyontanyt && pelaaja->tyyppi != Julkinen::TIETOKONE) throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_IRTOPALAA_EI_OLE_TYONNETTY);
	else if (!pelaaja->onLiikkunut) throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_PELAAJA_EI_OLE_LIIKKUNUT);
	else
	{
		pelaaja->onTyontanyt = false;
		pelaaja->onLiikkunut = false;
		if (pelaaja->kerättävätEsineet.size() > 0)
		{
			if (!pelaaja->extraVuoro)
			{
				if (std::next(this->vuorossa) != this->_pelaajat.end()) {
					this->vuorossa = std::next(this->vuorossa);
				}
				else if (this->_pelaajat.begin() != this->_pelaajat.end())
				{
					this->vuorossa = this->_pelaajat.begin();
				}
				else return false;
			}
			else pelaaja->extraVuoro = false;
			pelaaja = *vuorossa;
			if (pelaaja->menetaVuoro)
			{
				pelaaja->onLiikkunut = true;
				pelaaja->onTyontanyt = true;
				pelaaja->menetaVuoro = false;
				this->vaihdaVuoro();
			}
			else this->paivitaNaytto();
		}
		else return false;
		return true;
	}
	return false;	
}

Julkinen::PelaajaTyyppi Peli::haeVuorossa()
{
	ESIEHTO(this->onkoPelitilassa());
	return (*vuorossa)->tyyppi;
}

void Peli::paivitaNaytto()
{
	_naytto->aloitaRakennus();

	/*std::vector<Pala*> palat = this->_data->haeKaikkiPalaOsoitteet();
	for (Pala * tmp : palat)
	{
		if (tmp->esine != NULL)
		{
			Esine esine = *tmp->esine;
			if (tmp->keraaEsine()) this->_naytto->ilmoitusEsinePoimittu(esine);
		}
	}*/
	/*std::vector<Pelaaja*> pelaajat = this->_data->haeKaikkiPelaajatOsoitteet();
	for (Pelaaja * tmp : pelaajat)
	{
		if (tmp->kerattyEsine != NULL)
		{
			Esine esine = *tmp->kerattyEsine;
			this->_naytto->ilmoitusEsinePoimittu(esine);
			tmp->kerattyEsine = NULL;
		}
	}
	*/
	this->_naytto->asetaData(*this->_data);
	this->_naytto->lopetaRakennus();
	this->_naytto->vuorossa((*vuorossa)->nimi);
}