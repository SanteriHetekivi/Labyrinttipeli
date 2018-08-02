#include "pelitehdas.hh"
#include "Peli.hpp"

/**
*  \brief Luo instanssi pelirajapinnasta.
*
*  P‰‰ohjelma kutsuu t‰t‰ funktiota saadakseen itselleen instanssin
*  oliosta, joka toteuttaa pelirajapinnan.
*  Funktion toteutus on teht‰v‰ omaan koodiin.
*
*  \post Luodun peli-instanssin tuhoamisvastuu siirtyi p‰‰ohjelmalle.
*      Luotu olio on alustustilassa.
*  \return Dynaamisesti luotu instanssi luokasta, joka toteuttaa
*      Labyrintti-pelin.
*/
namespace
	Julkinen
{
	std::unique_ptr<Pelirajapinta> luoPeli()
	{
		std::unique_ptr<Pelirajapinta> peli(new Peli());
		return peli;
	}
}