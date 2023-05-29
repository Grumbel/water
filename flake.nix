{
  description = "A simple OpenGL/Glut based water-fx toy";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.05";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in {
        packages = rec {
          default = water-fx;

          water-fx = pkgs.stdenv.mkDerivation {
            pname = "water-fx";
            version = "0.0.0";

            src = ./.;

            nativeBuildInputs = with pkgs; [
              cmake
              pkgconfig
            ];

            buildInputs = with pkgs; [
              libGL
              libGLU
              freeglut
            ];
           };
        };
      }
    );
}
