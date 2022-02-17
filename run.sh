RUN_CMD="cd /app && g++ main.cppt && ./a.out"
CONTAINER_NAME="mooveit_challenge"
if [ ! $(docker ps -q -f name="^${CONTAINER_NAME}$") ]; then
docker build docker -t $CONTAINER_NAME
docker run -dit --rm \
  --name $CONTAINER_NAME \
  -v $PWD/src:/app \
  $CONTAINER_NAME bash
fi

docker exec -it $CONTAINER_NAME bash -c "$RUN_CMD"

