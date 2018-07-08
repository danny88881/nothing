with import <nixpkgs> {}; {
    nothingEnv = stdenv.mkDerivation {
        name = "nothing-env";
        buildInputs = [ stdenv
                        gcc
                        SDL2
                        SDL2_mixer
                        SDL2_ttf
                        mesa
                        pkgconfig
                        cmake
                        xqilla
                        valgrind
                        racket
                        inotifyTools
                      ];
        LD_LIBRARY_PATH="${mesa}/lib";
    };
}
