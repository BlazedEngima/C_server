# cpp_server
A server written in C++ to resize an image. Uses the libasyik and OpenCV libraries.

The program creates a simple HTTP server that listens on port 8080 of localhost to
resize a jpeg image, in the forrm of a base 64 encoded binary input data.

It serves this API:
```
HTTP://127.0.0.1:8080/resize_image [POST]
```

#### Input payload:  
```
content-type: application/json
{
    "input_jpeg": "[base 64 encoding of jpeg binary]",
    "desired_width": [target_width],
    "desired_length": [target_height]
}
```

#### Output payload:
##### On success:
```
HTTP 200
content-type: application/json
{
    "code": 200,
    "message": "success",
    "output_jpeg": "[base 64 encoding of output jpeg binary]"
}
```

##### On fail:
```
HTTP 4XX/5XX
content-type: application/json
{
    "code": 4xx/5xx,
    "message": "[output error description]"
}
```

## Building
There is Dockerfile given under `.devcontainer` which can be used to directly build a docker container that can run the project.

After creating the docker image, you can either `git clone` the repo inside the docker container or mount the working directory into
the docker container, here is an example:
```
docker run -it --mount type=bind,source=.,target=/opt/cpp_server <container_name> bash
```

When not using the docker container, one has to ensure that OpenCV is installed and setup as well as the libasyik library. Please refer to their
respective documentations:
- [OpenCV](https://github.com/opencv/opencv)
- [libasyik](https://github.com/okyfirmansyah/libasyik)

There are shell scripts provided to automate the building and running of the project. Do note that there is a git submodule included so be sure
to `init` the submodule before setting up the project.

To build the project:
```
git clone https://github.com/BlazedEngima/cpp_server.git
git submodule init
sh configure.sh
sh build.sh
```

The `.sh` files are simply the standard `cmake` configure and build commands.

## Running
To run the server:
```
sh run_server.sh
```
To test the server:
```
sh test_run.sh
```
in another shell

If you wish to test the server manually, the command to run the client that will request to the server follows this format:
```
./build/client <img_path> <desired_width> <desired_height>
```
There will also be an output image file produced by the client after recieving the response from the server. The output image will be in `build/resources/result.jpg`.
