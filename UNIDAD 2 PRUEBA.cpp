#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>
using namespace std;

class LoteProduccion {
private:
    string codigo;
    string color;
    string talla;
    int cantidad;
    float precio;
    float humedad;

public:
    LoteProduccion(string c, string col, string t, int cant, float p, float h) {
        codigo = c;
        color = col;
        talla = t;
        cantidad = cant;
        precio = p;
        humedad = h;
    }

    float calcularMerma() {
        return cantidad * (humedad / 100);
    }

    void secar(int minutos) {
        if (minutos > 0) {
            humedad -= 0.8;
            if (humedad < 0) humedad = 0;
            secar(minutos - 1);
        }
    }

    void mostrar() {
        cout << "\nCodigo: " << codigo;
        cout << "\nColor: " << color;
        cout << "\nTalla: " << talla;
        cout << "\nCantidad: " << cantidad;
        cout << "\nPrecio: " << precio;
        cout << "\nHumedad: " << humedad;
        cout << "\nMerma: " << calcularMerma() << endl;
    }

    float getMerma() { return calcularMerma(); }
};

class SistemaTextil {
private:
    vector<LoteProduccion> lotes;

public:
    void registrar() {
        string c, col, t;
        int cant;
        float p, h;

        cout << "Codigo: "; cin >> c;
        cout << "Color: "; cin >> col;
        cout << "Talla: "; cin >> t;

        do {
            cout << "Cantidad (>0): ";
            cin >> cant;
        } while (cant <= 0);

        cout << "Precio: "; cin >> p;

        do {
            cout << "Humedad (0-100): ";
            cin >> h;
        } while (h < 0 || h > 100);

        lotes.push_back(LoteProduccion(c, col, t, cant, p, h));
    }

    void mostrar() {
        for (auto &l : lotes) {
            l.mostrar();
        }
    }

    void ordenar() {
        for (int i = 0; i < lotes.size(); i++) {
            for (int j = i + 1; j < lotes.size(); j++) {
                if (lotes[j].getMerma() > lotes[i].getMerma()) {
                    swap(lotes[i], lotes[j]);
                }
            }
        }
    }
};

bool repetida(string usadas, char l) {
    for (char c : usadas) {
        if (c == l) return true;
    }
    return false;
}

void jugarPartida(vector<string> palabras, int &ganadas, int &perdidas) {
    string palabra = palabras[rand() % palabras.size()];
    string progreso(palabra.length(), '_');
    string usadas = "";
    int intentos = 6;

    while (intentos > 0 && progreso != palabra) {
        cout << "\nPalabra: " << progreso;
        cout << "\nUsadas: " << usadas;
        cout << "\nIntentos: " << intentos;
        cout << "\nLetra: ";

        char l;
        cin >> l;
        l = toupper(l);

        if (!isalpha(l) || repetida(usadas, l)) {
            cout << "Entrada invalida\n";
            continue;
        }

        usadas += l;
        bool acierto = false;

        for (int i = 0; i < palabra.length(); i++) {
            if (palabra[i] == l) {
                progreso[i] = l;
                acierto = true;
            }
        }

        if (!acierto) intentos--;
    }

    if (progreso == palabra) {
        cout << "\nGanaste\n";
        ganadas++;
    } else {
        cout << "\nPerdiste. Era: " << palabra << endl;
        perdidas++;
    }
}

void menuAhorcado() {
    int op;
    int ganadas = 0, perdidas = 0;

    vector<string> facil = {"JEANS", "TELA"};
    vector<string> dificil = {"DENIM", "BOTONES"};

    do {
        cout << "\n=== AHORCADO ===";
        cout << "\n1. Jugar facil";
        cout << "\n2. Jugar dificil";
        cout << "\n3. Ver estadisticas";
        cout << "\n4. Volver";
        cout << "\nOpcion: ";
        cin >> op;

        switch (op) {
            case 1: jugarPartida(facil, ganadas, perdidas); break;
            case 2: jugarPartida(dificil, ganadas, perdidas); break;
            case 3:
                cout << "\nGanadas: " << ganadas;
                cout << "\nPerdidas: " << perdidas << endl;
                break;
        }

    } while (op != 4);
}

int main() {
    srand(time(0));
    SistemaTextil sistema;
    int op;

    do {
        cout << "\n=== SISTEMA TEXTIL ===";
        cout << "\n1. Registrar lote";
        cout << "\n2. Mostrar lotes";
        cout << "\n3. Ordenar por merma";
        cout << "\n4. Ahorcado";
        cout << "\n5. Salir";
        cout << "\nOpcion: ";
        cin >> op;

        switch (op) {
            case 1: sistema.registrar(); break;
            case 2: sistema.mostrar(); break;
            case 3: sistema.ordenar(); cout << "Ordenado\n"; break;
            case 4: menuAhorcado(); break;
        }

    } while (op != 5);

    return 0;
}
