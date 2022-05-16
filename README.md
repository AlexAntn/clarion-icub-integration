This project is intended to be developed using docker. 

In order to build the image, just download the Dockerfile (/docker/Dockerfile) and build the image: `docker build . -t clarion-icub-integration:latest`. To ensure that the latest changes are taken into consideration, run the following command instead: `docker build . -t clarion-icub-integration:latest --no-cache`

Inside the container, you will find the cloned repo in the following directory: /projects/clarion-icub-integration.


If no libraries are installed (so you don't rebuild the docker image again), you can instead work with the same image/container, making sure to pull the code in the repository.

To make sure your changes are not lost, either commit them to github, or you can commit the container using the following commands:

```
docker container ls -a -> from here copy the container ID
docker commmit <container-ID> <name>
```

This is not advised.

