#ifndef PALA_HPP
#define PALA_HPP

/**
*	\version $Id: Pala.hpp 2660 2015-12-08 12:47:00Z bitti $
*	\file Pala.hpp
*	\brief Pala-luokan esittely.
*	\author ©2015 Santeri Hetekivi <santeri.hetekivi@eng.tamk.fi>
*/

//	Julkisen rajapinnan kirjastot:
#include "koordinaatti.hh"
#include "luettelotyypit.hh"

//	Luomani luokat
#include "Esine.hpp"
#include "Pelaaja.hpp"

/**
*	\brief Labyrintti-pelin palan tietoluokka.
*/
class Pala
{
	public:
		/**
		*	\brief Palan tyhjä rakentaja
		*
		*	Alustaa muuttujat.
		*
		*	\post Muuttujat on alustettu.
		*/
		Pala();
		/**
		*	\brief Palan kuormitettu rakentaja
		*
		*	Alustaa muuttujat annettuihin arvoihin.
		*
		*	\param[in] pala Palan tyyppi <code>Julkinen::PalaTyyppi</code>-luokkana.
		*	\param[in] rotaatio \c Palan rotaatio.
		*	\param[in] sijainti Palan sijainti <code>Julkinen::Koordinaatti</code>-luokkana.
		*	\param[in] tyyppi Palan erikoispala tyyppi <code>Julkinen::ErikoispalaTyyppi</code>-luokkana.
		*	\param[in] kohde Palan kohde <code>Julkinen::Koordinaatti</code>-luokkana.
		*	\param[in] esine Palan esine <code>Esine</code>-luokkana.
		*	\param[in] pelaaja Palan pelaaja <code>Pelaaja</code>-luokkana.
		*
		*	\post Muuttujat on alustettu.
		*/
		Pala(Julkinen::PalaTyyppi pala,
			unsigned int rotaatio,
			Julkinen::Koordinaatti sijainti,
			Julkinen::ErikoispalaTyyppi tyyppi = Julkinen::NORMAALI,
			Julkinen::Koordinaatti kohde = Julkinen::Koordinaatti(),
			Esine * esine = NULL,
			Pelaaja * pelaaja = NULL);
		/**
		*	\brief Purkaja.
		*
		*	\post No-throw takuu.
		*/
		~Pala();
		/**
		*	\brief Esineen kerääjä
		*
		*	Tarkistaa voiko palalla istuva pelaaja kerätä esineen, jos sellaista on.
		*
		*	\pre Esine on yritetty kerätä
		*
		*	\return Palauttaa <code>true</code>, jos keräys onnistui.
		*		Palauttaa <code>false</code>, jos keräys epäonnistui.
		*/
		bool keraaEsine();
	
		Julkinen::PalaTyyppi pala;
		unsigned int rotaatio;
		Julkinen::Koordinaatti sijainti;
		Julkinen::ErikoispalaTyyppi tyyppi = Julkinen::ErikoispalaTyyppi();
		Julkinen::Koordinaatti kohde = Julkinen::Koordinaatti();
		Esine * esine = NULL;
		Pelaaja * pelaaja = NULL;
};

#endif

