#include "uincampus/note.hpp"

#include <cmath>
#include <stdexcept>

namespace uin {

Note::Note(double valeur) : valeur_(valeur) {
    if (!std::isfinite(valeur_) || valeur_ < noteMin || valeur_ > noteMax) {
        throw std::invalid_argument("Note hors de l'intervalle autorise");
    }
}

} // namespace uin