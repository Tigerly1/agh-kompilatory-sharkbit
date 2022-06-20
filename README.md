# 1. SharkBit

## 2, 3. Autorzy:

- Filip Pilarek filippilarek@student.agh.edu.pl
- Jan Fiszer fiszer@student.agh.edu.pl

## 4. Założenia języka SharkBit:

a, b: SharkBit to funkcyjny interpretowany język, który składniowo przypomina pomieszanego pythona z językiem C.
  
 
  
c: Celem programu jest prostsze oraz skuteczniejsze analizowanie działających procesów. Wszystko co znajdziemy w procesie podlega naszej ingerencji. 
  
d: Planowanym językiem implementacji jest C++.

## 5. Tokeny:
  [opis tokenów](https://github.com/Tigerly1/agh-kompilatory-sharkbit/blob/master/tokens.md)
## 6. Gramatyka:
  [opis gramatyki](https://github.com/Tigerly1/agh-kompilatory-sharkbit/blob/master/grammar.md)
## 7. Struktura Programu:

  Program składa się ze skanera oraz parsera wygenerowanych w antlerze przy pomocy naszej gramatyki. Kod wraz z klasami generowany jest w Tree Listenerze w pliku MyListener.cpp. Do klas obsługujących matematykę, zapisywanie zmiennych, obsługę ifów są również dołączone wpisane funkcje.
  
## 8. Informacje o stosowanych narzędziach i technologiach:
  Wszystko zostało napisane przy użyciu anltr 4.10 oraz C++17, używamy zaimplementowanych bibliotek niskiego poziomu do przechwytywania procesów oraz prostszych bibliotek do obsługi zmiennych

## 9. Informacje o zastosowanych metodach i algorytmach:
  W listenerze korzystamy głównie z trzech klas:
  
    VariableContainer --Przechowuje ona zmienne wraz z wartościami oraz typami danych
    Math  --Wykonuje działania arytmetyczne na liczbach, tak samo jak na zmiennych
    Functions  --Przechowuje zadeklarowane funkcje takie jak: writeMemory, scanMemory oraz findMemory
  
## 10. Krótka instrukcja obsługi:

  1. Należy pobrać zawartość
  2. Uruchomić projekt w Visual Studio 2019
  3. Uruchomić CMakeList
  4. Uruchomić sharkbit.cpp
  
  W pliku sharkbit.sb możemy pisać kod, którzy będzie później odtwarzany przez zaimplementowany Listener

## 11. Testy i przykłady:
   [Przykłady](https://github.com/Tigerly1/agh-kompilatory-sharkbit/blob/master/example_code_1.md)

## 12. Możliwe rozszerzenia programu:
  Program można rozserzyć o dodatkowe implementacje działania na bitach, procesach. Można także spróbować napisać nowe wbudowane funkcje do obsługii owych procesów
   

