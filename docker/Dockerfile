# our local base image
FROM ubuntu 

LABEL description="Mooveit challenge" 
WORKDIR /app

# install build dependencies 
RUN apt-get update && apt-get install -y g++ rsync zip


# expose port 22 
EXPOSE 22
