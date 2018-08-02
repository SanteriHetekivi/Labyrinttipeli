#ifndef ESINE_HPP
#define ESINE_HPP

/**
*	\version $Id: Esine.hpp 2660 2015-12-08 12:47:00Z bitti $
*	\file Esine.hpp
*	\brief Esine-luokan esittely.
*	\author ©2015 Santeri Hetekivi <santeri.hetekivi@eng.tamk.fi>
*/

//	STL:n kirjastot:
#include <string>

/**
*	\brief Labyrintti-pelin esineen tietoluokka.
*/
class Esine
{
	public:
		/**
		*	\brief Esineen tyhjä rakentaja
		*
		*	Alustaa muuttujat.
		*
		*	\post Muuttujat on alustettu.
		*/
		Esine();
		/**
		*	\brief Esineen kuormitettu rakentaja
		*
		*	Alustaa muuttujat annettuihin arvoihin.
		*	\param[in] merkki \c Esineen merkki.
		*	\param[in] pelaaja \c Esineen pelaajan nimi.
		*
		*	\post Muuttujat on alustettu.
		*/
		Esine(char merkki, std::string pelaaja);
		/**
		*	\brief Purkaja.
		*
		*	\post No-throw takuu.
		*/
		~Esine();

		char merkki;
		std::string pelaaja;
};
#endif