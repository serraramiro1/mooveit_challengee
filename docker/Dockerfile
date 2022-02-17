# our local base image
FROM ubuntu 

LABEL description="Mooveit challenge" 
WORKDIR /app

# install build dependencies 
RUN apt-get update && apt-get install -y g++ rsync zip cmake make curl libcurl4-openssl-dev
RUN apt-get install wget


# expose port 22 
EXPOSE 22
