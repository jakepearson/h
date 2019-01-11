#!/usr/bin/env bash
set +x

HX_PATH="$HOME/.hx"
mkdir -p "$HX_PATH/cache"

case "$OSTYPE" in
  *arwin*)
    OS="darwin"
    ;;
  *in32* | *indows*)
    OS="windows"
    ;;
  *)
    OS="linux"
esac

TARGET_VERSION=$(helm version --template '{{ .Server.SemVer }}')

TARGET=$HX_PATH/helm-$TARGET_VERSION

if [ ! -f $TARGET ]; then
  cd "$HX_PATH"
  curl -LO "https://storage.googleapis.com/kubernetes-helm/helm-$TARGET_VERSION-$OS-amd64.tar.gz"
  tar xvzf helm-$TARGET_VERSION-$OS-amd64.tar.gz
  mv $HX_PATH/$OS-amd64/helm $TARGET
  rm -rf $OS-amd64
  chmod +x $TARGET
fi

$TARGET "$@"