#!/bin/bash

# Nom de l'image Docker
IMAGE_NAME="battle_bot"

# Chemin du Dockerfile (ajustez si nécessaire)
DOCKERFILE="Dockerfile"

# Construction de l'image Docker
echo "Construction de l'image Docker..."
docker build -t $IMAGE_NAME -f $DOCKERFILE .

# Vérification du succès de la construction
if [ $? -ne 0 ]; then
    echo "Erreur : La construction de l'image Docker a échoué."
    exit 1
fi

echo "Image $IMAGE_NAME construite avec succès."

# Exécution du conteneur Docker
echo "Exécution du conteneur Docker..."
docker run $IMAGE_NAME

# Vérification de l'exécution
if [ $? -ne 0 ]; then
    echo "Erreur : L'exécution du conteneur Docker a échoué."
    exit 1
fi

echo "Conteneur $IMAGE_NAME exécuté avec succès."
