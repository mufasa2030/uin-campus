#include "uincampus/carte_campus.hpp"

#include <stdexcept>
#include <utility>

namespace uin {

CarteCampus::CarteCampus(std::string numero, std::string matricule)
    : numero_{std::move(numero)}, matricule_{std::move(matricule)} {
    if (numero_.empty() || matricule_.empty()) {
        throw std::invalid_argument("CarteCampus : numero et matricule obligatoires");
    }
}

void CarteCampus::verifierOperationPossible(std::int64_t montant) const {
    if (montant <= 0) {
        throw std::invalid_argument("CarteCampus : le montant doit etre strictement positif");
    }
    if (bloquee_) {
        throw std::logic_error("CarteCampus : la carte est bloquee");
    }
}

void CarteCampus::recharger(std::int64_t montant) {
    verifierOperationPossible(montant);
    solde_ += montant;
    historique_.push_back(Operation{TypeOperation::Recharge, montant, "Recharge", solde_});
}

bool CarteCampus::payer(std::int64_t montant, std::string_view libelle) {
    verifierOperationPossible(montant);
    if (montant > solde_) {
        return false; // refus normal : aucun changement d'état
    }
    solde_ -= montant;
    historique_.push_back(
        Operation{TypeOperation::Paiement, montant, std::string{libelle}, solde_});
    return true;
}

} // namespace uin