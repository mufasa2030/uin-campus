#include <exception>
#include <iostream>
#include <string>
#include <utility>

class Traceur {
public:
    explicit Traceur(std::string nom) : nom_(std::move(nom)) {
        std::cout << "+ construction de " << nom_ << '\n';
    }

    ~Traceur() {
        std::cout << "- destruction de " << nom_ << '\n';
    }

    Traceur(const Traceur& autre) : nom_(autre.nom_) {
        std::cout << "* copie de " << nom_ << '\n';
    }

    Traceur& operator=(const Traceur& autre) {
        if (this != &autre) {
            nom_ = autre.nom_;
            std::cout << "* affectation par copie de " << nom_ << '\n';
        }
        return *this;
    }

    Traceur(Traceur&& autre) noexcept : nom_(std::move(autre.nom_)) {
        std::cout << "-> deplacement de " << nom_ << '\n';
    }

    Traceur& operator=(Traceur&& autre) noexcept {
        if (this != &autre) {
            nom_ = std::move(autre.nom_);
            std::cout << "-> affectation par deplacement de " << nom_ << '\n';
        }
        return *this;
    }

    const std::string& nom() const noexcept {
        return nom_;
    }

private:
    std::string nom_;
};

class Fragile {
public:
    explicit Fragile(std::string nom) : trace_(std::move(nom)) {
        throw std::runtime_error("echec pendant la construction de " + trace_.nom());
    }

    ~Fragile() {
        std::cout << "corps du destructeur de Fragile\n";
    }

private:
    Traceur trace_;
};

int main() {
    try {
        Traceur a("A");
        Traceur b = a;
        Traceur c("C");
        c = b;
        Traceur d = std::move(a);
        c = std::move(d);

        Fragile f("objet_fragile");
    } catch (const std::exception& e) {
        std::cerr << "exception : " << e.what() << '\n';
    }

    std::cout << "fin de main\n";
    return 0;
}