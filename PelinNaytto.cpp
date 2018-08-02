#include "PelinNaytto.hpp"



PelinNaytto::PelinNaytto(Julkinen::Nayttorajapinta* naytto)
{
	ESIEHTO(naytto != NULL);
	this->_naytto = naytto;
}

void PelinNaytto::asetaData(Data const data)
{
	this->_data = data;
}

PelinNaytto::~PelinNaytto()
{
	delete this->_naytto;
}

void PelinNaytto::aloitaRakennus()
{
	_naytto->komentoAloitaRakennus();
}

void PelinNaytto::lopetaRakennus()
{
	ESIEHTO(this->_naytto != NULL);
	ESIEHTO(!this->_naytto->onTulostustilassa());

	for (Pala tmp : this->_data.haeKaikkiPalat())
	{
		this->lisaaPala(tmp);
	}
	for (Pelaaja tmp : this->_data.haeKaikkiPelaajat())
	{
		this->lisaaPelaaja(tmp);
	}
	for (Esine tmp : this->_data.haeKaikkiEsineet())
	{
		this->lisaaEsine(tmp);
	}
	for (Pelaaja tmp : this->_data.haeKaikkiPelaajat())
	{
		_naytto->tulostaPelaajantiedot(tmp.nimi,
			tmp.keratytesineet(),
			tmp.kerattavatesineet(),
			tmp.edellinentoiminto);
	}
	_naytto->komentoLopetaRakennus();
}

void PelinNaytto::vuorossa(std::string const& nimi)
{
	this->_naytto->ilmoitusVuorossa(nimi);
}

void PelinNaytto::ilmoitusEsinePoimittu(Esine esine)
{
	this->_naytto->ilmoitusEsinePoimittu(esine.merkki, esine.pelaaja);
}

void PelinNaytto::ilmoitusErikoispalaanAstuttu(const Pala pala, const Pelaaja pelaaja)
{
	this->_naytto->ilmoitusErikoispalaanAstuttu(pala.tyyppi, pelaaja.nimi);
}

void PelinNaytto::tulostaVirhe(Julkinen::Toimintovirhe virhe)
{
	std::cout << virhe << std::endl;
}

void PelinNaytto::lisaaPelaaja(Pelaaja pelaaja)
{
	try
	{
		_naytto->pelaajaLaudalle(pelaaja.merkki, this->_data.haePelaajanSijainti(pelaaja));
	}
	catch (...)
	{
		throw;
	}
}

void PelinNaytto::lisaaPala(Pala pala)
{
	try
	{
		_naytto->palaLaudalle(pala.pala, pala.tyyppi, pala.rotaatio, pala.sijainti, pala.kohde);
	}
	catch (...)
	{
		throw;
	}
}

void PelinNaytto::lisaaEsine(Esine esine)
{
	try
	{
		_naytto->esineLaudalle(esine.merkki, this->_data.haeEsineenSijainti(esine));
	}
	catch (...)
	{
		throw;
	}
}