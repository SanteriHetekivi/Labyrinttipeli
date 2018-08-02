#ifndef DATA_HPP
#define DATA_HPP

/**
*	\version $Id: Data.hpp 2660 2015-12-08 12:47:00Z bitti $
*	\file Data.hpp
*	\brief Data-luokan esittely.
*	\author ©2015 Santeri Hetekivi <santeri.hetekivi@eng.tamk.fi>
*/

//	Julkisen rajapinnan kirjastot:
#include "luettelotyypit.hh"
#include "koordinaatti.hh"
#include "alustusvirhe.hh"

//	Luomani luokat
#include "Pelaaja.hpp"
#include "Esine.hpp"
#include "Pala.hpp"

//	STL:n kirjastot:
#include <vector>
#include <map>

class Data
{
public:
	/**
	*	\brief Datan rakentaja
	*
	*	Alustaa muuttujat.
	*
	*	\post Muuttujat on alustettu.
	*/
	Data();
	/**
	*	\brief Purkaja.
	*
	*	\post No-throw takuu.
	*/
	~Data();
	/**
	*	\brief Pelaajan osoitteen nimestä hakija.
	*
	*	Hakee nimeä vastaavan <code>Pelaaja</code>-luokan osoitteen. 
	*
	*	\param[in] name \c Haettavan pelaajan nimi.
	*
	*	\exception Alustusvirhe pelaajaa ei löytynyt.
	*
	*	\post Pelaajan osoite on haettu.
	*
	*	\return Osoite haluttuun pelaajaan
	*/
	Pelaaja * Data::haePelaaja(std::string name);
	/**
	*	\brief Esineen kordinaattien hakija.
	*
	*	Hakee merkkiä vastaavan <code>Esine</code>-luokan kordinaatit.
	*
	*	\param[in] merkki \c Haettavan esineen merkki.
	*
	*	\post Esineen sijainti on haettu.
	*
	*	\return Merkkiä vastaavan <code>Esine</code>-luokan kordinaatit <code>Julkinen::Koordinaatti</code>-luokkana.
	*/
	Julkinen::Koordinaatti Data::haeEsine(char merkki) const;
	/**
	*	\brief Esineen osoitteen hakija.
	*
	*	Hakee <code>Julkinen::Koordinaatti</code>-luokkaa vastaavan
	*	<code>Esine</code>-luokan osoitteen.
	*
	*	\param[in] kordinaatit Haettavan esineen kordinaatit <code>Julkinen::Koordinaatti</code>-luokkana.
	*
	*	\post Esineen osoite on haettu.
	*
	*	\return Merkkiä vastaavan <code>Esine</code>-luokan osoite.
	*/
	Esine * haeEsine(Julkinen::Koordinaatti const& kordinaatit);
	/**
	*	\brief Palan osoitteen hakija.
	*
	*	Hakee <code>Julkinen::Koordinaatti</code>-luokkaa vastaavan
	*	<code>Pala</code>-luokan osoitteen.
	*
	*	\param[in] kordinaatit Haettavan palan kordinaatit <code>Julkinen::Koordinaatti</code>-luokkana.
	*
	*	\post Palan osoite on haettu.
	*
	*	\return Merkkiä vastaavan <code>Pala</code>-luokan osoite.
	*/
	Pala * Data::haePala(Julkinen::Koordinaatti const&  kordinaatit);
	/**
	*	\brief Pelaajan osoitteen hakija.
	*
	*	Hakee <code>Julkinen::Koordinaatti</code>-luokkaa vastaavan
	*	<code>Pelaaja</code>-luokan osoitteen.
	*
	*	\param[in] kordinaatit Haettavan pelaajan kordinaatit <code>Julkinen::Koordinaatti</code>-luokkana.
	*
	*	\post Pelaajan osoite on haettu.
	*
	*	\return Merkkiä vastaavan <code>Pelaaja</code>-luokan osoite.
	*/
	Pelaaja * Data::haePelaaja(Julkinen::Koordinaatti const&  kordinaatit);
	/**
	*	\brief Irtopalan osoitteen hakija.
	*
	*	Hakee irtopalan osoitteen.
	*
	*	\post Irtopalan osoite on haettu.
	*
	*	\return Irtopalaksi merkityn <code>Pala</code>-luokan osoite.
	*/
	Pala * Data::haeIrtopala();

