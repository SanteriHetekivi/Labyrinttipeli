#ifndef PELAAJA_HPP
#define PELAAJA_HPP

/**
*	\version $Id: Pelaaja.hpp 2660 2015-12-08 12:47:00Z bitti $
*	\file Pelaaja.hpp
*	\brief Pelaaja-luokan esittely.
*	\author ©2015 Santeri Hetekivi <santeri.hetekivi@eng.tamk.fi>
*/

//	Julkisen rajapinnan kirjastot:
#include "luettelotyypit.hh"

//	Luomani luokat
#include "Esine.hpp"

//	STL:n kirjastot:
#include <queue>
#include <vector>


/**
*	\brief Labyrintti-pelin pelaajan tietoluokka.
*/
class Pelaaja
{
public:
	/**
	*	\brief Pelaajan kuormitettu rakentaja
	*
	*	Alustaa muuttujat annettuihin arvoihin.
	*
	*	\param[in] _tyyppi Pelaajan tyyppi <code>Julkinen::PelaajaTyyppi</code>-luokkana.
	*	\param[in] _nimi \c Pelaajan nimi.
	*	\param[in] _merkki \c Pelaajan merkki.
	*	\param[in] _kerättävätEsineet Pelaajan kerättävät esineet <code>Julkinen::Esine</code>-luokka osoite jonona.
	*	\param[in] _kerättävätEsineet Pelaajan kerätyt esineet <code>Julkinen::Esine</code>-luokka osoite vektorina.
	*	\param[in] _edellinentoiminto \c Pelaajan edellinen toiminto.
	*	\param[in] _extraVuoro \c Tieto pelaajan extra vuorosta <code>true</code> tai <code>false</code>.
	*	\param[in] _menetaVuoro \c Tieto pelaajan menetetystä vuorosta <code>true</code> tai <code>false</code>.
	*	\param[in] _onTyontanyt \c Tieto onko pelaaja työntänyt <code>true</code> tai <code>false</code>.
	*	\param[in] _onLiikkunut \c Tieto onko pelaaja liikkunut <code>true</code> tai <code>false</code>.
	*
	*	\post Muuttujat on alustettu.
	*/
	Pelaaja(Julkinen::PelaajaTyyppi _tyyppi = Julkinen::TIETOKONE,
		std::string _nimi = "", char _merkki = ' ',
		std::queue<Esine*> _kerättävätEsineet = std::queue<Esine*>(),
		std::vector<Esine*> _keratytEsineet = std::vector<Esine*>(),
		std::string _edellinentoiminto = "", bool _extraVuoro = false,
		bool _menetaVuoro = false, bool _onTyontanyt = false,
		bool _onLiikkunut = false);
	/**
	*	\brief Purkaja.
	*
	*	\post No-throw takuu.
	*/
	~Pelaaja();

	/**
	*	\brief Pelaajan kerättävien esineiden hakija
	*
	*	Hakee muotoillun std::string muuttujan kerättäviestä esineistä.
	*
	*	\post Muotoiltu std::string muuttuja on luotu ja palautettu.
	*
	*	\return Muotoiltu std::string muuttuja kerättäviestä esineistä.
	*/
	std::string kerattavatesineet();
	/**
	*	\brief Pelaajan kerätyiden esineiden hakija
	*
	*	Hakee muotoillun std::string muuttujan kerätyistä esineistä.
	*
	*	\post Muotoiltu std::string muuttuja on luotu ja palautettu.
	*
	*	\return Muotoiltu std::string muuttuja kerätyistä esineistä.
	*/
	std::string keratytesineet();


	char merkki;

	Julkinen::PelaajaTyyppi tyyppi;

	std::string nimi;
	std::string edellinentoiminto;


	std::queue<Esine*> kerättävätEsineet;
	std::vector<Esine*> keratytEsineet;

	bool extraVuoro;
	bool menetaVuoro;
	bool onTyontanyt;
	bool onLiikkunut;
};

#endif