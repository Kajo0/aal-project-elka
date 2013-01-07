Autor:		Mikolaj Markiewicz
Przedmiot:	AAL


Problem:	Maksymalizacja sumarycznego wykorzystania sal wykladowych
		przez akceptacje jednych i odrzucenie innych wykladow.
		Porownanie czasu i wynikow obliczen roznych metod.


Poprawne wywolanie programu:
	./aal -d plik
	./aal -d < plik
	./aal -g rozmiar_problemu
	./aal -t rozmiar_problemu_od rozmiar_problemu_do algorytm [ilosc_probek_na_rozmiar_problemu]

	, gdzie:
		algorytm : {1,2,3,4}
		-d : pomiar czasu i wynik na podstawie danych wejsciowych
		-g : pomiar czasu i wynik dla wygenerowanego problemu o zadanym rozmiarze
		-t : pomiar czasow i porownanie wynikow dla zadanego przedzialu rozmiaru problemu oraz wybranego do tego algorytmu


Format pliku danych wejsciowych:	Kolejnosc linii dowolna,
					nazwy odpowiendnich id inne,
					odstepy jako spacje,
					brak spacji na poczatku i koncu linii,
					brak znaku nowej linii na koncu pliku:

{nazwa_sali}
{nazwa_sali_1}
...
{dzien/1..5/} {godzina_od} {godzina_do} [{nazwa_wykladu}]
...


Prezentacja wynikow:	Przy wyborze opcji -d | -g
			Wynik dzialania algorytmu x zapisany do pliku
			o nazwie result_{x}.html
			Prezentowane sa w postaci tabel planu wypelnienia
			poszczegolnych sal przez przyporzadkowane wyklady.


Opis algorytmow:
	1. Algorytm programowania dynamicznego, szybkie dzialanie,
		w wiekszosci przypadkow wyniki bliskie optymalnym.
	2. Algorytm zachlanny, najszybsze dzialanie,
		najwieksza ilosc wykladow przyporzadkowana, przecietne wyniki.
	3. Metoda Brute Force, sprawdzenie wszystkich mozliwych kombinacji,
		nawet dla malych instancji problemu brak wynikow w rozsadnym
		czasie, dla bardzo malych instancji optymalny wynik.
	4. Polaczenie algorytmow, wybor nakladajacych sie wykladow i wykonanie
		dla nich jednego z ww. algorytmow, wyniki zblizone do algorytmu
		pierwszego w krotszym czasie.


Struktury danych:
	Zastosowane struktury m.in.: std::list, std::vector, std::map


Dekompozycja funkcjonalna programu:
	Classroom	- przechowujaca przyporzadkowane wyklady
	Order		- przechowujaca zamowienia
	Generator	- generujaca problemy zadanych wielkosci
	Reader		- czytajaca dane z zadanego strumienia
	Model		- zbierajaca dane do obliczen (sale, zamowienia)
	FirstAlgorithm	- wykonujaca algorytm 1
	SecondAlgorithm	- wykonujaca algorytm 2
	ThirdAlgorithm	- wykonujaca algorytm 3
	FourthAlgorithm	- wykonujaca algorytm 4
	Result		- przechowujaca liste sal z przyporzadkowanymi wykladami
	Timer		- do liczenia czasu


Informacje dodatkowe:
	Program przewidziany jest dla 5 dni wykladowych
	Rozmiar problemu n = n * 10 wykladow + n / 10 sal (n < 10 => 1 sala)
	Dla metody Brute Force maksymalny rozmiar problemu = 2,
		dajacy od ~3 do ~15 sekund obliczen
	Klasa Timer'a zrealizowana jako Singleton
