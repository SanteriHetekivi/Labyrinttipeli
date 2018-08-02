#include "Esine.hpp"

Esine::Esine()
{
	this->merkki = ' ';
	this->pelaaja = "";
}

Esine::Esine(char merkki, std::string pelaaja)
{
	this->merkki = merkki;
	this->pelaaja = pelaaja;
}


Esine::~Esine()
{
}
