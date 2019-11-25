#!/usr/bin/env bash
set +x

HX_PATH="$HOME/.hx"
mkdir -p "$HX_PATH"

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

CPU_ARCHITECTURE=$(uname -m)
case $CPU_ARCHITECTURE in
  armv5*) CPU_ARCHITECTURE="armv5";;
  armv6*) CPU_ARCHITECTURE="armv6";;
  armv7*) CPU_ARCHITECTURE="arm";;
  aarch64) CPU_ARCHITECTURE="arm64";;
  x86) CPU_ARCHITECTURE="386";;
  x86_64) CPU_ARCHITECTURE="amd64";;
  i686) CPU_ARCHITECTURE="386";;
  i386) CPU_ARCHITECTURE="386";;
esac

function GET_HELM_VERSION() {
  VERSION=$1
  HELM_PATH=$HX_PATH/helm-$VERSION
  HELM_TAR="$HELM_PATH.tar.gz"

  curl -L -o "$HELM_TAR" "https://get.helm.sh/helm-$VERSION-$OS-$CPU_ARCHITECTURE.tar.gz"
  tar --extract --file="$HELM_TAR" --strip=1 --directory="$HX_PATH" $OS-$CPU_ARCHITECTURE/helm 
  mv "$HX_PATH/helm" "$HELM_PATH"
  rm "$HELM_TAR"
}

# Ensure we have at least 1 helm version
KNOWN_VERSION="v2.16.0"
LOCAL_HELM=$HX_PATH/helm-$KNOWN_VERSION
HELM_PATH=$(command -v helm)
if [ -n "$HELM_PATH" ]; then
  LOCAL_HELM=$HELM_PATH
elif [ ! -f "$LOCAL_HELM" ]; then
  GET_HELM_VERSION $KNOWN_VERSION
fi

TARGET_VERSION=$($LOCAL_HELM version --template '{{ .Server.SemVer }}')
TARGET="$HX_PATH/helm-$TARGET_VERSION"

if [ ! -f "$TARGET" ]; then
  GET_HELM_VERSION "$TARGET_VERSION"
fi

$TARGET "$@"