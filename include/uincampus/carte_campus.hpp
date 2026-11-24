#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace uin {

enum class TypeOperation { Recharge, Paiement };

/// Une ligne de l'historique : regroupement passif de données.
struct Operation {
    TypeOperation type;
    std::int64_t montant;
    std::string libelle;
    std::int64_t soldeApres;
};

/// Carte de campus prépayée (solde en francs CFA, entier >= 0).
class CarteCampus {
public:
    /// @throws std::invalid_argument si le numéro ou le matricule est vide
    CarteCampus(std::string numero, std::string matricule);

    [[nodiscard]] const std::string& numero() const { return numero_; }
    [[nodiscard]] const std::string& matricule() const { return matricule_; }
    [[nodiscard]] std::int64_t solde() const { return solde_; }
    [[nodiscard]] bool estBloquee() const { return bloquee_; }
    [[nodiscard]] const std::vector<Operation>& historique() const { return historique_; }

    /// @throws std::invalid_argument si montant <= 0
    /// @throws std::logic_error si la carte est bloquée
    void recharger(std::int64_t montant);

    /// Renvoie false si le solde est insuffisant.
    /// @throws std::invalid_argument si montant <= 0
    /// @throws std::logic_error si la carte est bloquée
    [[nodiscard]] bool payer(std::int64_t montant, std::string_view libelle);

    void bloquer() { bloquee_ = true; }
    void debloquer() { bloquee_ = false; }

private:
    void verifierOperationPossible(std::int64_t montant) const;

    std::string numero_;
    std::string matricule_;
    std::int64_t solde_{0};
    bool bloquee_{false};
    std::vector<Operation> historique_;
};

} // namespace uin