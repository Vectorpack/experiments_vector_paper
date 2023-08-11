{
    #pkgs ? import (fetchTarball "https://github.com/NixOS/nixpkgs/archive/21.11.tar.gz") {}
    pkgs ? import <nixpkgs> {} # To be able to use the shell without internet on NixOS
}:
let
    vectorpack_lib = pkgs.stdenv.mkDerivation rec {
        name = "Vectorpack_cpp";
        buildInputs = [ pkgs.cmake ];
        src = pkgs.fetchFromGitHub {
            owner = "Vectorpack";
            repo = name;
            rev = "de50bc4ab093e3b39416e21381a377bd9de23b32"; # Specific commit
            sha256 = "sha256-4cyUAQoUsF8iILMJVaNiR8W+StVSk+p3fdgqsQ0Q5mM=";
        };
        enableParallelBuilding = true;
    };

    VPSolver_light = pkgs.stdenv.mkDerivation rec {
        name = "VPSolver_light";
        buildInputs = [ pkgs.cmake ];
        propagatedBuildInputs = [ pkgs.gurobi ];
        src = pkgs.fetchFromGitHub {
            owner = "Vectorpack";
            repo = name;
            rev = "fbe8b246c5fa8ff5281cf58a7577b1bdcb7b530c"; # Specific commit
            sha256 = "sha256-QkkLvRg7CRaw9l22TLKemBds8Y9kAyutu6Acklntsrs=";
        };
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
            name = "expe";

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

        expes-gurobi = pkgs.stdenv.mkDerivation {
            name = "expe-gurobi";
            buildInputs = [
                pkgs.cmake
                vectorpack_lib
                VPSolver_light
            ];

            src = pkgs.lib.sourceByRegex ./. [
                "^CMakeLists.txt"
                "^src"
                "^src/main_VPS.cpp"
            ];

            installPhase = ''
                mkdir -p $out
                cp main_VPS $out/
            '';
        };
    };
in jobs
