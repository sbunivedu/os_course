Please follow the instructions to setup your programming environment:
## **Step 1 Install Docker**
Download and install Docker Desktop at https://www.docker.com/products/docker-desktop/
* choose the free "Docker Personal" plan.
* create an account and confirm your email.

## **Step 2 Start Docker Desktop and Login**
Please start your Docker Desktop and run a custom image
* start your installed Docker Desktop app.
* login with your previously created account.

## **Step 3 Pull and Run an Image**
* go to a terminal (use the Docker Terminal on Windows or the "Terminal" app on Mac)
* run `docker pull lubaochuan/gcc-python-vim` in the terminal to get the image.
* run `docker run -it lubaochuan/gcc-python-vim bash` in the terminal to run the image in a container with a `bash` shell.

## **Step 4 Get Code Examples**
In your `bash shell` run `git clone https://github.com/remzi-arpacidusseau/ostep-code.git` to get a copy of the code examples from the textbook.