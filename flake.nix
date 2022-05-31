{
  description = "A simple OpenGL/Glut based water-fx toy";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-22.05";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in rec {
        packages = flake-utils.lib.flattenTree {
          water-fx = pkgs.stdenv.mkDerivation {
            pname = "water-fx";
            version = "0.0.0";
            src = nixpkgs.lib.cleanSource ./.;
            nativeBuildInputs = [
              pkgs.cmake
              pkgs.pkgconfig
            ];
            buildInputs = [
              pkgs.libGL
              pkgs.libGLU
              pkgs.freeglut
            ];
           };
        };
        defaultPackage = packages.water-fx;
      });
}
