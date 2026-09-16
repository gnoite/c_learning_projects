{
  outputs = {self, nixpkgs ? import <nixpkgs>, ...}:
  let
    system = "x86_64-linux";
    pkgs = nixpkgs.legacyPackages.${system};
  in {
    devShells.${system}.default = pkgs.mkShell {
      nativeBuildInputs = with pkgs; [
        pkg-config
        clang-tools
        lldb
      ];
      shellHook = "nu";
    };
  };
}
