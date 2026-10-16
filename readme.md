# Magic Checker

Prosty program w C++, który rozpoznaje format pliku na podstawie jego sygnatury, czyli kilku pierwszych bajtów.

## Rozpoznawane formaty

- PNG
- JPEG
- GIF
- PDF
- ZIP
- GZIP
- ELF
- BMP
- EXE/DLL

## Kompilacja

Wymagany jest kompilator C++ obsługujący standard C++11, na przykład `g++`:

```sh
g++ -std=c++11 main.cpp signature_detector.cpp -o magicChecker
```

## Użycie

Podaj ścieżkę do pliku jako argument:

```sh
./magicChecker plik.png
```

Na Windows:

```powershell
.\magicChecker.exe plik.png
```

Program wyświetli rozpoznany format albo informację, że sygnatura nie została rozpoznana. Dla plików EXE/DLL może też ostrzec, gdy ich rozszerzenie jest nietypowe. Ostrzeżenie nie potwierdza obfuskacji ani złośliwości pliku.
