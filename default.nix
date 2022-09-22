{
    #pkgs ? import (fetchTarball "https://github.com/NixOS/nixpkgs/archive/21.11.tar.gz") {}
    pkgs ? import <nixpkgs> {} # To be able to use the shell without internet on NixOS
}:
let
    vectorpack_lib = pkgs.stdenv.mkDerivation {
        name = "vectorpack_cpp";
        buildInputs = [ pkgs.cmake ];
        src = fetchTarball "https://github.com/Vectorpack/Vectorpack_cpp/archive/master.tar.gz"; #TODO: put a specific release/tag
        
        enableParallelBuilding = true;
    };

    jobs = rec {
        # Use for instance generation and results analysis
        python-shell = pkgs.mkShell {
            name = "python-shell";

            buildInputs = [
                (pkgs.python3.withPackages ( ps: [
                    ps.numpy
                    ps.pandas
                    ps.matplotlib
                ]))
                pkgs.jupyter
            ];
        };

        expes = pkgs.stdenv.mkDerivation {
            name = "shell-expe";

            buildInputs = [ pkgs.cmake vectorpack_lib ];

            src = pkgs.lib.sourceByRegex ./. [
                "^CMakeLists.txt"
                "^src"
                "^src/algo_lists.hpp"
                "^src/main_multidim.cpp"
                "^src/main_1dim.cpp"
            ];

            installPhase = ''
                mkdir -p $out
                cp main_multidim $out/
                cp main_1dim $out/
            '';
        };

        ## TODO: one more package with Gurobi and VPSolver
    };
in jobs
