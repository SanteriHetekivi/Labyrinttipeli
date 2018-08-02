#ifndef PELINNAYTTO_HPP
#define PELINNAYTTO_HPP

/**
*	\version $Id: PelinNaytto.hpp 2660 2015-12-08 12:47:00Z bitti $
*	\file PelinNaytto.hpp
*	\brief PelinNaytto-luokan esittely.
*	\author ©2015 Santeri Hetekivi <santeri.hetekivi@eng.tamk.fi>
*/

//	Rajapinta:
#include "nayttorajapinta.hh"

//	Pelin data luokka:
#include "Data.hpp"

//	Julkisen rajapinnan kirjastot:
#include "vaittama.hh"
#include "toimintovirhe.hh"
#include "alustusvirhe.hh"

//	STL:n kirjastot:
#include <iostream>


/**
*	\brief Labyrintti-pelin pelin toimintojen näyttöön piirtäjä.
*/
class PelinNaytto
{
public:
	/**
	*	\brief PelinNaytto rakentaja
	*
	*	\pre Annettu osoite näyttöön on kelvollinen.
	*
	*	Asettaa käytettävän näytön.
	*
	*	\param[in] naytto Käytettävä näyttö <code>Julkinen::Nayttorajapinta</code>-luokkan osoitteena.
	*/
	PelinNaytto(Julkinen::Nayttorajapinta* naytto);
	/**
	*	\brief Purkaja.
	*
	*	\post No-throw takuu.
	*/
	~PelinNaytto();
	/**
	*	\brief Pelidatan asettaja
	*
	*	Asettaa käytettävän datan.
	*
	*	\param[in] data Käytettävä data <code>Data</code>-luokkana.
	*/
	void asetaData(Data const data);
	/**
	*	\brief Rakennuksen aloittaja
	*
	*	Käskee osoitettua <code>Julkinen::Nayttorajapinta</code>-luokkaa aloittamaan rakennuksen.
	*
	*	\post Osoitettua <code>Julkinen::Nayttorajapinta</code>-luokka rakennus tilassa.
	*/
	void aloitaRakennus();
	/**
	*	\brief Rakennuksen lopettaja
	*
	*	\pre Osoitettu <code>Julkinen::Nayttorajapinta</code>-luokka on rakennustilassa.
	*
	*	Asettaa kaiken datan näytölle ja lopettaa rakennuksen.
	*
	*	\post Kaikki data näytöllä. Osoitettua <code>Julkinen::Nayttorajapinta</code>-luokka tulostus tilassa.
	*/
	void lopetaRakennus();
	/**
	*	\brief Vuorossa olevan tulostaja
	*
	*	Kertoo <code>Julkinen::Nayttorajapinta</code>-luokkalle kuka on vuorossa.
	*
	*	\param[in] nimi \c Vuorossa olevan pelaajan nimi.
	*/
	void vuorossa(std::string const& nimi);
	/**
	*	\brief Erikoispalaan astumisesta ilmoittaja
	*
	*	Kertoo <code>Julkinen::Nayttorajapinta</code>-luokkalle kuka astui mihin erikoispalaan.
	*
	*	\param[in] pala Astuttu pala <code>Pala</code>-luokkana.
	*	\param[in] pelaaja Astunut pelaaja <code>Pelaaja</code>-luokkana
	*/
	void ilmoitusErikoispalaanAstuttu(Pala const pala, Pelaaja const pelaaja);
	/**
	*	\brief Esineen poiminnasta ilmoittaja
	*
	*	Kertoo <code>Julkinen::Nayttorajapinta</code>-luokkalle kuka poimi minkä esineen.
	*
	*	\param[in] esine Poimittu esine <code>Esine</code>-luokkana.
	*/
	void ilmoitusEsinePoimittu(Esine const esine);
	/**
	*	\brief Virheen tulostaja.
	*
	*	Tulostaa toimintavirheen.
	*
	*	\param[in] virhe Tulostettava virhe <code>Julkinen::Toimintovirhe</code>-luokkana.
	*/
	void tulostaVirhe(Julkinen::Toimintovirhe virhe);

private:
	void lisaaPelaaja(Pelaaja);
	void lisaaPala(Pala pala);
	void lisaaEsine(Esine esine);

	Julkinen::Nayttorajapinta* _naytto = NULL;
	Data _data;
};
#endif

