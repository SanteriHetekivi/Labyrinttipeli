#ifndef PELI_HPP
#define PELI_HPP

/**
*	\version $Id: Peli.hpp 2660 2015-12-08 12:47:00Z bitti $
*	\file Peli.hpp
*	\brief Peli-luokan esittely.
*	\author ©2015 Santeri Hetekivi <santeri.hetekivi@eng.tamk.fi>
*/

//	Rajapinta
#include "pelirajapinta.hh"

//	Nayttö
#include "valmiiden_toteutus\include\naytto.hh"

//	Julkisen rajapinnan kirjastot:
#include "vaittama.hh"
#include "toimintovirhe.hh"

//	Luomani luokat
#include "PelaajaToiminto.hpp"
#include "PelinNaytto.hpp"
#include "Data.hpp"

//	STL:n kirjastot:
#include <map>

/**
*	\brief Labyrintti-pelin pelin toimintojen suorittava luokka.
*/
class Peli : public Julkinen::Pelirajapinta
{
	public:
		Peli();
		~Peli();
		/**
		*  \copydoc Julkinen::Pelirajapinta::onkoAlustustilassa() const
		*/
		virtual bool onkoAlustustilassa() const;
		/**
		*  \copydoc Julkinen::Pelirajapinta::lisaaNaytto(Nayttorajapinta* naytto)
		*/
		virtual void lisaaNaytto(Julkinen::Nayttorajapinta* naytto);
		/**
		*  \copydoc Julkinen::Pelirajapinta::maaritaPelialueenKoko(Julkinen::Koordinaatti const& koko)
		*/
		virtual void maaritaPelialueenKoko(Julkinen::Koordinaatti const& koko);
		/**
		*  \copydoc Julkinen::Pelirajapinta::lisaaPelaaja(PelaajaTyyppi tyyppi, std::string const& nimi, char lyhenne, Julkinen::Koordinaatti const& sijainti)
		*/
		virtual void lisaaPelaaja(Julkinen::PelaajaTyyppi tyyppi, std::string const& nimi, char lyhenne, Julkinen::Koordinaatti const& sijainti);
		/**
		*  \copydoc Julkinen::Pelirajapinta::lisaaPala(Julkinen::PalaTyyppi pala, unsigned int rotaatio, Julkinen::Koordinaatti const& sijainti)
		*/
		virtual void lisaaPala(Julkinen::PalaTyyppi pala, unsigned int rotaatio, Julkinen::Koordinaatti const& sijainti);
		/**
		*  \copydoc Julkinen::Pelirajapinta::lisaaEsine(char merkki, Julkinen::Koordinaatti const& sijainti, std::string const& pelaaja)
		*/
		virtual void lisaaEsine(char merkki, Julkinen::Koordinaatti const& sijainti, std::string const& pelaaja);
		/**
		*  \copydoc Julkinen::Pelirajapinta::asetaPalanTyyppi(Julkinen::ErikoispalaTyyppi tyyppi, Julkinen::Koordinaatti const& sijainti, Julkinen::Koordinaatti const& kohde = Julkinen::Koordinaatti())
		*/
		virtual void asetaPalanTyyppi(Julkinen::ErikoispalaTyyppi tyyppi, Julkinen::Koordinaatti const& sijainti, Julkinen::Koordinaatti const& kohde = Julkinen::Koordinaatti());
		/**
		*  \copydoc Julkinen::Pelirajapinta::alustusLopeta()
		*/
		virtual void alustusLopeta();
		/**
		*  \copydoc Julkinen::Pelirajapinta::onkoPelitilassa() const
		*/
		virtual bool onkoPelitilassa() const;
		/**
		*  \copydoc Julkinen::Pelirajapinta::komentoTyonna(Julkinen::Reuna reuna, unsigned int paikka, unsigned int rotaatio)
		*/
		virtual void komentoTyonna(Julkinen::Reuna reuna, unsigned int paikka, unsigned int rotaatio);
		/**
		*  \copydoc Julkinen::Pelirajapinta::komentoLiiku(Julkinen::Suunta suunta, unsigned int maara = 0)
		*/
		virtual void komentoLiiku(Julkinen::Suunta suunta, unsigned int maara = 0);
		/**
		*  \copydoc Julkinen::Pelirajapinta::vaihdaVuoro()
		*/
		virtual bool vaihdaVuoro();
		/**
		*  \copydoc Julkinen::Pelirajapinta::haeVuorossa()
		*/
		virtual Julkinen::PelaajaTyyppi haeVuorossa();

	private:
		
		void paivitaNaytto();
		enum Tila
		{
			ALUSTUS,
			PELI
		};
		Tila _tila;
		PelinNaytto * _naytto = NULL;
		PelaajaToiminto * _toiminto = NULL;
		std::vector<Pelaaja *>::iterator vuorossa;
		Julkinen::Koordinaatti _koko;
		std::vector<Pelaaja *> _pelaajat;
		Data * _data = new Data();
};
#endif