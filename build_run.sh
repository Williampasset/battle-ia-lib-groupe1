#!/bin/bash

IMAGE_NAME="battle_bot"

DOCKERFILE="Dockerfile"

echo "Building the Docker image..."
docker build -t $IMAGE_NAME -f $DOCKERFILE .

if [ $? -ne 0 ]; then
    echo "Error: Docker image build failed."
    exit 1
fi

echo "Image $IMAGE_NAME built successfully."

echo "Running the Docker container..."
docker run $IMAGE_NAME

if [ $? -ne 0 ]; then
    echo "Error: Docker container run failed."
    exit 1
fi

echo "Container $IMAGE_NAME ran successfully."
