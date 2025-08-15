# cpp_development_container
Container with C++ development tool chain base on Fedora

Run the following command on host PC to generate public key and copy to cloned repo
````
ssh-keygen -t ed25519
````
## vscode
In vscode folder see vscode files to get started on configuring tasks, launch and settings for code completion

````
podman run -d --replace --name <CONTAINER_NAME>> --network <NETWORK_NAME> -v <LOCAL_FOLER_LOCATION>>:/devenv/workspace/service:z -p 20202:22 -p 8081:8080 <NAME_OF_IMAGE>
````
