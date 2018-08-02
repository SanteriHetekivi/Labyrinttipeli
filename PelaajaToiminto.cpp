#include "PelaajaToiminto.hpp"
#include <sstream>


PelaajaToiminto::PelaajaToiminto(Julkinen::Nayttorajapinta* naytto, Julkinen::Koordinaatti const& koko, Data * data) : PelinNaytto(naytto)
{
	ESIEHTO(naytto != NULL);
	ESIEHTO(data != NULL);

	this->_koko = koko;
	this->_data = data;
}


PelaajaToiminto::~PelaajaToiminto()
{
}

void PelaajaToiminto::asetaKoko(Julkinen::Koordinaatti const& koko)
{
	this->_koko = koko;
}

bool PelaajaToiminto::Tyonna(Julkinen::Reuna reuna, unsigned int paikka, unsigned int rotaatio, Pelaaja * pelaaja)
{
	ESIEHTO(pelaaja != NULL);
	unsigned const int MAX_Y = this->_koko.haeYkoordinaatti();
	unsigned const int MAX_X = this->_koko.haeXkoordinaatti();
	std::stringstream toiminto;
	toiminto << "tyonna";
	if (!pelaaja->onTyontanyt)
	{
		if (rotaatio >= 1 && rotaatio <= 4)
		{
			if (reuna != Julkinen::EIOLE)
			{
				if (paikka >= 1 && (
					((reuna == Julkinen::VASEN || reuna == Julkinen::OIKEA) && paikka <= MAX_Y) ||
					((reuna == Julkinen::ALA || reuna == Julkinen::YLA) && paikka <= MAX_X)
					))
				{
					Julkinen::Koordinaatti kordinaatti = Julkinen::Koordinaatti();
					Julkinen::Koordinaatti irtopala_kor = Julkinen::Koordinaatti();
					Pala pala = *this->_data->haeIrtopala();
					pala.rotaatio = rotaatio;
					toiminto << " " << rotaatio;
					switch (reuna)
					{
					case Julkinen::ALA:
						irtopala_kor = Julkinen::Koordinaatti(paikka, MAX_Y);
						for (unsigned int y = MAX_Y; y > 0; --y)
						{
							pala.sijainti = Julkinen::Koordinaatti(paikka, y);
							pala = LiikutaPalaa(pala);
						}
						toiminto << " a";
						break;
					case Julkinen::YLA:
						irtopala_kor = Julkinen::Koordinaatti(paikka, 1);
						for (unsigned int y = 1; y <= MAX_Y; ++y)
						{
							pala.sijainti = Julkinen::Koordinaatti(paikka, y);
							pala = LiikutaPalaa(pala);
						}
						toiminto << " y";
						break;
					case Julkinen::VASEN:
						irtopala_kor = Julkinen::Koordinaatti(1, paikka);
						for (unsigned int x = 1; x <= MAX_X; ++x)
						{
							pala.sijainti = Julkinen::Koordinaatti(x, paikka);
							pala = LiikutaPalaa(pala);
						}
						toiminto << " v";
						break;
					case Julkinen::OIKEA:
						irtopala_kor = Julkinen::Koordinaatti(MAX_X, paikka);
						for (unsigned int x = MAX_X; x > 0; --x)
						{
							pala.sijainti = Julkinen::Koordinaatti(x, paikka);
							pala = LiikutaPalaa(pala);
						}
						toiminto << " o";
						break;
					default:
						throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_IRTOPALAN_REUNA);
						break;
					}
					this->_data->lisaaIrtopala(pala);
					if (pala.pelaaja != NULL) this->_data->liikutaPelaajaa(pala.pelaaja->nimi, irtopala_kor);
					pelaaja->onTyontanyt = true;
					toiminto << " " << paikka;
					pelaaja->edellinentoiminto = toiminto.str();
				}
				else throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_IRTOPALAN_PAIKKA); //Virheellinen paikka
			}
			else throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_IRTOPALAN_REUNA); //Virheellinen reuna
		}
		else throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_IRTOPALAN_ROTAATIO); //Virheellinen rotattio
	}
	else throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_IRTOPALAA_ON_JO_TYONNETTY);
	return false;
}