	/**
	*	\brief Pelaajan sijainnin hakija.
	*
	*	Hakee <code>Pelaaja</code>-luokkaa vastaavan <code>Pelaaja</code>-luokan kordinaatit.
	*
	*	\param[in] pelaaja Haettava pelaaja <code>Pelaaja</code>-luokkana.
	*
	*	\post Pelaajan sijainti on haettu.
	*
	*	\return Merkkiä vastaavan <code>Pelaaja</code>-luokan kordinaatit <code>Julkinen::Koordinaatti</code>-luokkana.
	*/
	Julkinen::Koordinaatti haePelaajanSijainti(Pelaaja pelaaja) const;
	/**
	*	\brief Esineen sijainnin hakija.
	*
	*	Hakee <code>Esine</code>-luokkaa vastaavan <code>Esine</code>-luokan kordinaatit.
	*
	*	\param[in] esine Haettava esine <code>Esine</code>-luokkana.
	*
	*	\post Esineen sijainti on haettu.
	*
	*	\return Merkkiä vastaavan <code>Esine</code>-luokan kordinaatit <code>Julkinen::Koordinaatti</code>-luokkana.
	*/
	Julkinen::Koordinaatti haeEsineenSijainti(Esine esine) const;

	/**
	*	\brief Kaikkien esineiden hakija.
	*
	*	Hakee kaikki pelilaudalla olevat esineet <code>Esine</code>-luokkina.
	*
	*	\post Kaikki esineet on haettu.
	*
	*	\return Vektori joka sisältää kaikki esineet <code>Esine</code>-luokkina.
	*/
	std::vector<Esine> haeKaikkiEsineet() const;
	/**
	*	\brief Kaikkien palojen hakija.
	*
	*	Hakee kaikki pelilaudalla olevat palat <code>Pala</code>-luokkina.
	*
	*	\post Kaikki palat on haettu.
	*
	*	\return Vektori joka sisältää kaikki palat <code>Pala</code>-luokkina.
	*/
	std::vector<Pala> haeKaikkiPalat() const;
	/**
	*	\brief Kaikkien pelaajien hakija.
	*
	*	Hakee kaikki pelilaudalla olevat pelaajat <code>Pelaaja</code>-luokkina.
	*
	*	\post Kaikki pelaajat on haettu.
	*
	*	\return Vektori joka sisältää kaikki pelaajat <code>Pelaaja</code>-luokkina.
	*/
	std::vector<Pelaaja> haeKaikkiPelaajat() const;

	/**
	*	\brief Kaikkien palojen osoitteiden hakija.
	*
	*	Hakee kaikki pelilaudalla olevat palat <code>Pala</code>-luokkien osoitteina.
	*
	*	\post Kaikkien pelaajien osoitteet on haettu.
	*
	*	\return Vektori joka sisältää kaikki palat <code>Pala</code>-luokan osoitteina.
	*/
	std::vector<Pala*> haeKaikkiPalaOsoitteet();
	/**
	*	\brief Kaikkien pelaajien osoitteiden hakija.
	*
	*	Hakee kaikki pelilaudalla olevat pelaajat <code>Pelaaja</code>-luokkien osoitteina.
	*
	*	\post Kaikkien palojen osoitteet on haettu.
	*
	*	\return Vektori joka sisältää kaikki pelaajat <code>Pelaaja</code>-luokan osoitteina.
	*/
	std::vector<Pelaaja*> haeKaikkiPelaajatOsoitteet();

