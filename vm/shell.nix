let
  pkgs = import <nixpkgs> {};
in
pkgs.mkShell {
  buildInputs = [
    pkgs.clang
    pkgs.ccls
    pkgs.gdb
    pkgs.pwndbg
  ];
}
