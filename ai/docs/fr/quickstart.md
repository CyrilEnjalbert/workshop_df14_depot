# Premiers pas avec PROOVme
![Logo](assets/logo_proovme.png)


```mermaid
flowchart TD
    A[Bienvenue] --> B{Avez-vous un compte ?}
    B -- Oui --> C[Connectez-vous]
    B -- Non --> D[Faite la demande à l'Administrateur]
    C --> E[Accédez à l'application]
    D --> E
    E --> F{Avez-vous besoin d'aide ?}
    F -- Oui --> G[Consultez la documentation]
    F -- Non --> H[Commencez à utiliser PROOVme]
    G --> H
    H --> I[Faites-nous part de vos commentaires]
    I --> J[Bonne utilisation]
```