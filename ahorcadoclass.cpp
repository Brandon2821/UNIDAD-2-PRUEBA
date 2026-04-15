#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Ahorcado {
private:
    string palabraSecreta;
    string palabraMostrada;
    vector<char> letrasUsadas;
    int intentosRestantes;
    int puntaje;
public:
    Ahorcado(string palabra) {
        palabraSecreta = palabra;
        palabraMostrada = "";

        for (size_t i = 0; i < palabraSecreta.length(); i++) {
            if (palabraSecreta[i] == ' ') {
                palabraMostrada += ' ';
            } else {
                palabraMostrada += '_';
            }
        }

        intentosRestantes = 6;
        puntaje = 0;
    }
     bool letraYaUsada(char letra) {
        letra = toupper(letra);

        for (size_t i = 0; i < letrasUsadas.size(); i++) {
            if (letrasUsadas[i] == letra) {
                return true;
            }
        }
        return false;
    }
 bool intentarLetra(char letra) {
        letra = toupper(letra);

        if (letraYaUsada(letra)) {
            cout << "La letra ya fue usada.\n";
            return false;
        }

        letrasUsadas.push_back(letra);

        bool acierto = false;

        for (size_t i = 0; i < palabraSecreta.length(); i++) {
            if (toupper(palabraSecreta[i]) == letra) {
                palabraMostrada[i] = palabraSecreta[i];
                acierto = true;
            }
        }

        if (acierto) {
            puntaje += 10;
            cout << "Letra correcta.\n";
        } else {
            intentosRestantes--;
            cout << "Letra incorrecta.\n";
        }
     return acierto;
    }

    bool gano() {
        return palabraMostrada == palabraSecreta;
    }

    bool perdio() {
        return intentosRestantes <= 0;
    }

    void mostrarEstado() {
        cout << "\nPalabra: ";
        for (size_t i = 0; i < palabraMostrada.length(); i++) {
            cout << palabraMostrada[i] << " ";
        }

        cout << "\nLetras usadas: ";
        for (size_t i = 0; i < letrasUsadas.size(); i++) {
            cout << letrasUsadas[i] << " ";
        }

        cout << "\nIntentos restantes: " << intentosRestantes;
        cout << "\nPuntaje: " << puntaje << endl;
    }

    string getPalabraSecreta() {
        return palabraSecreta;
    }

    int getIntentosRestantes() {
        return intentosRestantes;
    }

    int getPuntaje() {
        return puntaje;
    }
};

int main() {
    string palabra;
    char letra;

    cout << "Ingrese la palabra secreta: ";
    getline(cin, palabra);

    Ahorcado juego(palabra);

    while (!juego.gano() && !juego.perdio()) {
        juego.mostrarEstado();
        cout << "\nIngrese una letra: ";
        cin >> letra;

        if (isalpha(letra)) {
            juego.intentarLetra(letra);
        } else {
            cout << "Debe ingresar una letra valida.\n";
        }
    }

    juego.mostrarEstado();

    if (juego.gano()) {
        cout << "\nGanaste. Puntaje final: " << juego.getPuntaje() << endl;
    } else {
        cout << "\nPerdiste. La palabra era: " << juego.getPalabraSecreta() << endl;
    }

    return 0;
}