bool PelaajaToiminto::Liiku(Julkinen::Suunta suunta, unsigned int maara, Pelaaja * pelaaja)
{
	ESIEHTO(pelaaja != NULL);
	Julkinen::Koordinaatti sijainti = this->_data->haePelaajanSijainti(*pelaaja);
	int y = sijainti.haeYkoordinaatti();
	int x = sijainti.haeXkoordinaatti();
	bool liiku = true;
	std::stringstream toiminto;
	toiminto << "liiku";
	if (!pelaaja->onTyontanyt && pelaaja->tyyppi != Julkinen::TIETOKONE) throw  Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_IRTOPALAA_EI_OLE_TYONNETTY);
	else if(pelaaja->onLiikkunut) throw  Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_PELAAJA_ON_JO_LIIKKUNUT);
	else
	{
		if (suunta == Julkinen::AUTOMAATTI)
		{
			this->suoritaAutomaattiLiike(x, y, pelaaja);
		}
		else if (suunta == Julkinen::PAIKALLAAN || maara == 0)
		{
			pelaaja->edellinentoiminto = "-";
			pelaaja->onLiikkunut = true;
		}
		else
		{
			for (unsigned int i = 1; i <= maara && liiku; ++i)
			{
				if (this->TarkistaLiike(x, y, suunta, MENOSSA))
				{
					switch (suunta)
					{
					case Julkinen::ALAS:
						++y;
						if(i == 1)toiminto << " a " << maara;
						break;
					case Julkinen::AUTOMAATTI:
						if (i == 1)this->suoritaAutomaattiLiike(x, y, pelaaja);
						break;
					case Julkinen::OIKEALLE:
						++x;
						if (i == 1)toiminto << " o " << maara;
						break;
					case Julkinen::VASEMMALLE:
						--x;
						if (i == 1)toiminto << " v " << maara;
						break;
					case Julkinen::YLOS:
						--y;
						if (i == 1)toiminto << " y " << maara;
						break;
					case Julkinen::PAIKALLAAN:
						if (i == 1)toiminto.str("-");
						break;
					default:
						throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_LIIKKEEN_SUUNTA);
						break;
					}
					liiku = this->TarkistaLiike(x, y, suunta, TULOSSA, (i == maara));
				}
				else liiku = false;
			}
			if (liiku)
			{
				pelaaja->edellinentoiminto = toiminto.str();
				this->suoritaRuutu(Julkinen::Koordinaatti(x, y), pelaaja);
				pelaaja->onLiikkunut = true;
				return true;
			}
			else throw  Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_EI_VOITU_LIIKKUA_ANNETTUA_MAARAA);
		}
	}
	return false;
	
}
bool PelaajaToiminto::TarkistaKordinaatit(int x, int y)
{
	const int X_MAX = this->_koko.haeXkoordinaatti();
	const int Y_MAX = this->_koko.haeYkoordinaatti();
	bool canMove = false;

	if (y > 0 && x > 0 && y <= Y_MAX && x <= X_MAX)
	{
		canMove = true;
	}
	
	return canMove;
}

bool PelaajaToiminto::TarkistaLiike(int x, int y, Julkinen::Suunta suunta, Liike liike, bool viimeinenLiike)
{
	bool canMove = false;

	if (this->TarkistaKordinaatit(x, y))
	{
		Julkinen::Koordinaatti kordinaatit(x, y);
		if (this->tarkistaRuutu(kordinaatit, suunta, liike))
		{
			if (liike == MENOSSA || !viimeinenLiike || this->onkoRuutuVapaa(kordinaatit))
			{
				canMove = true;
			}
		}
	}
	return canMove;
}

