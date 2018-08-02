#ifndef PELAAJATOIMINTO_HPP
#define PELAAJATOIMINTO_HPP

/**
*	\version $Id: PelaajaToiminto.hpp 2660 2015-12-08 12:47:00Z bitti $
*	\file PelaajaToiminto.hpp
*	\brief PelaajaToiminto-luokan esittely.
*	\author ©2015 Santeri Hetekivi <santeri.hetekivi@eng.tamk.fi>
*/

//	Sisarluokka
#include "PelinNaytto.hpp"

//	Julkisen rajapinnan kirjastot:
#include "luettelotyypit.hh"
#include "koordinaatti.hh"
#include "vaittama.hh"
#include "toimintovirhe.hh"

//	STL:n kirjastot:
#include <stdlib.h>
#include <time.h>

//	Määritys liikkeen suunnalle
enum Liike { TULOSSA, MENOSSA };

/**
*	\brief Labyrintti-pelin pelaajan toimintojen suoritus luokka.
*/
class PelaajaToiminto : PelinNaytto
{

	public:
		/**
		*	\brief PelaajaToiminto luokan rakentaja
		*	
		*	\pre Annettu naytto ja data ovat oikeita osoitteita.
		*
		*	Asettaa käytettävän näytön, koon ja datan.
		*
		*	\param[in] naytto Käytettävä näyttö <code>Julkinen::Nayttorajapinta</code>-luokkan osoitteena.
		*	\param[in] koko Näytön koko <code>Julkinen::Koordinaatti</code>-luokkana.
		*	\param[in] data Käytettävä data <code>Data</code>-luokkan osoitteena.
		*/
		PelaajaToiminto(Julkinen::Nayttorajapinta* naytto, Julkinen::Koordinaatti const& koko, Data * data);
		/**
		*	\brief Purkaja.
		*
		*	\post No-throw takuu.
		*/
		~PelaajaToiminto();
		/**
		*	\brief Koon asettaja
		*
		*	Asettaa yksityisen kentän kokoa säilyttävän <code>Julkinen::Koordinaatti</code> luokan _koko
		*
		*	\param[in] koko Pelialueen koko <code>Julkinen::Koordinaatti</code>-luokkana.
		*/
		void asetaKoko(Julkinen::Koordinaatti const& koko);
		/**
		*	\brief Pelaajan liikuttaja
		*	
		*	\pre Osoite <code>Pelaaja</code>-luokaan on oikea. 
		*
		*	Hoitaa pelaajan liikuttamisen.
		*	Tätä kutsutaan <code>Peli</code> luokassa, 
		*	kun <code>Komentotulkki</code> luokka antaa liikkumis komennon tai
		*	oma <code>suoritaAutomaattiLiike</code> metodi suorittaa liikeen.
		*
		*	\param[in] suunta Liikkeen suunta <code>Julkinen::Suunta</code>-luokkana.
		*	\param[in] maara \c Liikkeen määrä.
		*	\param[in] pelaaja Liikutettava pelaaja <code>Pelaaja</code>-luokan osoitteena.
		*
		*	\exception Toimintovirhe irtopalan reuna on virheellinen.
		*	\exception Toimintovirhe irtopalan paikka on virheellinen.
		*	\exception Toimintovirhe irtopalan rotaatio on virheellinen.
		*	\exception Toimintovirhe pelaaja on jo työntänyt vuorollansa.
		*
		*	\post Tieto siitä onnistuko työntö
		*/
		bool Tyonna(Julkinen::Reuna reuna, unsigned int paikka, unsigned int rotaatio, Pelaaja * pelaaja);
		/**
		*	\brief Pelaajan liikuttaja
		*	
		*	\pre Osoite <code>Pelaaja</code>-luokaan on oikea. 
		*
		*	Hoitaa pelaajan työntö käskyn suorituksen.
		*	Tätä kutsutaan <code>Peli</code> luokassa,
		*	kun <code>Komentotulkki</code> luokka antaa työntö komennon
		*
		*	\param[in] reuna Laudan työntö reuna <code>Julkinen::Reuna</code>-luokkana.
		*	\param[in] paikka \c Työnnön paikka reunalta.
		*	\param[in] rotaatio \c Työnnettävän palan rotaatio.
		*	\param[in] pelaaja Työntävä pelaaja <code>Pelaaja</code>-luokan osoitteena.
		*
		*	\exception Toimintovirhe pelaaja ei ole työntänyt irtopalaa vuorollansa.
		*	\exception Toimintovirhe pelaaja on jo liikkunut vuorollansa.
		*	\exception Toimintovirhe liikkeen suunta on virheellinen.
		*	\exception Toimintovirhe pelaaja ei voi liikkua annettua määrää.

		*	\post Tieto siitä onnistuko liikkuminen
		*/
		bool Liiku(Julkinen::Suunta suunta, unsigned int maara, Pelaaja * pelaaja);

	private:

		bool TarkistaKordinaatit(int x, int y);
		bool TarkistaLiike(int x, int y, Julkinen::Suunta suunta, Liike liike, bool viimeinenLiike = true);
		bool onkoRuutuVapaa(Julkinen::Koordinaatti const & kordinaatti);
		bool tarkistaRuutu(Julkinen::Koordinaatti const & kordinaatti, Julkinen::Suunta suunta, Liike liike);

		void suoritaRuutu(Julkinen::Koordinaatti const & kordinaatti, Pelaaja * pelaaja);
		void suoritaAutomaattiLiike(int x, int y, Pelaaja * pelaaja);
		Pala LiikutaPalaa(Pala pala);
		void liikutaXY(int * x, int * y, const Julkinen::Suunta suunta);

		const std::vector<Julkinen::Suunta> suunnat = { Julkinen::ALAS, Julkinen::YLOS, Julkinen::VASEMMALLE,  Julkinen::OIKEALLE };
		Julkinen::Koordinaatti _koko;
		Data * _data;
};

#endif

