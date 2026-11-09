#include "uincampus/regles.hpp"
#include "uincampus/saisie.hpp"
#include "uincampus/version.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <format>
#include <iostream>
#include <print>
#include <string>
#include <vector>

int main()
{
    std::println("UIN-Campus {} - TP3 : Statistiques d'une série de notes\n", uin::version());

    std::cout << "Nom de l'UE : ";
    std::string ue;
    std::getline(std::cin, ue);

    const int nb = uin::lireEntier("Nombre d'étudiants (1 à 200) : ", 1, 200);

    std::vector<double> notes;
    for (int i{1}; i <= nb; ++i) {
        notes.push_back(uin::lireNote(std::format("Note de l'étudiant {} : ", i)));
    }

    constexpr std::size_t nbMentions{5};
    double minimum{uin::noteMax};
    double maximum{uin::noteMin};
    double somme{0.0};
    int admis{0};
    std::array<int, nbMentions> repartition{};

    for (double n : notes) {
        minimum = std::min(minimum, n);
        maximum = std::max(maximum, n);
        somme += n;
        if (n >= uin::seuilValidation) {
            ++admis;
        }
        ++repartition[static_cast<std::size_t>(uin::mentionPour(n))];
    }

    const double taille = static_cast<double>(notes.size());
    const double moyenne = somme / taille;

    double sommeEcarts{0.0};
    for (double n : notes) {
        sommeEcarts += (n - moyenne) * (n - moyenne);
    }
    const double ecartType = std::sqrt(sommeEcarts / taille);

    std::println("\nStatistiques : {} ({} étudiants)", ue, nb);
    std::println("{:-<58}", "");
    std::println("{:<18} : {:6.2f}", "Note minimale", minimum);
    std::println("{:<18} : {:6.2f}", "Note maximale", maximum);
    std::println("{:<18} : {:6.2f}", "Moyenne", moyenne);
    std::println("{:<18} : {:6.2f}", "Écart-type", ecartType);
    std::println("{:<18} : {} ({:.1f} %)", "Admis", admis, 100.0 * admis / taille);

    std::println("\nRépartition par mention");
    for (std::size_t i{0}; i < nbMentions; ++i) {
        const auto m = static_cast<uin::Mention>(i);
        std::println("{:<12} {} ({})", uin::libelle(m), std::string(static_cast<std::size_t>(repartition[i]), '*'), repartition[i]);
    }
    std::println("{:-<58}", "");
}