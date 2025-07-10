# Hocus Pocus

A matching decompilation of Hocus Pocus DOS game (prototype).

## Building

Clone the repository:

```sh
git clone https://github.com/Gillou68310/hocus.git
```

Navigate into the freshly cloned repo

```sh
cd hocus
```

Now build the executable:

```sh
make all
```

If you did everything correctly, you'll be greeted with the following:

```sh
Linking DOS file: build/proto/hocus.exe
OK
```

## Docker

A Docker image containing all dependencies can be built and ran as follows:
```sh
docker build . -t hocus
docker run --rm -ti --mount src=$(pwd),target=/hocus,type=bind hocus
```

Then continue with [the building instructions](#Building)