bool PelaajaToiminto::tarkistaRuutu(Julkinen::Koordinaatti const & kordinaatti, Julkinen::Suunta suunta, Liike liike)
{
	bool canMove = false;

	Pala * pala = this->_data->haePala(kordinaatti);
	if (pala != NULL)
	{
		Julkinen::PalaTyyppi p = pala->pala;
		int r = pala->rotaatio;
		if (liike == TULOSSA)
		{
			if (suunta == Julkinen::ALAS) suunta = Julkinen::YLOS;
			else if (suunta == Julkinen::YLOS) suunta = Julkinen::ALAS;
			else if (suunta == Julkinen::OIKEALLE) suunta = Julkinen::VASEMMALLE;
			else if (suunta == Julkinen::VASEMMALLE) suunta = Julkinen::OIKEALLE;
		}
		
		if (p == Julkinen::IPALA)
		{
			if (suunta == Julkinen::ALAS || suunta == Julkinen::YLOS)
				canMove = (r == 1 || r == 3);
			else if (suunta == Julkinen::VASEMMALLE || suunta == Julkinen::OIKEALLE) 
				canMove = (r == 2 || r == 4);
			else canMove = false;
		}
		else if (p == Julkinen::LPALA)
		{
			if (suunta == Julkinen::ALAS)
				canMove = (r == 2 || r == 3);
			else if (suunta == Julkinen::YLOS)
				canMove = (r == 1 || r == 4);
			else if (suunta == Julkinen::VASEMMALLE)
				canMove = (r == 3 || r == 4);
			else if (suunta == Julkinen::OIKEALLE)
				canMove = (r == 1 || r == 2);
			else canMove = false;
		}
		else if (p == Julkinen::TPALA)
		{
			if (suunta == Julkinen::ALAS)
				canMove = (r == 1 || r == 2 || r == 4);
			else if (suunta == Julkinen::YLOS)
				canMove = (r == 2 || r == 3 || r == 4);
			else if (suunta == Julkinen::VASEMMALLE)
				canMove = (r == 1 || r == 2 || r == 3);
			else if (suunta == Julkinen::OIKEALLE)
				canMove = (r == 1 || r == 3 || r == 4);
			else canMove = false;
		}
	}
	
	return canMove;
}

bool PelaajaToiminto::onkoRuutuVapaa(Julkinen::Koordinaatti const & kordinaatti)
{
	Pelaaja * pelaaja = this->_data->haePelaaja(kordinaatti);
	return (pelaaja == NULL);
}

void PelaajaToiminto::suoritaRuutu(Julkinen::Koordinaatti const & kordinaatti, Pelaaja * pelaaja)
{
	ESIEHTO(pelaaja != NULL);
	Pala * pala = this->_data->haePala(kordinaatti);
	if (this->_data->liikutaPelaajaa(pelaaja->nimi, kordinaatti))
	{

		if (pala->keraaEsine()) this->ilmoitusEsinePoimittu(*pelaaja->keratytEsineet.back());
		switch (pala->tyyppi)
		{
		case Julkinen::NORMAALI:
			break;
		case Julkinen::TELEPORTTI:
			if (!pala->kohde.onkoIrtopala() && this->onkoRuutuVapaa(pala->kohde))
			{
				this->ilmoitusErikoispalaanAstuttu(*pala, *pelaaja);
				this->suoritaRuutu(pala->kohde, pelaaja);
			}
			break;
		case Julkinen::SIUNATTU:
			this->ilmoitusErikoispalaanAstuttu(*pala, *pelaaja);
			pelaaja->extraVuoro = true;
			break;
		case Julkinen::KIROTTU:
			this->ilmoitusErikoispalaanAstuttu(*pala, *pelaaja);
			pelaaja->menetaVuoro = true;
			break;
		default:
			break;
		}
	}
	else {} //Pelaajan liikutus epäonnistui
}

