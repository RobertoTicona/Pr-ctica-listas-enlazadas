#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib> 


using namespace std;

// Definici�n de la estructura del nodo
struct Player {
    int id;
    string name;
    int score;
    Player* next;
};

// Funci�n para crear un nuevo nodo
Player* createNode(int id, string name, int score) {
    Player* newNode = new Player();
    newNode->id = id;
    newNode->name = name;
    newNode->score = score;
    newNode->next = NULL;
    return newNode;
}

// Funci�n para agregar un nodo al final de la lista
void appendNode(Player*& head, int id, string name, int score) {
    Player* newNode = createNode(id, name, score);
    if (head == NULL) {
        head = newNode;
        return;
    }
    Player* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Funci�n para calcular la puntuaci�n promedio
double calculateAverage(Player* head) {
    double sum = 0;
    int count = 0;
    Player* temp = head;
    while (temp != NULL) {
        sum += temp->score;
        count++;
        temp = temp->next;
    }
    return (count == 0) ? 0 : sum / count;
}

// Funci�n para encontrar al jugador con la puntuaci�n m�s alta
Player* findHighestScore(Player* head) {
    Player* highest = head;
    Player* temp = head;
    while (temp != NULL) {
        if (temp->score > highest->score) {
            highest = temp;
        }
        temp = temp->next;
    }
    return highest;
}

// Funci�n para encontrar al jugador con la puntuaci�n m�s baja
Player* findLowestScore(Player* head) {
    Player* lowest = head;
    Player* temp = head;
    while (temp != NULL) {
        if (temp->score < lowest->score) {
            lowest = temp;
        }
        temp = temp->next;
    }
    return lowest;
}

// Funci�n para eliminar jugadores con puntuaciones por debajo del promedio
void removeBelowAverage(Player*& head, double average) {
    Player* temp = head;
    Player* prev = NULL;
    while (temp != NULL) {
        if (temp->score < average) {
            if (prev != NULL) {
                prev->next = temp->next;
            } else {
                head = temp->next;
            }
            Player* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
}

// Funci�n principal
int main() {
    Player* head = NULL;
    ifstream inputFile("jugadores.txt");
    string line;

    // Leer datos desde el archivo
    while (getline(inputFile, line)) {
        int id, score;
        string name;
        size_t firstSpace = line.find(' ');
        size_t lastSpace = line.rfind(' ');

        id = atoi(line.substr(0, firstSpace).c_str());
        name = line.substr(firstSpace + 1, lastSpace - firstSpace - 1);
        score = atoi(line.substr(lastSpace + 1).c_str());

        appendNode(head, id, name, score);
    }
    inputFile.close();

    // Calcular la puntuaci�n promedio
    double average = calculateAverage(head);
    cout << "Puntuacion Promedio: " << average << endl;

    // Encontrar al jugador con la puntuaci�n m�s alta y m�s baja
    Player* highest = findHighestScore(head);
    Player* lowest = findLowestScore(head);

    cout << "Mayor Puntuacion: JugadorID=" << highest->id << ", Nombre de jugador=" << highest->name
         << ", Score=" << highest->score << endl;
    cout << "Menor Puntuacion: JugadorID=" << lowest->id << ", Nombre de jugador=" << lowest->name
         << ", Score=" << lowest->score << endl;

    // Medir tiempo para eliminar jugadores por debajo del promedio
    clock_t start = clock();
    removeBelowAverage(head, average);
    clock_t end = clock();

    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    cout << "Tiempo para eliminar jugadores por debajo del promedio: " << elapsed << " segundos" << endl;

    return 0;
}
