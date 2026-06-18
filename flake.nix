{
  outputs = {...}:
  let pkgs = import <nixpkgs> {
    system = "x86_64-linux";
  };
  in {
    devShells.x86_64-linux.default = pkgs.mkShell {
      packages = with pkgs; [
        clang-tools
        lldb
      ];
      shellHook = "nu";
    };
  };
}
