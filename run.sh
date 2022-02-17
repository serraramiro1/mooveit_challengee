CONTAINER_NAME="mooveit_challenge"
CHALLENGE_EXECUTABLE=$CONTAINER_NAME
RUN_CMD="cd /app && mkdir -p build && cd build && cmake .. && make && ./$CHALLENGE_EXECUTABLE"
if [ ! $(docker ps -q -f name="^${CONTAINER_NAME}$") ]; then
docker build docker -t $CONTAINER_NAME
docker run -dit --rm \
  --name $CONTAINER_NAME \
  -v $PWD/src:/app \
  -v $PWD/curlcpp:/app/curlcpp \
  $CONTAINER_NAME bash
fi

docker exec -it $CONTAINER_NAME bash -c "$RUN_CMD"