	/**
	*	\brief Pelaajan lisääjä
	*
	*	Lisää annetun pelaajan peliin ja palauttaa sen osoitteen.
	*
	*	\param[in] data Lisättävä pelaaja <code>Pelaaja</code>-luokkana.
	*	\param[in] kordinaatit Lisättävän pelaajan kordinaatit <code>Julkinen::Koordinaatti</code>-luokkana.
	*
	*	\exception Alustusvirhe virheellinen sijainti. Kordinaateissa on jo pelaaja tai kordinaatit eivät ole käytössä.
	*
	*	\post Pelaaja on lisätty.
	*
	*	\return Osoite lisättyyn <code>Pelaaja</code>-luokkaan.
	*/
	Pelaaja * Data::lisaaPelaaja(Pelaaja data, Julkinen::Koordinaatti const&  kordinaatit);
	/**
	*	\brief Esineen lisääjä
	*
	*	Lisää annetun esineen peliin ja palauttaa sen osoitteen.
	*
	*	\param[in] data Lisättävä esine <code>Esine</code>-luokkana.
	*	\param[in] kordinaatit Lisättävän esineen kordinaatit <code>Julkinen::Koordinaatti</code>-luokkana.
	*
	*	\exception Alustusvirhe virheellinen sijainti.
	*	\exception Alustusvirhe palassa on jo esine.
	*	\exception Alustusvirhe pelaajaa ei löytynyt.
	*
	*	\post Esine on lisätty.
	*
	*	\return Osoite lisättyyn <code>Esine</code>-luokkaan.
	*/
	Esine * Data::lisaaEsine(Esine data, Julkinen::Koordinaatti const& kordinaatit);
	/**
	*	\brief Palan lisääjä
	*
	*	Lisää annetun palan peliin ja palauttaa sen osoitteen.
	*
	*	\param[in] data Lisättävä pala <code>Pala</code>-luokkana.
	*	\param[in] kordinaatit Lisättävän palan kordinaatit <code>Julkinen::Koordinaatti</code>-luokkana.
	*
	*	\exception Alustusvirhe virheellinen sijainti.
	*	\exception Alustusvirhe virheellinen rotaatio.
	*
	*	\post Pala on lisätty.
	*
	*	\return Osoite lisättyyn <code>Pala</code>-luokkaan.
	*/
	Pala * Data::lisaaPala(Pala data, bool paivitaPala = false);
	/**
	*	\brief Iropalan lisääjä
	*
	*	Lisää tai päivittää annetun palan pelin irtopalaksi
	*
	*	\param[in] data Lisättävä irtopala <code>Pala</code>-luokkana.
	*
	*	\post Irtopala on lisätty
	*
	*	\return Osoite lisättyyn irtopalaan <code>Pala</code>-luokkana.
	*/
	Pala * Data::lisaaIrtopala(Pala data);

	/**
	*	\brief Pelaajan liikuttaja
	*
	*	Asettaa pelaajan palalta toiselle.
	*
	*	\param[in] nimi \c liikutettavan pelaajan nimi.
	*	\param[in] kordinaatit Kohde kordinaatit <code>Julkinen::Koordinaatti</code>-luokkana.
	*
	*	\exception Alustusvirhe pelaajaa ei löytynyt.
	*
	*	\pre Pelaaja on liikutettu, jos se on mahdollista ja siitä on ilmoitettu.
	*
	*	\return Palauttaa <code>true</code> jos liikutus onnistui.
	*		Palauttaa <code>false</code> jos liikutus epäonnistui.
	*/
	bool liikutaPelaajaa(std::string nimi, Julkinen::Koordinaatti const& kordinaatit);
	/**
	*	\brief Pelaajan seuraavan haettavan esineen sijainnin hakija
	*
	*	Hakee pelaajan seuraavan esineen sijainnin.
	*
	*	\param[in] pelaaja Valittu pelaaja <code>Pelaaja</code>-luokkana.
	*
	*	\pre Esineen sijainti on löytynyt
	*
	*	\return Esineen sijainti <code>Julkinen::Koordinaatti</code>-luokkana.
	*/
	Julkinen::Koordinaatti pelaajanSeuraavanEsineenSijainti(const Pelaaja pelaaja) const;

	
private:
	
	std::map<Julkinen::Koordinaatti, Pala> ruudut;
	Pala irtopala;
	std::map<std::string, Pelaaja> pelaajat;
	std::map<char, Esine> esineet;

};

#endif