void PelaajaToiminto::suoritaAutomaattiLiike(int x, int y, Pelaaja * pelaaja)
{
	ESIEHTO(pelaaja != NULL);
	if (pelaaja != NULL)
	{
		const int X_START = x;
		const int Y_START = y;

		Julkinen::Suunta suunta = Julkinen::PAIKALLAAN;
		std::queue<Julkinen::Suunta> tmpSuunnat = std::queue<Julkinen::Suunta>();

		int maara = 1;

		int xEro = 0;
		int yEro = 0;
		int maxMaara = 0;

		bool meno = false;
		bool tulo = false;

		Julkinen::Suunta xSuunta = Julkinen::PAIKALLAAN;
		Julkinen::Suunta ySuunta = Julkinen::PAIKALLAAN;

		Julkinen::Suunta tmpSuunta = Julkinen::PAIKALLAAN;
	
		Julkinen::Koordinaatti esine = this->_data->pelaajanSeuraavanEsineenSijainti(*pelaaja);
		if (!esine.onkoIrtopala())
		{
			xEro = esine.haeXkoordinaatti() - X_START;
			yEro = esine.haeYkoordinaatti() - Y_START;

			if (xEro > 0)  xSuunta = Julkinen::OIKEALLE;
			else xSuunta = Julkinen::VASEMMALLE;
			if (yEro > 0)  ySuunta = Julkinen::ALAS;
			else ySuunta = Julkinen::YLOS;

			xEro = abs(xEro);
			yEro = abs(yEro);

			if (xEro >= yEro)
			{
				tmpSuunnat.push(xSuunta);
				tmpSuunnat.push(ySuunta);
			}
			else
			{
				tmpSuunnat.push(ySuunta);
				tmpSuunnat.push(xSuunta);
			}

			do
			{
				y = Y_START;
				x = X_START;
				if (!tmpSuunnat.empty())
				{
					suunta = tmpSuunnat.front();

					liikutaXY(&x, &y, suunta);

					if (suunta == Julkinen::ALAS || suunta == Julkinen::YLOS) maxMaara = yEro;
					else if (suunta == Julkinen::OIKEALLE || suunta == Julkinen::VASEMMALLE) maxMaara = xEro;

					meno = this->TarkistaLiike(X_START, Y_START, suunta, MENOSSA);
					tulo = this->TarkistaLiike(x, y, suunta, TULOSSA, (maxMaara == 1));
					tmpSuunnat.pop();
					
				}
			} while (!(meno && tulo) && !tmpSuunnat.empty());
		}

		if (!meno || !tulo || esine.onkoIrtopala() || maxMaara == 0)
		{
			suunta = Julkinen::PAIKALLAAN;
			maara = 0;
		}
		else
		{
			maara = 1;
			int yStop = y;
			int xStop = x;

			while (meno && tulo && maara < maxMaara)
			{
				x = xStop;
				y = yStop;
				liikutaXY(&xStop, &yStop, suunta);
				meno = this->TarkistaLiike(x, y, suunta, MENOSSA);
				tulo = this->TarkistaLiike(xStop, yStop, suunta, TULOSSA, false);
				if (meno && tulo) ++maara;
			}
			while(!this->TarkistaLiike(x, y, suunta, TULOSSA, true) && maara > 0)
			{
				if (suunta == Julkinen::ALAS) --y;
				else if (suunta == Julkinen::YLOS) ++y;
				else if (suunta == Julkinen::OIKEALLE) --x;
				else if (suunta == Julkinen::VASEMMALLE) ++x;
				--maara;
			}
			if (maara <= 0)
			{
				suunta = Julkinen::PAIKALLAAN;
				maara = 0;
			}
		}
		this->Liiku(suunta, maara, pelaaja);
	}
}

Pala PelaajaToiminto::LiikutaPalaa(Pala pala)
{
	Pala result = Pala();
	Pala * tmp = this->_data->haePala(pala.sijainti);
	if (tmp != NULL)
	{
		result = *tmp;
		this->_data->lisaaPala(pala, true);
	}
	return result;

}

void PelaajaToiminto::liikutaXY(int * x, int * y, const Julkinen::Suunta suunta)
{
	ESIEHTO(x != NULL);
	ESIEHTO(y != NULL);
	if (suunta == Julkinen::ALAS) ++(*y);
	else if (suunta == Julkinen::YLOS) --(*y);
	else if (suunta == Julkinen::OIKEALLE) ++(*x);
	else if (suunta == Julkinen::VASEMMALLE) --(*x);
}
