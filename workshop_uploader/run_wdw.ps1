# Installer les dépendances nécessaires
choco install -y qt6 libgit2 cmake ninja

# Nettoyer l'ancien build
if (Test-Path build) { Remove-Item -Recurse -Force build }
New-Item -ItemType Directory -Path build | Out-Null
Set-Location build

# Génération du projet avec CMake + Ninja
cmake .. -G "Ninja" -DCMAKE_BUILD_TYPE=Release

# Compilation
cmake --build . --config Release

# Exécution (si le binaire a bien été généré)
if (Test-Path ".\WorkshopUploader.exe") {
    Write-Host "Lancement de l'application..."
    .\WorkshopUploader.exe "/////"
} else {
    Write-Host "Erreur : WorkshopUploader.exe introuvable dans le dossier Release."
}
