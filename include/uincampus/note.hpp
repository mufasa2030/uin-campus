#pragma once

#include "uincampus/regles.hpp"

namespace uin {

/// Note sur 20.
/// Invariant : noteMin <= valeur() <= noteMax.
/// Objet valeur immuable : pour changer une note, on la remplace.
class Note {
public:
    /// @throws std::invalid_argument si la valeur est hors de [noteMin; noteMax]
    explicit Note(double valeur);

    [[nodiscard]] double valeur() const { return valeur_; }
    [[nodiscard]] bool estValidante() const { return valeur_ >= seuilValidation; }
    [[nodiscard]] Mention mention() const { return mentionPour(valeur_); }

private:
    double valeur_;
};

}