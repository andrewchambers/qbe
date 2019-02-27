#! /bin/sh

exec >&2
set -eu

target="$1"
out="$3"

export CC=${CC:-gcc}
export CFLAGS=${CFLAGS:--MMD -Wall -Wextra -std=c99 -pedantic}
export LDFLAGS=${LDFLAGS:-}

anysrc="
main.c util.c parse.c cfg.c mem.c ssa.c alias.c 
load.c copy.c fold.c live.c spill.c rega.c gas.c
"

amd64src="
amd64/targ.c amd64/sysv.c amd64/isel.c amd64/emit.c
"

arm64src="
arm64/targ.c arm64/abi.c arm64/isel.c arm64/emit.c
"

v () { echo "$@" ; $@ ; }

case "$target" in
  all)
    redo-ifchange obj/qbe ;;
  
  clean)
    v rm -rf obj config.h ;;
  
  obj/qbe)
    src="$(echo $anysrc $amd64src $arm64src | sed 's, ,\n,g')"
    obj="$(sed -e 's,\.c,.o,g' -e 's,^,obj/,g' <<< "$src")"
    redo-ifchange $obj
    mkdir -p obj
    v $CC $LDFLAGS -o "$out" $obj ;;
  
  obj/*.o)
    base="${target%.o}"
    cfile="${base#obj/}.c" 
    redo-ifchange "$cfile" config.h
    mkdir -p "$(dirname $target)"
    v $CC $CFLAGS -c -o "$out" "$cfile"
    # If our CFLAGS generated deps, use them.
    if test -f $base.o.redo.d
    then
      read DEPS <$base.o.redo.d
      redo-ifchange ${DEPS#*:}
      rm $base.o.redo.d
    fi ;;

  config.h)
    (
    case `uname` in
      *Darwin*)
        echo "#define Defasm Gasmacho"
        echo "#define Deftgt T_amd64_sysv" ;;
      *)
        echo "#define Defasm Gaself" ;;
    esac
    case `uname -m` in
      *aarch64*)
        echo "$define Deftgt T_arm64" ;;
      *)
        echo "#define Deftgt T_amd64_sysv" ;;
    esac
  ) > "$out" ;;

  *)
    echo "Don't know how to build $target."
    exit 1 ;;
esac
