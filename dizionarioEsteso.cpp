#include <iostream>
#include <string>
#include <optional>

template <typename T>
class DizionarioEsteso {
private:
    static const int TABLE_SIZE = 10; // Dimensione della tabella hash
    struct Entry {
        std::string key; 
        T value;        
        bool isOccupied = false; 
        bool isDeleted = false;  
    };

    Entry table[TABLE_SIZE]; 

  
    int hashFunction(const std::string& key) const {
        int hash = 0;
        for (char ch : key) {
            hash = (hash * 31 + ch) % TABLE_SIZE; 
        }
        return hash;
    }

    int findSlot(const std::string& key) const {
        int index = hashFunction(key);
        
        while (table[index].isOccupied && !table[index].isDeleted && table[index].key != key) {
            index = (index + 1) % TABLE_SIZE; // Prova il prossimo slot
        }
        return index;
    }

public:
    void inserisci(const std::string& key, const T& value) {
        int index = findSlot(key);
        table[index].key = key;
        table[index].value = value;
        table[index].isOccupied = true;
        table[index].isDeleted = false;
    }

    std::optional<T> recupera(const std::string& key) const {
        int index = findSlot(key);
        
        if (table[index].isOccupied && !table[index].isDeleted && table[index].key == key) {
            return table[index].value;
        }
        return std::nullopt; 
    }

    void cancella(const std::string& key) {
        int index = findSlot(key);

        if (table[index].isOccupied && !table[index].isDeleted && table[index].key == key) {
            table[index].isDeleted = true;  
            std::cout << "Chiave '" << key << "' rimossa con successo.\n";
        } else {
            std::cout << "Chiave '" << key << "' non trovata per la rimozione.\n";
        }
    }

    bool appartiene(const std::string& key) const {
        int index = findSlot(key);
        return table[index].isOccupied && !table[index].isDeleted && table[index].key == key;
    }

    void stampa() const {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (table[i].isOccupied && !table[i].isDeleted) {
                std::cout << "Index " << i << ": " << table[i].key << " => " << table[i].value << "\n";
            }
        }
    }
};

int main() {
    DizionarioEsteso<int> dizionario;

    std::cout << "Inserimento delle coppie chiave-valore:\n";
    dizionario.inserisci("apple", 10); 
    dizionario.inserisci("banana", 20); 
    dizionario.inserisci("cherry", 30); 
    dizionario.inserisci("fig", 40); 
    dizionario.inserisci("grape", 50); 

    std::cout << "\nContenuto del dizionario:\n";
    dizionario.stampa();

    std::cout << "\nVerifica se 'banana' appartiene al dizionario: " 
              << (dizionario.appartiene("banana") ? "Sì" : "No") << std::endl;
    std::cout << "Verifica se 'orange' appartiene al dizionario: "
              << (dizionario.appartiene("orange") ? "Sì" : "No") << std::endl;

    std::cout << "\nRecupero del valore per 'banana':\n";
    if (auto val = dizionario.recupera("banana")) {
        std::cout << "Valore per 'banana': " << *val << std::endl;
    } else {
        std::cout << "Chiave 'banana' non trovata.\n";
    }

    std::cout << "\nRimozione della chiave 'banana':\n";
    dizionario.cancella("banana");

    std::cout << "\nTentativo di rimuovere la chiave 'orange':\n";
    dizionario.cancella("orange");

    std::cout << "\nContenuto del dizionario dopo le rimozioni:\n";
    dizionario.stampa();

    std::cout << "\nVerifica se 'banana' appartiene al dizionario dopo la rimozione: " 
              << (dizionario.appartiene("banana") ? "Sì" : "No") << std::endl;

    return 0;
}
